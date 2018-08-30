/*
 * kick rbd_add: echo 1 > /sys/bus/rbd/add -- infinite loop??
 *               echo 1 > /sys/bus/rbd/uevent -- not responding
 * https://www.kernel.org/doc/pending/hotplug.txt
 * http://free-electrons.com/doc/udev.pdf
 * http://www.makelinux.net/ldd3/chp-14-sect-4
 * https://www.kernel.org/doc/Documentation/ABI/testing/sysfs-bus-pci
 *
 * Add bus->add to wire in ramdisk block device
 *
 * Add blk-mq
 * https://lwn.net/Articles/552904/
 * https://lwn.net/Articles/552911/
 *
 */

//#include <linux/parser.h>
#include <linux/bsearch.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/blkdev.h>
#include <linux/slab.h>
#include <linux/idr.h>

#define DEV_NAME_LEN    32
#define RBD_DRV_NAME    "rbd"
#define SPACE_SIZE 10*1024*1024
#define SIZE_SECTOR 512
 
static int rbd_major;
static LIST_HEAD(dev_list);

struct rbd_device {
	int			dev_id;		/* blkdev unique id */

	int			major;		/* blkdev assigned major */
	int			minor;
	struct gendisk		*disk;		/* blkdev's gendisk and rq */

	u32			image_format;	/* Either 1 or 2 */
	//struct rbd_client	*rbd_client;

	char			name[DEV_NAME_LEN]; /* blkdev name, e.g. rbd3 */

	spinlock_t		lock;		/* queue, flags, open_count */

	//struct rbd_image_header	header;
	unsigned long		flags;		/* possibly lock protected */
	//struct rbd_spec		*spec;

	char			*header_name;

	//struct ceph_file_layout	layout;

	//struct ceph_osd_event   *watch_event;
	//struct rbd_obj_request	*watch_request;

	//struct rbd_spec		*parent_spec;
	u64			parent_overlap;
	atomic_t		parent_ref;
	struct rbd_device	*parent;

	/* protects updating the header */
	struct rw_semaphore     header_rwsem;

	//struct rbd_mapping	mapping;

	struct list_head	node;

	/* sysfs related */
	struct device		dev;
	unsigned long		open_count;	/* protected by lock */

    struct list_head entry;
    struct request_queue *queue;
    int size;
    int lba_shift;
    u32 max_hw_sectors;
    char *data;
};

// block
static int rbd_open(struct block_device *bdev, fmode_t mode)
{
    return 0;
}

static void rbd_release(struct gendisk *disk, fmode_t mode)
{
}

static int rbd_ioctl(struct block_device *bdev, fmode_t mode,
			unsigned int cmd, unsigned long arg)
{
    return 0;
}

#ifdef CONFIG_COMPAT
static int rbd_compat_ioctl(struct block_device *bdev, fmode_t mode,
				unsigned int cmd, unsigned long arg)
{
	return rbd_ioctl(bdev, mode, cmd, arg);
}
#endif /* CONFIG_COMPAT */

static const struct block_device_operations rbd_bd_ops = {
	.owner			= THIS_MODULE,
	.open			= rbd_open,
	.release		= rbd_release,
	.ioctl			= rbd_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl		= rbd_compat_ioctl,
#endif
};


void write(struct rbd_device *dev, char *buffer, unsigned long sector, int size)
{
    unsigned long offset = sector * SIZE_SECTOR;
    //printk("%s called.\n", __FUNCTION__);
    memcpy(&dev->data[offset], buffer, size);
}

void read(struct rbd_device *dev, char *buffer, unsigned long sector, int size)
{
    unsigned long offset = sector * SIZE_SECTOR;
    //printk("%s called.\n", __FUNCTION__);
    memcpy(buffer, &dev->data[offset], size);
}

