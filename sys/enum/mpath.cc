/*
 * @requires: sg3-utils
 *            libdevmapper-dev
 *            libudev-dev
 *
 *
 */

#include <libudev.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <libdevmapper.h>
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

#define TGT_MPATH	                    "multipath"
#define PARAMS_SIZE		                4096
#define TPGS_STATE_OPTIMIZED            0x0
#define TPGS_STATE_NONOPTIMIZED         0x1
#define TPGS_STATE_STANDBY              0x2
#define TPGS_STATE_UNAVAILABLE          0x3
#define TPGS_STATE_LBA_DEPENDENT        0x4
#define TPGS_STATE_OFFLINE              0xe
#define TPGS_STATE_TRANSITIONING        0xf

// evil global variables
struct udev *udev;
struct path {
    int major;
    int minor;
};
struct path paths[32];

void hexdump(char *buffer, unsigned int length)
{
    char OffsetBuf[10];
    unsigned int LastStart = 0, i, k, j;
    for (i = 0 ; i < length ; i++) {
        if (i % 16 == 0) {
            sprintf(OffsetBuf, "%03x", i);
            printf("%4s:", OffsetBuf);
        }
        if (i % 4 == 0) {
            printf(" ");
        }
        printf("%02x ", buffer[i]);
        if (i % 16 == 15 || i == length-1) {
            if (i == length-1) {
                for (k = i % 16 ; k < 15 ; k++) {
                     printf( "   " );
                     if (k % 4 == 3 && k % 16 != 0) {
                         printf(" ");
                     }
                }
            }
            printf("|");
            for (j = LastStart ; j <= i ; j++) {
                if (j % 4 == 0) {
                    printf(" ");
                }
                if (buffer[j] > 31 && buffer[j] < 127) {
                    printf("%c", buffer[j]);
                } else {
                    printf(".");
                }
            }
            if (i == length-1) {
                printf("\n");
                break;
            }
            printf("\n");
            LastStart += 16;
        }        
    }
}

static
struct udev_device*
get_child(struct udev* udev, struct udev_device* parent, const char* subsystem) {
  struct udev_device* child = NULL;
  struct udev_enumerate *enumerate = udev_enumerate_new(udev);

  udev_enumerate_add_match_parent(enumerate, parent);
  udev_enumerate_add_match_subsystem(enumerate, subsystem);
  udev_enumerate_scan_devices(enumerate);

  struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
  struct udev_list_entry *entry;

  udev_list_entry_foreach(entry, devices) {
      const char *path = udev_list_entry_get_name(entry);
      child = udev_device_new_from_syspath(udev, path);
      break;
  }

  udev_enumerate_unref(enumerate);
  return child;
}

string get_stdout_from_cmd(string &cmd) {

    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];

    cmd.append(" 2>&1"); // Do we want STDERR?

    stream = popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
        pclose(stream);
    }
    return data;
}



int get_state(string &alua)
{
    //string state = osnstr::strBetween(alua, "state:", "\n");
    //return osnstr::str2int(state);
    int state;
    string find("target port group asymmetric access state");
    std::size_t found = alua.find(find);
    if (found == std::string::npos) {
        cout << "error string too long\n";
        return 24;
    }
    found += find.length();
    alua.erase(found+7);
    string sub = alua.substr(found+3);
    state = std::stoi(sub, nullptr, 0);
    //cout << "alua state: (" << sub << ")\n";
    return state;
}

