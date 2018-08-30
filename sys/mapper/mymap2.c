#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/bio.h>
#include <linux/device-mapper.h>
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/sysfs.h>

#define BUCKET0        512
#define BUCKET1       1024
#define BUCKET2     4*1024
#define BUCKET3     8*1024
#define BUCKET4    16*1024
#define BUCKET5    32*1024
#define BUCKET6    64*1024
#define BUCKET7   128*1024
#define BUCKET8   256*1024

#define SEC2NANO                    1000000000.0f
#define MY_MAPPER_NAME              "my_mapper"
#define LBA_ZONE_SIZE               1024 * 1024
#define MAX_LBA_ZONES               64
#define MAX_LATENCY_HEAT_BUCKETS    64
#define SAMPLE_SIZE                 16

char *buckets[10] = {   "512"   ,    "1k",       "4k",     "8k",       "16k",      "32k",        "64k",    "128k",     "256k", "urr?"};
char *lines[10]   = { "    ========", "========", "========", "========", "========", "========", "========", "========", "========", "========"};

struct my_dm_target {
    struct list_head node;
    struct dm_dev *dev;
    struct dm_target *ti;
    struct timer_list timer;
    unsigned int started;
    unsigned long jiffies_start;
    unsigned long jiffies_stop;
    char name[256];
    unsigned long lba_heat_buckets[MAX_LBA_ZONES]; // in giga-sector bucket sizes
    unsigned long zone_iops[MAX_LBA_ZONES]; // in giga-sector bucket sizes
    unsigned long zone_accum[MAX_LBA_ZONES]; // in giga-sector bucket sizes
    unsigned long latency_heat_buckets[16]; // in microseconds: 0 - 2ms: bucket size = 32us
    unsigned long wr_buckets[16];
    unsigned long rd_buckets[16];
    sector_t start;
    sector_t size;
};

struct my_context {
    struct my_dm_target *mdt;
    unsigned long start;
    unsigned long size;
    struct bio *bio;
    struct timespec time;
};

static DEFINE_SPINLOCK(mdt_list_lock);
static LIST_HEAD(mdt_list);
static int my_start_timer(struct my_dm_target *mdt);

struct my_dm_target *curr_mdt;

struct my_dm_target *my_get_target(const char *arg)
{
    struct my_dm_target *mdt;
    printk("my_get_target: %s\n", arg);
    list_for_each_entry(mdt, &mdt_list, node) {
        printk("checking: %s\n", mdt->name);
        //if (strstr(mdt->name, arg)) {
            return mdt;
        //}
    }
    return NULL;
}

/*
 * 1. build the driver and insmod ./mymod.ko
 * 2. echo 0 $(blockdev --getsize /dev/sdb) mymap /dev/sdb 0 $(blockdev --getsize /dev/sdb)|dmsetup create my_qdev
 *      disk-scan
 *      disk-list
 *      check GUI for dm devices under physical disks
 * 3. echo 1 >  /sys/kernel/my_mapper/foo  # clears the counters
 * 4. dd if=/dev/zero of=/dev/dm-0 oflag=direct bs=512 count=20000
 * 5. cat /sys/kernel/my_mapper/foo        # spews the counters
 * 6. dmsetup remove my_qdev
 * 7. rmmod mymap
 */

unsigned long get_size(struct bio *bio)
{
    unsigned long size;
    struct bio_vec bvec;
    struct bvec_iter iter;
    size = 0;
    bio_for_each_segment(bvec, bio, iter) {
        size += bvec.bv_len;
    }
    return size;
}

unsigned int get_bucket(unsigned long size)
{
    unsigned int bucket;

    if      (size <= BUCKET0) bucket = 0;
    else if (size <= BUCKET1) bucket = 1;
    else if (size <= BUCKET2) bucket = 2;
    else if (size <= BUCKET3) bucket = 3;
    else if (size <= BUCKET4) bucket = 4;
    else if (size <= BUCKET5) bucket = 5;
    else if (size <= BUCKET6) bucket = 6;
    else if (size <= BUCKET7) bucket = 7;
    else if (size <= BUCKET8) bucket = 8;
    else                      bucket = 9;

    return bucket;
}

unsigned long cal_running_avg(unsigned long avg, unsigned long new_sample) 
{
    if (avg != 0) {
        avg -= avg / SAMPLE_SIZE;
    }
    avg += new_sample / SAMPLE_SIZE;
    return avg;
}