static int rd_xfr_bio(struct rbd_device *dev, struct bio *bio)
{
#if 0
    struct bio_vec *bvec, *bvprv = NULL;
    //struct bvec_iter iter;
    int segno;
    char *base_addr = NULL;
    int first = 1, length = 0, nsegs = 0, split_len = bio->bi_iter.bi_size;
    //int first = 1, length = 0, nsegs = 0, split_len = bio->bi_size;
    int psegs = bio_phys_segments(dev->queue, bio);

    if ((bio->bi_rw & REQ_FLUSH) && psegs)
        printk("flusher...\n");

    //printk("psegs %x\n", psegs);
    //printk("bi_iter.bi_size %x\n", bio->bi_iter.bi_size);
    //printk("bi_iter.bi_size %x\n", bio->bi_size);
    //printk("bi_rw           %lx\n", bio->bi_rw);
    if (bio->bi_rw & REQ_DISCARD) printk("discard...\n");
    if ((bio->bi_rw & REQ_FLUSH) && !psegs) printk("no data flusher...\n");
    if (bio->bi_rw & REQ_FUA) printk("requesting FUA...\n");
    if (bio->bi_rw & (REQ_FAILFAST_DEV | REQ_RAHEAD)) printk("lazy reader...\n");
    if (bio->bi_rw & REQ_RAHEAD) printk("prefetcher...\n");
    //printk("sector %lx\n", bio->bi_iter.bi_sector);
    //printk("sector %lx\n", bio->bi_sector);
    base_addr = bio_data(bio);
    //printk("base address %p\n", base_addr);

    bio_for_each_segment(bvec, bio, segno) {
        //if (!first && BIOVEC_PHYS_MERGEABLE(bvprv, bvec)) {
        //    length += bvec->bv_len;
        //} else {
            if (!first && BIOVEC_NOT_VIRT_MERGEABLE(bvprv, bvec)) {
                //printk("need to split ...\n");
                break;
            }
      		//printk("bvec.bv_page.mapping %p, bvec.bv_len %x bvec.bv_offset %x\n", 
            //      			bvec->bv_page->mapping, bvec->bv_len, bvec->bv_offset);

            nsegs++;
        //}
        if (split_len - length < bvec->bv_len) {
            //printk("need to split again ...\n");
            break;
        }
        length += bvec->bv_len;
        bvprv = bvec;
        first = 0;
    }
    //printk("length %d, split len %d, nsegs %d\n", length, split_len, nsegs);
    if (bio_data_dir(bio)) {
        //printk("writer...\n");
        //write(dev, base_addr, bio->bi_iter.bi_sector, length);
        write(dev, base_addr, bio->bi_sector, length);
    } else {
        //printk("reader...\n");
        //read(dev, base_addr, bio->bi_iter.bi_sector, length);
        read(dev, base_addr, bio->bi_sector, length);
    }
#endif
    return 0;
}

static void rd_make_request(struct request_queue *q, struct bio *bio)
{
    struct rbd_device *dev = q->queuedata;
    int rc;
    //rc = rd_xfr_bio(dev, bio);
    bio_endio(bio, rc);
    return;
}

static int rd_alloc_ns(struct rbd_device *dev, unsigned nsid)
{
    struct gendisk *disk;
    dev->queue = blk_alloc_queue(GFP_KERNEL);
    if (!dev->queue)
        goto out_free_ns;
    dev->queue->queue_flags = QUEUE_FLAG_DEFAULT;
    queue_flag_set_unlocked(QUEUE_FLAG_NOMERGES, dev->queue);
    queue_flag_set_unlocked(QUEUE_FLAG_NONROT, dev->queue);
    blk_queue_make_request(dev->queue, rd_make_request);
    dev->queue->queuedata = dev;
    disk = alloc_disk(0); /* allow up to 4 partitions = 4 minors */
    if (!disk)
        goto out_free_queue;
    dev->dev_id = nsid;
    dev->disk = disk;
    dev->lba_shift = 9; //id->lbaf[lbaf].ds;
    blk_queue_logical_block_size(dev->queue, 1 << dev->lba_shift);
    if (dev->max_hw_sectors)
        blk_queue_max_hw_sectors(dev->queue, dev->max_hw_sectors);
    disk->major = rbd_major;
    disk->first_minor = 0;
    disk->fops = &rbd_bd_ops;
    disk->private_data = dev;
    disk->queue = dev->queue;
    disk->flags = GENHD_FL_EXT_DEVT;
    sprintf(disk->disk_name, "rd%dn%d", 0, nsid);
    set_capacity(disk, SPACE_SIZE / SIZE_SECTOR); // 10Meg
    return 0;
out_free_queue:
    blk_cleanup_queue(dev->queue);
out_free_ns:
    return -1;
}