char *get_disk_path_by_devnum(struct udev* udev, int mj, int mn) {
    struct udev_enumerate* enumerate = udev_enumerate_new(udev);
    dev_t n;
    int major, minor;

    udev_enumerate_add_match_subsystem(enumerate, "scsi");
    udev_enumerate_add_match_property(enumerate, "DEVTYPE", "scsi_device");
    udev_enumerate_scan_devices(enumerate);

    struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry *entry;

    udev_list_entry_foreach(entry, devices) {
        const char* path = udev_list_entry_get_name(entry);
        struct udev_device* scsi = udev_device_new_from_syspath(udev, path);

        struct udev_device* block = get_child(udev, scsi, "block");
        struct udev_device* scsi_disk = get_child(udev, scsi, "scsi_disk");

        if (block && scsi_disk) {
            n = udev_device_get_devnum(block);
            major = n>>8;
            minor = n&0xff;
            if (major == mj && minor == mn) {
                char cmd[32];
                //const char *path = udev_device_get_syspath(block);
                const char *devnode = udev_device_get_devnode(block);
                const char *vendor = udev_device_get_sysattr_value(scsi, "vendor");
                printf("   --> %s - %s ", devnode, vendor);
                memset(cmd, 0, 32);
                sprintf(cmd, "sg_rtpg %s", devnode);
                string command(cmd);
                string out = get_stdout_from_cmd(command);
                std::size_t found = out.find("target port group asymmetric access state");
                if (found != std::string::npos) {
                    int state = get_state(out);
                    switch (state) {
                        case TPGS_STATE_OPTIMIZED:
                            cout << "alua state: OPTIMIZED\n"; 
                            break;
                        case TPGS_STATE_NONOPTIMIZED:
                            cout << "alua state: NONOPTIMIZED\n"; 
                            break;
                        case TPGS_STATE_STANDBY:
                            cout << "alua state: STANDBY\n"; 
                            break;
                        case TPGS_STATE_UNAVAILABLE:
                            cout << "alua state: UNAVAILABLE\n"; 
                            break;
                        case TPGS_STATE_LBA_DEPENDENT:
                            cout << "alua state: LBA_DEPENDENT\n"; 
                            break;
                        case TPGS_STATE_OFFLINE:
                            cout << "alua state: OFFLINE\n"; 
                            break;
                        case TPGS_STATE_TRANSITIONING:
                            cout << "alua state: TRANSITIONING\n"; 
                            break;
                        default:
                            cout << "alua state: UNKNOWN STATE (" << state << endl; 
                            break;
                    }
                } else {
                    std::cout << "(no alua info found)" << std::endl;
                }
                break;
            }
        }

        if (block) {
            udev_device_unref(block);
        }

        if (scsi_disk) {
            udev_device_unref(scsi_disk);
        }

        udev_device_unref(scsi);
    }

    udev_enumerate_unref(enumerate);
    return NULL;
}

int
dm_drv_version (unsigned int * version, char * str)
{
	int r = 2;
	struct dm_task *dmt;
	struct dm_versions *target;
	struct dm_versions *last_target;
	unsigned int *v;

	version[0] = 0;
	version[1] = 0;
	version[2] = 0;

	if (!(dmt = dm_task_create(DM_DEVICE_LIST_VERSIONS)))
		return 1;

	dm_task_no_open_count(dmt);

	if (!dm_task_run(dmt)) {
		printf("Can not communicate with kernel DM\n");
		goto out;
	}
	target = dm_task_get_versions(dmt);

	do {
		last_target = target;
        printf("target name: %s\n", target->name);
		if (!strncmp(str, target->name, strlen(str))) {
			r = 1;
			break;
		}
		//target = (void *) target + target->next;
		target = target + target->next;
	} while (last_target != target);

	if (r == 2) {
		printf("DM %s kernel driver not loaded\n", str);
		goto out;
	}
	v = target->version;
        version[0] = v[0];
        version[1] = v[1];
        version[2] = v[2];
	r = 0;
out:
	dm_task_destroy(dmt);
	return r;
}

static int
dm_lib_prereq (void)
{
    char version[64];
    int v[3];
    dm_get_library_version(version, sizeof(version));
    sscanf(version, "%d.%d.%d ", &v[0], &v[1], &v[2]);
    printf("mapper version: %s\n", version);
    return 1;
}


int dm_prereq (void)
{
    if (dm_lib_prereq())
        return 1;
    //return dm_drv_prereq();
    return 0;
}

int
dm_get_info (char * mapname, struct dm_info ** dmi)
{
    int r = 1;
    struct dm_task *dmt = NULL;

    if (!mapname)
        return 1;

    if (!*dmi)
        *dmi = (struct dm_info *) malloc(sizeof(struct dm_info));

    if (!*dmi)
        return 1;

    if (!(dmt = dm_task_create(DM_DEVICE_INFO)))
        goto out;

    if (!dm_task_set_name(dmt, mapname))
        goto out;

    dm_task_no_open_count(dmt);

    if (!dm_task_run(dmt))
        goto out;

    if (!dm_task_get_info(dmt, *dmi))
        goto out;

    r = 0;
out:
    if (r) {
        memset(*dmi, 0, sizeof(struct dm_info));
        free(*dmi);
        *dmi = NULL;
    }

    if (dmt)
        dm_task_destroy(dmt);

    return r;
}

