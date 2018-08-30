/*
 * @requires: sg3-utils
 *            libudev-dev
 *
 *
 */

#include <libudev.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
#include <locale.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>

using std::vector;
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
struct path_dev {
    int major;
    int minor;
    string vendor;
    string devpath;
    string syspath;
};
//struct path paths[32];

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

int FromHex(const string &s) { return strtoul(s.c_str(), NULL, 16); }

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
    //state = std::stoi(sub);
    state = FromHex(sub);
    //state = 42;
    //cout << "alua state: (" << sub << ")\n";
    return state;
}

#define DEVNODE 0
#define SYSPATH 1
#define VENDOR  2
#define MODEL   3
char *get_disk_path_by_devnum(struct udev* udev, int mj, int mn, int type) {
    struct udev_enumerate* enumerate = udev_enumerate_new(udev);
    dev_t n;
    char *devnode, *vendor, *syspath, *model;
    int major, minor;

    udev_enumerate_add_match_subsystem(enumerate, "scsi");
    udev_enumerate_add_match_property(enumerate, "DEVTYPE", "scsi_device");
    udev_enumerate_scan_devices(enumerate);

    struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry *entry;

    udev_list_entry_foreach(entry, devices) {
        const char* devpath = udev_list_entry_get_name(entry);
        struct udev_device* scsi = udev_device_new_from_syspath(udev, devpath);

        struct udev_device* block = get_child(udev, scsi, "block");
        struct udev_device* scsi_disk = get_child(udev, scsi, "scsi_disk");

        if (block && scsi_disk) {
            n = udev_device_get_devnum(block);
            major = n>>8;
            minor = n&0xff;
            if (major == mj && minor == mn) {
                char cmd[32];
                syspath = (char *) udev_device_get_syspath(block);
                devnode = (char *) udev_device_get_devnode(block);
                vendor  = (char *) udev_device_get_sysattr_value(scsi, "vendor");
                model  = (char *) udev_device_get_sysattr_value(scsi, "model");
                //printf("   --> %s - %s - %s \n", devnode, vendor, model);
                memset(cmd, 0, 32);
                sprintf(cmd, "sg_stpg %s", devnode);
                string command(cmd);
                string out = get_stdout_from_cmd(command);
                std::size_t found = out.find("target port group asymmetric access state");
                if (found != std::string::npos) {
                    int state = get_state(out);
                    switch (state) {
                        case TPGS_STATE_OPTIMIZED:
                            //cout << "alua state: OPTIMIZED\n"; 
                            break;
                        case TPGS_STATE_NONOPTIMIZED:
                            //cout << "alua state: NONOPTIMIZED\n"; 
                            break;
                        case TPGS_STATE_STANDBY:
                            //cout << "alua state: STANDBY\n"; 
                            break;
                        case TPGS_STATE_UNAVAILABLE:
                            //cout << "alua state: UNAVAILABLE\n"; 
                            break;
                        case TPGS_STATE_LBA_DEPENDENT:
                            //cout << "alua state: LBA_DEPENDENT\n"; 
                            break;
                        case TPGS_STATE_OFFLINE:
                            //cout << "alua state: OFFLINE\n"; 
                            break;
                        case TPGS_STATE_TRANSITIONING:
                            //cout << "alua state: TRANSITIONING\n"; 
                            break;
                        default:
                            //cout << "alua state: UNKNOWN STATE (" << state << endl; 
                            break;
                    }
                } else {
                    //cout << "(no alua info found)" << std::endl;
                }
                switch (type) {
                    case DEVNODE:
                        return devnode;
                    case SYSPATH:
                        return syspath;
                    case VENDOR:
                        return vendor;
                    case MODEL:
                        return model;
                }
            }
        }

        if (block)
            udev_device_unref(block);

        if (scsi_disk)
            udev_device_unref(scsi_disk);

        if (scsi)
            udev_device_unref(scsi);
    }

    if (enumerate)
        udev_enumerate_unref(enumerate);
    return NULL;
}