static int add_latency_heat(struct my_dm_target *mdt, struct bio *bio)
{
    unsigned int bucket;
    unsigned long size;
    unsigned long avg;
    struct my_context *context = bio->bi_private;
    struct timespec t1, t2;
    unsigned long elapsed_time;

    getrawmonotonic(&t2);
    t1 = context->time;
    elapsed_time = ((t2.tv_nsec) - (t1.tv_nsec));
    elapsed_time /= 1000; // nsec -> usec


    size = context->size;
    bucket = get_bucket(size);
    avg = cal_running_avg(mdt->latency_heat_buckets[bucket], elapsed_time);
    if (avg > 9999) avg = 9999;
    //printk("add_latency_heat[%d] = %ld, size=%lu\n", bucket, avg, size);
    mdt->latency_heat_buckets[bucket] = avg;

    return 0;
}

static int add_zone_iops(struct my_dm_target *mdt, struct bio *bio)
{
    int zone;
    zone = bio->bi_iter.bi_sector;
    zone /= LBA_ZONE_SIZE;
    if (zone >= MAX_LBA_ZONES-1) zone = MAX_LBA_ZONES-1;
    mdt->zone_accum[zone]++;
    return 0;
}

static int add_lba_heat(struct my_dm_target *mdt, struct bio *bio)
{
#if 0
    int zone;
    zone = bio->bi_iter.bi_sector;
    zone /= LBA_ZONE_SIZE;
    if (zone >= MAX_LBA_ZONES-1) zone = MAX_LBA_ZONES-1;
    mdt->lba_heat_buckets[zone]++; // in mega-sector zones
#endif
    return 0;
}

static int format_lba(struct my_dm_target *mdt)
{
#if 0
    int i;
    printk("ht: ");
    for (i = 0; i < MAX_LBA_ZONES; i++) {
        printk("%04lu ", mdt->lba_heat_buckets[i]);
    }
    printk("\n");
#endif
    return 0;
}

static ssize_t format_io(struct my_dm_target *mdt, char *buf)
{
    int i, sz;
    ssize_t size = 0;
    for (i = 0; i < 10; i++) {
        printk("%9s ", buckets[i]);
    }
    printk("\n");
    for (i = 0; i < 10; i++) {
        printk("%9s ", lines[i]);
    }
    printk("\n");
#if 0
    printk("rd: ");
    for (i = 0; i < 10; i++) {
        printk("%8lu  ", mdt->rd_buckets[i]);
    }
    printk("\n");
    printk("wr: ");
    for (i = 0; i < 10; i++) {
        printk("%8lu  ", mdt->wr_buckets[i]);
    }
    printk("\n");
    printk("tm: ");
    for (i = 0; i < 10; i++) {
        printk("%8lu  ", mdt->latency_heat_buckets[i]);
    }
    printk("\n");
#endif
    printk("iops: ");
    for (i = 0; i < MAX_LBA_ZONES; i++) {
        printk("%04lu ", mdt->zone_iops[i]);
        if (i < MAX_LBA_ZONES-1) {
            sz = sprintf(buf, "%d,%lu:", i, mdt->zone_iops[i]);
        } else {
            sz = sprintf(buf, "%d,%lu", i, mdt->zone_iops[i]);
        }
        buf += sz;
        size += sz;
    }
    printk("\n");
    return size;
}

static int add_io(struct my_dm_target *mdt, struct bio *bio)
{
    int is_wr = bio_is_rw(bio); // write is true
    int bucket = 9;
    unsigned long size; // = bio->bi_size;

    size = get_size(bio);
    bucket = get_bucket(size);

    //printk("add_io: size %lu, bucket %u\n", size, bucket);

    if (is_wr) {
        mdt->wr_buckets[bucket]++;
    } else {
        mdt->rd_buckets[bucket]++;
    }

    return 0;
}

static void my_timer_callback(unsigned long data)
{
    struct my_dm_target *mdt = (struct my_dm_target *) data;
    unsigned long delta_time;
    unsigned long sample, avg;
    int i;
    mdt->jiffies_stop = jiffies;
    delta_time = mdt->jiffies_stop - mdt->jiffies_start;
    delta_time /= HZ;
    printk("got timer callback for %s (%lu) secs\n", mdt->name, delta_time);
    for (i = 0; i < MAX_LBA_ZONES; i++) {
        sample = mdt->zone_accum[i] / delta_time;
        avg = cal_running_avg(mdt->zone_iops[i], sample); 
        printk("sample: (%lu) iops: (%lu)\n", sample, avg);
        mdt->zone_iops[i] = avg; 
        mdt->zone_accum[i] = 0;
    }
    if (mdt->started) my_start_timer(mdt);
}

static void end_io_handler(struct bio *clone, int err)
{
    struct my_context *context = clone->bi_private;
    struct bio *bio_src;
    //printk("end_io_handler: err %d\n", err);
    if (context) {
        bio_src = context->bio;
        add_latency_heat(context->mdt, clone);
        add_lba_heat(context->mdt, clone);
        bio_put(clone);
        bio_endio(bio_src, err);
        kfree(context);
    } else {
        printk("end_io_handler: no context - err %d\n", err);
    }
}