void show_dminfo(struct dm_info *dmi)
{
    printf("exists %x\n", dmi->exists);
    printf("suspended %x\n", dmi->suspended);
    printf("live_table; %x\n", dmi->live_table);
    printf("inactive_table %x\n", dmi->inactive_table);
    printf("open_count %x\n", dmi->open_count);
    printf("event_nr %x\n", dmi->event_nr);
    printf("major %x\n", dmi->major);
    printf("minor; %x\n", dmi->minor);
    printf("read_only; %x\n", dmi->read_only);
    printf("target_count %x\n", dmi->target_count);
}

int
dm_get_major (char * mapname)
{
    int r = -1;
    struct dm_task *dmt;
    struct dm_info info;

    if (!(dmt = dm_task_create(DM_DEVICE_INFO)))
        return 0;

    if (!dm_task_set_name(dmt, mapname))
        goto out;

    if (!dm_task_run(dmt))
        goto out;

    if (!dm_task_get_info(dmt, &info))
        goto out;

    if (!info.exists)
        goto out;

    r = info.major;
out:
    dm_task_destroy(dmt);
    return r;
}

int
dm_get_minor (char * mapname)
{
    int r = -1;
    struct dm_task *dmt;
    struct dm_info info;

    if (!(dmt = dm_task_create(DM_DEVICE_INFO)))
        return 0;

    if (!dm_task_set_name(dmt, mapname))
        goto out;

    if (!dm_task_run(dmt))
        goto out;

    if (!dm_task_get_info(dmt, &info))
        goto out;

    if (!info.exists)
        goto out;

    r = info.minor;
out:
    dm_task_destroy(dmt);
    return r;
}

char *
dm_mapname(int major, int minor)
{
    char * response = NULL;
    const char *map;
    struct dm_task *dmt;
    int r;
    //int loop = MAX_WAIT * LOOPS_PER_SEC;

    printf("get name: [%d:%d]\n", major, minor);
    if (!(dmt = dm_task_create(DM_DEVICE_STATUS))) {
        printf("bailing 1\n");
        return NULL;
    }

    if (!dm_task_set_major(dmt, major) ||
        !dm_task_set_minor(dmt, minor)) {
        printf("bailing 2\n");
        goto bad;
    }

    dm_task_no_open_count(dmt);
    r = dm_task_run(dmt);
    if (!r) {
        printf("%i:%i: timeout fetching map name", major, minor);
        goto bad;
    }

    map = dm_task_get_name(dmt);
    if (map && strlen(map)) {
        printf("name: %s\n", (char *) dm_task_get_name(dmt));
        //response = STRDUP((char *)dm_task_get_name(dmt));
    } else {
        printf("bailing 3\n");
    }

    dm_task_destroy(dmt);
    return response;
bad:
    dm_task_destroy(dmt);
    printf("%i:%i: error fetching map name", major, minor);
    return NULL;
}

void parse_mp_params(char *parms, int *nr_paths)
/*
 * 0 0 1 1 round-robin 0 2 1 8:80 100 8:48 100 
 *
 * TODO: parse into vector of strings
 */
{
    int npaths, i, j, major, minor;
    char buff[PARAMS_SIZE];
    char tok[16];
   
    //cout << "parse parameters:" << endl; 
    //cout << parms << endl; 

    // get parm 1 - num
    i = 0;
    memset(tok, 0, 16);
    while (isdigit(*parms)) {
        tok[i++] = *parms++;
    }
    tok[i]='\0';
    parms++;

    // get parm 1 - num
    i = 0;
    memset(tok, 0, 16);
    while (isdigit(*parms)) {
        tok[i++] = *parms++;
    }
    tok[i]='\0';
    parms++;

    // get parm 1 - num
    i = 0;
    memset(tok, 0, 16);
    while (isdigit(*parms)) {
        tok[i++] = *parms++;
    }
    tok[i]='\0';
    parms++;

    // get parm 1 - num
    i = 0;
    memset(tok, 0, 16);
    while (isdigit(*parms)) {
        tok[i++] = *parms++;
    }
    tok[i]='\0';
    parms++;

    // get parm 1 - num
    i = 0;
    memset(tok, 0, 16);
    while (!isspace(*parms)) {
        tok[i++] = *parms++;
    }
    tok[i]='\0';
    parms++;
    
    // get parm 1 - num
    i = 0;
    memset(tok, 0, 16);
    while (isdigit(*parms)) {
        tok[i++] = *parms++;
    }
    tok[i]='\0';
    parms++;

    // get number of paths - num
    i = 0;
    memset(tok, 0, 16);
    while (isdigit(*parms)) {
        tok[i++] = *parms++;
    }
    tok[i]='\0';
    npaths = atoi(tok);
    *nr_paths = npaths;
    parms++;

    // get parm 1 - num
    i = 0;
    memset(tok, 0, 16);
    while (isdigit(*parms)) {
        tok[i++] = *parms++;
    }
    tok[i]='\0';
    //printf("num 4: %s\n", tok);
    parms++;

    memset(buff, 0, PARAMS_SIZE);
    for (j = 0; j < npaths; j++) {
        i = 0;
        memset(tok, 0, 16);
        while (isdigit(*parms)) {
            tok[i++] = *parms++;
        }
        tok[i]='\0';
        major = atoi(tok);
        parms++;

        i = 0;
        memset(tok, 0, 16);
        while (isdigit(*parms)) {
            tok[i++] = *parms++;
        }
        tok[i]='\0';
        minor = atoi(tok);
        parms++;

        i = 0;
        memset(tok, 0, 16);
        while (isdigit(*parms)) {
            tok[i++] = *parms++;
        }
        tok[i]='\0';
        parms++;

        paths[j].major = major;
        paths[j].minor = minor;


    }
}