vector<string> split_string(const string& str, const string& delimiter)
{
    vector<string> strings;
    string::size_type pos = 0;
    string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }
    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(str.substr(prev));
    return strings;
}

class mpath {
public:
    string name;
    size_t start;
    size_t length;
    string policy;
    int npaths;
    vector<struct path_dev> devs;
};

vector<mpath> mpaths;

mpath parse_path_data(vector<string>& path_data)
/*
 * mpath3: 0 20971520 multipath 0 0 1 1 round-robin 0 2 1 8:112 100 8:48 100
 *         start, length, target name, num features, 
 *           length   target name
 *                              num features
 *                                num hw handler features
 *                                  num path groups
 *                                    next path group to try
 *                                      path selector
 *                                                  num selector args (always 0)
 *                                                    num paths
 *                                                      num path arguments (always 1)
 *                                                        maj:min   
 *                                                              num IO to send before switching paths
 */
{
    mpath data;
    vector<string>::iterator itr = path_data.begin();
    data.name = *itr;
    itr++; data.start = strtol(itr->c_str(),0,10); //std::stoi(*itr);
    itr++; data.length = strtol(itr->c_str(),0,10); //std::stoi(*itr);
    itr++; // "multipath"
    itr++; // int ?
    itr++; // int ? 
    itr++; // int ? 
    itr++; // int ? 
    itr++; data.policy = *itr;
    itr++; // int ?
    itr++; data.npaths = strtol(itr->c_str(),0,10); //std::stoi(*itr);
    itr++; // int ?
    for (int i = 0; i < data.npaths; ++i) {
        itr++; // major:minor data.npaths = std::stoi(*itr);
        vector<string> maj_min = split_string(*itr, ":");
        vector<string>::iterator mitr = maj_min.begin();
            int major = strtol(mitr->c_str(),0,10); //std::stoi(*mitr);
            mitr++;
            int minor = strtol(mitr->c_str(),0,10); //std::stoi(*mitr);
            path_dev pd;
            pd.major = major;
            pd.minor = minor;
            data.devs.push_back(pd);
        itr++; // int ?
    }
    return data;
}