static struct bio *new_bio(struct my_dm_target *mdt, struct bio *bio_src)
{
    struct bio *bio = bio_clone(bio_src, GFP_KERNEL);
    struct my_context *context;
    unsigned long size;
    
    context = kzalloc(sizeof(*context), GFP_KERNEL);
    if (context == NULL) {
        return bio_src;
    }

    size = get_size(bio_src);
    context->size = size;
    context->mdt = mdt;
    context->bio = bio_src;
    context->start = jiffies;
    getrawmonotonic(&context->time);
    bio->bi_end_io = end_io_handler;
    bio->bi_private = context;
    bio->bi_bdev = mdt->dev->bdev;
    return bio;
}
/*
 *  Param : 
 *  ti : It is the dm_target structure representing our basic target
 *  bio : The block I/O request from upper layer
 *  map_context : Its mapping context of target.
 *
 *: Return values from target map function:
 *  DM_MAPIO_SUBMITTED :  Your target has submitted the bio request to underlying request
 *  DM_MAPIO_REMAPPED  :  Bio request is remapped, Device mapper should submit bio.  
 *  DM_MAPIO_REQUEUE   :  Some problem has happened with the mapping of bio, So 
 *                                                re queue the bio request. So the bio will be submitted 
 *                                                to the map function  
 */
//static int my_target_map(struct dm_target *ti, struct bio *bio,union map_info *map_context)
static int my_target_map(struct dm_target *ti, struct bio *bio)
{
        struct my_dm_target *mdt = (struct my_dm_target *) ti->private;
        //struct bio *cloned_bio = NULL;

        bio->bi_bdev = mdt->dev->bdev;
        add_io(mdt, bio);
        add_zone_iops(mdt, bio);
        submit_bio(bio->bi_rw, bio); // pass-through

        //cloned_bio = new_bio(mdt, bio);
        //add_io(mdt, cloned_bio);
        //add_zone_iops(mdt, cloned_bio);
        //submit_bio(cloned_bio->bi_rw, cloned_bio);

        return DM_MAPIO_SUBMITTED;
}

void dump_args(unsigned int argc, char *argv[])
{
    int i;
    for (i = 0; i < argc; ++i) {
        printk("argv[%d] = %s\n", i, argv[i]);
    }
}

/*
 * Called on mapped device add - per device
 */
static int my_target_ctr(struct dm_target *ti,unsigned int argc,char **argv)
{
    struct my_dm_target *mdt;
    unsigned long long start, size;


    if (argc != 3) {
        dump_args(argc, argv);
        printk(KERN_CRIT "\n Invalid no.of arguments.\n");
        ti->error = "Invalid argument count";
        return -EINVAL;
    }

    mdt = kmalloc(sizeof(struct my_dm_target), GFP_KERNEL);
    if(mdt==NULL) {
        printk(KERN_CRIT "\n Mdt is null\n");
        ti->error = "dm-my_target: Cannot allocate linear context";
        return -ENOMEM;
    }       

    if(sscanf(argv[1], "%llu", &start)!=1) {
        ti->error = "dm-my_target: Invalid device sector";
        goto bad;
    }
    if(sscanf(argv[2], "%llu", &size)!=1) {
        ti->error = "dm-my_target: Invalid device size";
        goto bad;
    }

    mdt->start=(sector_t)start;
    mdt->size=(sector_t)size;
    printk(KERN_CRIT "my_target: add device %s, start %zu, size(sectors) %zu\n", argv[0], mdt->start, mdt->size);

    /* dm_get_table_mode 
     * Gives out you the Permissions of device mapper table. 
     * This table is nothing but the table which gets created
     * when we execute dmsetup create. This is one of the
     * Data structure used by device mapper for keeping track of its devices.
     *
     * dm_get_device 
     * The function sets the mdt->dev field to underlying device dev structure.
     */

    if (dm_get_device(ti, argv[0], dm_table_get_mode(ti->table), &mdt->dev)) {
        ti->error = "dm-my_target: Device lookup failed";
        goto bad;
    }

    memset(mdt->name, 0, 256);
    strcpy(mdt->name, argv[0]);
    mdt->ti = ti;
    ti->private = mdt;
    spin_lock(&mdt_list_lock);
    list_add(&mdt->node, &mdt_list);
    spin_unlock(&mdt_list_lock);
    init_timer_on_stack(&mdt->timer);
    mdt->started = 0;
    printk("dm_dev name: %s -> %s\n", mdt->dev->name, mdt->name);


    return 0;

bad:
    kfree(mdt);
    printk(KERN_CRIT "\n>>out function my_target_ctr with error\n");
    return -EINVAL;
}