extern int
dm_get_map(const char * name, unsigned long long * size, char * outparams)
{
    int r = 1, i;
    struct dm_task *dmt;
    void *next = NULL;
    uint64_t start, length, l_meg, l_gig;
    char *target_type = NULL;
    char *params = NULL;
    int nr_paths;

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("%s:\t", name);

    if (!(dmt = dm_task_create(DM_DEVICE_TABLE)))
        return 1;
    if (!dm_task_set_name(dmt, name))
        goto out;
    dm_task_no_open_count(dmt);
    if (!dm_task_run(dmt))
        goto out;
    do {
        next = dm_get_next_target(dmt, next, &start, &length,
                    &target_type, &params);
        parse_mp_params(params, &nr_paths);
        l_meg = (length * 512) / 1024 / 1024;
        l_gig = (length * 512) / 1024 / 1024 / 1024;
        if (l_gig) {
            printf("%lu %luG %s ", start, l_gig, target_type);
        } else if (l_meg) {
            printf("%lu %luM %s ", start, l_meg, target_type);
        } else {
            printf("%lu %lu %s ", start, length, target_type);
        }
        printf("%s\n", params);
        //major = dm_get_major((char *) name);
        //minor = dm_get_minor((char *) name);
        //printf("number of paths %d\n", nr_paths);
        for (i = 0; i < nr_paths; i++) {
            //printf("path %d: major %d, minor %d\n", i, paths[i].major, paths[i].minor);
            get_disk_path_by_devnum(udev, paths[i].major, paths[i].minor);
        }
    } while (next);

    if (size)
        *size = length;

    if (!outparams) {
        r = 0;
        goto out;
    }
    if (snprintf(outparams, PARAMS_SIZE, "%s", params) <= PARAMS_SIZE)
        r = 0;
out:
    dm_task_destroy(dmt);
    return r;
}

void fetch_paths()
{
    struct dm_names *names;
    struct dm_task *task;
    unsigned next = 0;
    unsigned long long size;
    //printf("fetch all multipath devices...\n");

    if (!(task = dm_task_create(DM_DEVICE_LIST))) {
        printf("failed to create task\n");
    } else {
        if (!dm_task_set_name(task, "multipath"))
            goto out;
        dm_task_no_open_count(task);
        if (!dm_task_run(task)) {
            printf("bad runner\n");
            goto out;
        }
        if (!(names = dm_task_get_names(task))) {
            printf("failed to get names\n");
        }
        do {
            names = (struct dm_names *) ((char *) names + next);
            dm_get_map(names->name, &size, NULL);
            next = names->next;
        } while (next);
    }
    dm_task_destroy (task);
out:
    return;
}

void enum_disks()
{
    struct udev* udev = udev_new();
    get_disk_path_by_devnum(udev, 0, 0);
    udev_unref(udev);
}

int main(int argc, char *argv[])
{
    udev = udev_new();
    dm_prereq();
    fetch_paths();
    udev_unref(udev);

    return 0;
}