static ssize_t rbd_add(struct bus_type *bus,
		       const char *buf,
		       size_t count)
{
	struct rbd_device *rbd_dev;
    static int dev_id = 0;
    int rc;

    printk("rbd_add: %s\n", buf);
	rbd_dev = kzalloc(sizeof (*rbd_dev), GFP_KERNEL);
	if (!rbd_dev)
		return count;

	/* Get an id and fill in device name. */
    rbd_dev->dev_id = dev_id++;
   	sprintf(rbd_dev->name, "%s%d", RBD_DRV_NAME, rbd_dev->dev_id);
    rc = register_blkdev(0, rbd_dev->name);
    rbd_dev->size = SPACE_SIZE;
    rbd_dev->data = vmalloc(SPACE_SIZE);
    memset(rbd_dev->data, 0, SPACE_SIZE);
    rc = rd_alloc_ns(rbd_dev, rbd_dev->dev_id);
 
	add_disk(rbd_dev->disk);
    list_add(&rbd_dev->entry, &dev_list);
	return count;
}

static ssize_t rbd_remove(struct bus_type *bus,
			  const char *buf,
			  size_t count)
{
    printk("rbd_remove: %s\n", buf);
	return count;
}

static ssize_t rbd_rescan(struct bus_type *bus, 
                const char *buf,
				size_t count)
{
    printk("rbd_rescan: %s\n", buf);
	return count;
}

static BUS_ATTR(add, S_IWUSR, NULL, rbd_add);
static BUS_ATTR(remove, S_IWUSR, NULL, rbd_remove);
static BUS_ATTR(rescan, (S_IWUSR|S_IWGRP), NULL, rbd_rescan);

static struct attribute *rbd_bus_attrs[] = {
	&bus_attr_add.attr,
	&bus_attr_remove.attr,
	&bus_attr_rescan.attr,
	NULL,
};

static umode_t rbd_bus_is_visible(struct kobject *kobj,
				  struct attribute *attr, int index)
{
    printk("rbd_bus_is_visible: %d\n", attr->mode);
	return attr->mode;
}

static const struct attribute_group rbd_bus_group = {
	.attrs = rbd_bus_attrs,
	.is_visible = rbd_bus_is_visible,
};
__ATTRIBUTE_GROUPS(rbd_bus);

static int rbd_bus_uevent(struct device *dev, struct kobj_uevent_env *env)
{
    printk("rbd_bus_uevent\n");
    return 0;
}

static struct bus_type rbd_bus_type = {
	.name		= "rbd",
	.bus_groups	= rbd_bus_groups,
	.uevent 	= rbd_bus_uevent,
};

static void rbd_root_dev_release(struct device *dev)
{
    printk("rbd_root_dev_release\n");
}

static struct device rbd_root_dev = {
	.init_name =    "rbd",
	.release =      rbd_root_dev_release,
};

// device
static ssize_t rbd_size_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "(none)\n");
}

/*
 * Note this shows the features for whatever's mapped, which is not
 * necessarily the base image.
 */
static ssize_t rbd_features_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "(none)\n");
}

static ssize_t rbd_major_show(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "(none)\n");
}

static ssize_t rbd_minor_show(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "(none)\n");
}

static ssize_t rbd_client_id_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "(none)\n");
}

static ssize_t rbd_pool_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "(unknown)\n");
}

static ssize_t rbd_pool_id_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "(unknown)\n");
}

static ssize_t rbd_name_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "(unknown)\n");
}

static ssize_t rbd_image_id_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "(unknown)\n");
}

/*
 * Shows the name of the currently-mapped snapshot (or
 * RBD_SNAP_HEAD_NAME for the base image).
 */
