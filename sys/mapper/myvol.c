/*
 * TODO:
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/bio.h>
#include <linux/device-mapper.h>
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/timer.h>
#include <linux/sysfs.h>

#define MY_MAPPER_NAME "my_mapper"

struct my_dm_target {
    struct dm_dev *dev;
    struct block_device *bdev;
    char name[256];
    fmode_t mode;
    sector_t start;
    sector_t size;
};

struct my_context {
    unsigned long start;
    unsigned long size;
    struct bio *bio;
    struct timespec time;
};

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

static void end_io_handler(struct bio *clone, int err)
{
    struct my_context *context = clone->bi_private;
    struct bio *bio_src;
    //printk("end_io_handler: err %d\n", err);
    if (context) {
        bio_src = context->bio;
        bio_put(clone);
        bio_endio(bio_src, err);
    } else {
        printk("end_io_handler: no context - err %d\n", err);
    }
}

static struct bio *new_bio(struct bio *bio_src, struct my_dm_target *mdt)
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
    context->bio = bio_src;
    context->start = jiffies;
    getrawmonotonic(&context->time);
    bio->bi_end_io = end_io_handler;
    bio->bi_private = context;
    //bio->bi_bdev = mdt->dev->bdev;
    bio->bi_bdev = mdt->bdev;
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
        struct bio *cloned_bio = NULL;

        //bio->bi_bdev = mdt->dev->bdev;
        //submit_bio(cbio->bi_rw, bio); // pass-through

        cloned_bio = new_bio(bio, mdt);
        submit_bio(cloned_bio->bi_rw, cloned_bio);

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
    int open_flags;
    struct file *fd;


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
    memset(mdt->name, 0, 256);
    sprintf(mdt->name, "%s", argv[0]);
    printk("start tracking device: %s\n", mdt->name);

    /* dm_get_table_mode 
     * Gives out you the Permissions of device mapper table. 
     * This table is nothing but the table which gets created
     * when we execute dmsetup create. This is one of the
     * Data structure used by device mapper for keeping track of its devices.
     *
     * dm_get_device 
     * The function sets the mdt->dev field to underlying device dev structure.
     */
    open_flags = O_LARGEFILE | O_RDWR | O_DIRECT | O_DSYNC;
    fd = filp_open(argv[0], open_flags, 0600);
    if (IS_ERR(fd)) {
        ti->error = "dm-my_target: file open failed";
        goto bad;
    }
    mdt->bdev = file_inode(fd)->i_bdev;
    mdt->mode = fd->f_mode;
    if (!mdt->bdev) {
        ti->error = "dm-my_target: inode not block device";
        goto bad;
    }
    //if (dm_get_device(ti, argv[0], dm_table_get_mode(ti->table), &mdt->dev)) {
    //    ti->error = "dm-my_target: Device lookup failed";
    //    goto bad;
    //}
    //mdt->bdev = mdt->dev;

    ti->private = mdt;

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
    //dm_put_device(ti, mdt->dev);
    kfree(mdt);
}

static int my_target_ioctl(struct dm_target *ti, unsigned int cmd,
                            unsigned long arg)
{
    struct my_dm_target *mdt = (struct my_dm_target *) ti->private;
    int r = 0;
    printk("my_target_ioctl: cmd=0x%x, arg=0x%x\n", cmd, arg);
    /*
     * Only pass ioctls through if the device sizes match exactly.
     */
    if (ti->len != i_size_read(mdt->bdev->bd_inode) >> SECTOR_SHIFT)
        r = scsi_verify_blk_ioctl(NULL, cmd);

    return r ? : __blkdev_driver_ioctl(mdt->bdev, mdt->mode, cmd, arg);
}

static void my_target_status(struct dm_target *ti, status_type_t type,
                          unsigned status_flags, char *result, unsigned maxlen)
{
    struct my_dm_target *mdt = (struct my_dm_target *) ti->private;

    printk("my_target_status\n");
    switch (type) {
    case STATUSTYPE_INFO:
        result[0] = '\0';
        break;

    case STATUSTYPE_TABLE:
        snprintf(result, maxlen, "%s", mdt->name);
        break;
    }
}

static int my_target_end_io(struct dm_target *ti, struct bio *bio, int error)
{
    //struct my_dm_target *mdt = (struct my_dm_target *) ti->private;
    printk("my_target_end_io\n");
    //if (is_bio_tracked(bio))
    //    stop_tracking_chunk(s, bio);
    return 0;
}

static struct target_type my_target = {
    
    .name = "myvol",
    .version = {1,0,0},
    .module = THIS_MODULE,
    .ctr = my_target_ctr,
    .dtr = my_target_dtr,
    .map = my_target_map,
    .status = my_target_status,
    .ioctl  = my_target_ioctl,
    .end_io = my_target_end_io,
};

/*
 * Create a group of attributes so that we can create and destory them all
 * at once.
 */
static int foo;

static int parse_foo(const char *buf)
{
    sscanf(buf, "%du", &foo);
    return 0;
}

static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr,
                        char *buf)
{
    //printk("foo spewing: %d\n", foo);
    return sprintf(buf, "%d\n", foo);
}

static ssize_t foo_store(struct kobject *kobj, struct kobj_attribute *attr,
                         const char *buf, size_t count)
{
    parse_foo(buf);
    printk("foo: clearing buffers: %d\n", foo);
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
    if(result < 0)
        printk(KERN_CRIT "\n Error in registering target \n");
    else
        printk("loading my_target\n");

    return 0;
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