/*
 * Called on mapped device removal - per device
 */
static void my_target_dtr(struct dm_target *ti)
{
    struct my_dm_target *mdt = (struct my_dm_target *) ti->private;
    printk("my_target: remove device\n");

    spin_lock(&mdt_list_lock);
    list_del(&mdt->node);
    spin_unlock(&mdt_list_lock);

    del_timer(&mdt->timer);
    dm_put_device(ti, mdt->dev);
    kfree(mdt);
}

static struct target_type my_target = {
    
    .name = "mymap",
    .version = {1,0,0},
    .module = THIS_MODULE,
    .ctr = my_target_ctr,
    .dtr = my_target_dtr,
    .map = my_target_map,
};

/*
 * Create a group of attributes so that we can create and destory them all
 * at once.
 */
static int foo;

static int my_start_timer(struct my_dm_target *mdt)
{
    mdt->timer.expires = jiffies + 10*HZ;
    mdt->timer.function = my_timer_callback;
    mdt->timer.data = (unsigned long) mdt;
    mdt->jiffies_start = jiffies;
    mdt->started = 1;
    add_timer(&mdt->timer);
    return 0;
}

static int parse_foo(const char *buf)
{
    struct my_dm_target *mdt = my_get_target(buf);
    curr_mdt = NULL;
    if (mdt) {
        curr_mdt = mdt;
    }
    printk("parse buf: %s -> %p\n", buf, mdt);
    // select dm dev to dump and store in curr_mdt;
    return 0;
}

static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr,
                        char *buf)
{
    //printk("foo spewing: %d\n", foo);
    struct my_dm_target *mdt = curr_mdt;
    ssize_t sz = format_io(mdt, buf);
    //format_lba(mdt);
    return sz;
}

static ssize_t foo_store(struct kobject *kobj, struct kobj_attribute *attr,
                         const char *buf, size_t count)
{
    int i;
    struct my_dm_target *mdt;
    parse_foo(buf); // get the device selected
    mdt = curr_mdt;
    printk("foo: clearing buffers: %d\n", foo);
    if (mdt == NULL) {
        printk("no device mapped...\n");
        goto err_out;
    }
    for (i = 0; i < 10; i++) {
        mdt->rd_buckets[i] = 0;
        mdt->wr_buckets[i] = 0;
    }
    for (i = 0; i < MAX_LATENCY_HEAT_BUCKETS; i++) {
        mdt->latency_heat_buckets[i] = 0; // in microseconds: 0 - 2ms: bucket size = 32us
    }
    for (i = 0; i < MAX_LBA_ZONES;  i++) {
        mdt->lba_heat_buckets[i] = 0;
    }
    for (i = 0; i < MAX_LBA_ZONES; i++) {
        mdt->zone_iops[i] = 0;
        mdt->zone_accum[i] = 0;
    }
    if (mdt->started) {
        mdt->started = 0;
    } else {
        mdt->started = 1;
        mdt->jiffies_start = jiffies;
        my_start_timer(mdt);
    }
err_out:
    return count;
}

static struct kobj_attribute foo_attribute =
        __ATTR_RW(foo);
        //__ATTR(foo, S_IRUGO | S_IWUGO, foo_show, foo_store);
        //__ATTR(foo, 0666, foo_show, foo_store);


static struct attribute *attrs[] = {
        &foo_attribute.attr,
        NULL,   /* need to NULL terminate the list of attributes */
};

/* /sys/kernel/my_mapper  In that directory, 3 files are created:
 * and a file name mgmt
 */
static struct attribute_group attr_group = {
        .attrs = attrs,
};
static struct kobject *my_kobj;

static int create_sysfs(void)
{
    int retval = 0;

    my_kobj = kobject_create_and_add(MY_MAPPER_NAME, kernel_kobj);
    if (!my_kobj)
        return -ENOMEM;

    /* Create the files associated with this kobject */
    retval = sysfs_create_group(my_kobj, &attr_group);
    if (retval)
        kobject_put(my_kobj);

    return retval;

}

static int destroy_sysfs(void)
{
    kobject_put(my_kobj);
    return 0;
}

static int init_my_target(void)
{
    int result;
    create_sysfs();
    result = dm_register_target(&my_target);
    if(result < 0) {
        printk(KERN_CRIT "\n Error in registering target \n");
        destroy_sysfs();
    } else {
        printk("loading my_target\n");
    }
    return result;
}


static void cleanup_my_target(void)
{
    printk("unloading my_target\n");
    destroy_sysfs();
    dm_unregister_target(&my_target);
}

module_init(init_my_target);
module_exit(cleanup_my_target);
MODULE_LICENSE("GPL");