static ssize_t rbd_snap_show(struct device *dev,
			     struct device_attribute *attr,
			     char *buf)
{
	return sprintf(buf, "(unknown)\n");
}

/*
 * For a v2 image, shows the chain of parent images, separated by empty
 * lines.  For v1 images or if there is no parent, shows "(no parent
 * image)".
 */
static ssize_t rbd_parent_show(struct device *dev,
			       struct device_attribute *attr,
			       char *buf)
{
	return sprintf(buf, "(unknown)\n");
}

static ssize_t rbd_image_refresh(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf,
				 size_t size)
{
	return size;
}

static DEVICE_ATTR(size, S_IRUGO, rbd_size_show, NULL);
static DEVICE_ATTR(features, S_IRUGO, rbd_features_show, NULL);
static DEVICE_ATTR(major, S_IRUGO, rbd_major_show, NULL);
static DEVICE_ATTR(minor, S_IRUGO, rbd_minor_show, NULL);
static DEVICE_ATTR(client_id, S_IRUGO, rbd_client_id_show, NULL);
static DEVICE_ATTR(pool, S_IRUGO, rbd_pool_show, NULL);
static DEVICE_ATTR(pool_id, S_IRUGO, rbd_pool_id_show, NULL);
static DEVICE_ATTR(name, S_IRUGO, rbd_name_show, NULL);
static DEVICE_ATTR(image_id, S_IRUGO, rbd_image_id_show, NULL);
static DEVICE_ATTR(refresh, S_IWUSR, NULL, rbd_image_refresh);
static DEVICE_ATTR(current_snap, S_IRUGO, rbd_snap_show, NULL);
static DEVICE_ATTR(parent, S_IRUGO, rbd_parent_show, NULL);

static struct attribute *rbd_attrs[] = {
	&dev_attr_size.attr,
	&dev_attr_features.attr,
	&dev_attr_major.attr,
	&dev_attr_minor.attr,
	&dev_attr_client_id.attr,
	&dev_attr_pool.attr,
	&dev_attr_pool_id.attr,
	&dev_attr_name.attr,
	&dev_attr_image_id.attr,
	&dev_attr_current_snap.attr,
	&dev_attr_parent.attr,
	&dev_attr_refresh.attr,
	NULL
};

static struct attribute_group rbd_attr_group = {
	.attrs = rbd_attrs,
};

static const struct attribute_group *rbd_attr_groups[] = {
	&rbd_attr_group,
	NULL
};

static void rbd_sysfs_dev_release(struct device *dev)
{
}

static struct device_type rbd_device_type = {
	.name		= "rbd",
	.groups		= rbd_attr_groups,
	.release	= rbd_sysfs_dev_release,
};

static int rbd_bus_add_dev(struct rbd_device *rbd_dev)
{
	struct device *dev;
	int ret;

	dev = &rbd_dev->dev;
	dev->bus = &rbd_bus_type;
	dev->type = &rbd_device_type;
	dev->parent = &rbd_root_dev;
	//dev->release = rbd_dev_device_release;
	dev_set_name(dev, "%d", rbd_dev->dev_id);
	ret = device_register(dev);

	return ret;
}


/*
 * create control files in sysfs
 * /sys/bus/rbd/...
 */
static int rbd_sysfs_init(void)
{
	int ret;

	ret = device_register(&rbd_root_dev);
	if (ret < 0)
		return ret;

	ret = bus_register(&rbd_bus_type);
	if (ret < 0)
		device_unregister(&rbd_root_dev);

	return ret;
}

static void rbd_sysfs_cleanup(void)
{
	bus_unregister(&rbd_bus_type);
	device_unregister(&rbd_root_dev);
}

static int __init myrbd_init(void)
{       
    printk("myrbd_init..\n");
    rbd_sysfs_init();
    return 0;
}

static void __exit myrbd_exit(void)
{       
    rbd_sysfs_cleanup();
    printk("myrbd_exit..\n");
}

module_init(myrbd_init);
module_exit(myrbd_exit);
MODULE_LICENSE("GPL");