void show_paths()
{
    size_t l_meg, l_gig;
    char cmd[32];
    char line[80];
    for (vector<mpath>::iterator itr = mpaths.begin(); itr != mpaths.end(); itr++) {
        mpath path = *itr;
        char *vendor, *model;
        vendor  = get_disk_path_by_devnum(udev, path.devs[0].major, path.devs[0].minor, VENDOR);
        model   = get_disk_path_by_devnum(udev, path.devs[0].major, path.devs[0].minor, MODEL);
        sprintf(line, "%s (%s) %s %s,%s", path.name.c_str(), "251534354524c3665", "dm-1", vendor, model);
        cout << line << endl;
        l_meg = (path.length * 512) / 1024 / 1024;
        l_gig = (path.length * 512) / 1024 / 1024 / 1024;
        if (l_gig) {
            cout << "size=" << l_gig << "G";
        } else if (l_meg) {
            cout << "size=" << l_meg << "M";
        } else {
            cout << "size=" << path.length;
        }
        cout << " features='0' hwhandler='0' wp=rw" << endl;
        cout << "`-+- policy='" << path.policy << "' prio=1 status=active" << endl;
#if 1
        for (int i = 0; i < path.npaths; i++) {
            char *devnode=NULL, *spath=NULL;
            bool nopath = false;
            string device_path;
            devnode = get_disk_path_by_devnum(udev, path.devs[i].major, path.devs[i].minor, DEVNODE);
            spath   = get_disk_path_by_devnum(udev, path.devs[i].major, path.devs[i].minor, SYSPATH);
            char p[16];
            if (devnode) { 
                nopath = false;
                sprintf(p, "%s %d:%d active ready  running, alua=", devnode,  path.devs[i].major, path.devs[i].minor);
                path.devs[i].devpath = p;
                device_path = devnode;
            } else {
                nopath = true;
                sprintf(p, "  #:# failed faulty  running, alua=");
                path.devs[i].devpath = p;
            }
            string syspath;
            if (spath) { 
                int len;
                path.devs[i].syspath = spath;
                len = path.devs[i].syspath.length() - 17;
                syspath =  path.devs[i].syspath.substr(len); //(80);
                syspath.erase(7);
            } else {
                syspath = path.devs[i].syspath = "#:#:#:#";
            }
            memset(line, 0, 80);
            if (i < path.npaths-1)
                sprintf(line, "  |- %s %s", syspath.c_str(), path.devs[i].devpath.c_str());
            else
                sprintf(line, "  `- %s %s", syspath.c_str(), path.devs[i].devpath.c_str());
            cout << line;

            if (!nopath) {
                memset(cmd, 0, 32);
                sprintf(cmd, "sg_rtpg %s", device_path.c_str());
                string command(cmd);
                string out = get_stdout_from_cmd(command);
                std::size_t found = out.find("target port group asymmetric access state");
                if (found != std::string::npos) {
                    int state = get_state(out);
                    switch (state) {
                        case TPGS_STATE_OPTIMIZED:
                            cout << "OPTIMIZED"; 
                            break;
                        case TPGS_STATE_NONOPTIMIZED:
                            cout << "NONOPTIMIZED"; 
                            break;
                        case TPGS_STATE_STANDBY:
                            cout << "STANDBY"; 
                            break;
                        case TPGS_STATE_UNAVAILABLE:
                            cout << "UNAVAILABLE"; 
                            break;
                        case TPGS_STATE_LBA_DEPENDENT:
                            cout << "LBA_DEPENDENT"; 
                            break;
                        case TPGS_STATE_OFFLINE:
                            cout << "OFFLINE"; 
                            break;
                        case TPGS_STATE_TRANSITIONING:
                            cout << "TRANSITIONING"; 
                            break;
                        default:
                            cout << "UNKNOWN STATE (" << state << ")"; 
                            break;
                    }
                } else {
                    cout << "(alua disabled)"; 
                }
            } else {
                cout << "(bad path)"; 
            }
            cout << endl;
        }
#endif
        cout << endl;
    }
//error_out:
//    cout << "(no alua info found)" << std::endl;
//    return;
}

void fetch_paths()
//sprintf(cmd, "sg_stpg %s", "/dev/sdd");
{
    char cmd[32];
    mpath path;

    memset(cmd, 0, 32);
    sprintf(cmd, "dmsetup table");
    string command(cmd);
    string out = get_stdout_from_cmd(command);
    vector<string> mp_out = split_string(out, "\n");
    //int i = 1;
    for (vector<string>::iterator itr = mp_out.begin(); itr != mp_out.end(); itr++) {
        if (itr->find("mpath") != string::npos) {
            //cout << "#" << i++ << " - \"" << *itr << "\"\n";
            vector<string> path_data = split_string(*itr, " ");
            path = parse_path_data(path_data);
            //mpaths.emplace_back(path);
            mpaths.push_back(path);
            
        }
    }
    show_paths();
#if 0    
    memset(cmd, 0, 32);
    sprintf(cmd, "multipath -ll"); // vectorize by line
    string command2(cmd);
    out = get_stdout_from_cmd(command2);
    mp_out = split_string(out, "\n");
    cout << "paths\n";
    i = 1;
    for (vector<string>::iterator itr = mp_out.begin(); itr != mp_out.end(); itr++) {
        cout << "#" << i++ << " - \"" << *itr << "\"\n";
        //if (itr->find("mpath") != string::npos) {
        //    cout << "#" << i++ << " - \"" << *itr << "\"\n";
        //    itr++;
        //    cout << "#" << i++ << " - \"" << *itr << "\"\n";
        //    itr++;
        //    cout << "#" << i++ << " - \"" << *itr << "\"\n";
        //}
    }
    cout << out << endl;
#endif
    return;
}

int main(int argc, char *argv[])
{
    udev = udev_new();
    fetch_paths();
    udev_unref(udev);

    return 0;
}
