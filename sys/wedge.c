#include <linux/module.h>
#include <linux/init.h>
#include <linux/blkdev.h>

/*
 * Explicit block device plugging:
 *      https://lwn.net/Articles/438256/
 *      https://www.kernel.org/doc/htmldocs/kernel-api/
 *
 * 	blk_delay_queue(queue, delay_in_msecs);
 *  blk_stop_queue()
 *  blk_start_queue()
 *
 *  checkout: ./drivers/md.dm.c
 *  static struct mapped_device *alloc_dev(int minor)
 *  static void cleanup_mapped_device(struct mapped_device *md)
 *
 * struct mapped_device {
 *      struct block_device *bdev;
 *      struct request_queue *queue;
 *      struct gendisk *disk;
 *      struct hd_geometry geometry;
 *      struct bio flush_bio;
 *
 *  md->queue = blk_alloc_queue(GFP_KERNEL);
 *  md->disk = alloc_disk(1);
 *  md->bdev = bdget_disk(md->disk, 0);
 *  bio_init(&md->flush_bio);
 *  md->flush_bio.bi_bdev = md->bdev;
 *  md->flush_bio.bi_rw = WRITE_FLUSH;
 *
 */

char *my_dev = "/dev/sdc";
struct request_queue *queue;
struct request_queue *orig_queue;
struct block_device *bdev = NULL;
dev_t dev;

static void wedge_make_request(struct request_queue *q, struct bio *bio)
{
    //struct rbd_device *dev = q->queuedata;
    int rc = 0;
    //rc = rd_xfr_bio(dev, bio);
    printk("wedge_make_request...\n");
    bio_endio(bio, rc);
    return;
}

static int __init wedge_init(void)
{       
    printk("wedge_init\n");
    bdev = lookup_bdev(my_dev);
    if (bdev) {
        queue = blk_alloc_queue(GFP_KERNEL);
        blk_queue_make_request(queue, wedge_make_request);
        dev = bdev->bd_dev;
        //orig_queue = bdev->bd_queue;
        //bdev->bd_queue = queue;
        //blk_stop_queue(queue);
        //blk_stop_queue(orig_queue);
        orig_queue = bdev->bd_disk->queue;
        bdev->bd_disk->queue = queue;
        //blk_start_queue(queue);
        bdput(bdev);
        printk("got the bdev %x:\n", dev);
        printk("    queue            %p\n", bdev->bd_queue);
        printk("    private          %ld\n", bdev->bd_private);
        printk("    block size       %d\n", bdev->bd_block_size);
        printk("    partition count  %d\n", bdev->bd_part_count);

#if 0
struct block_device {
        dev_t                   bd_dev;  /* not a kdev_t - it's a search key */
        int                     bd_openers;
        struct inode *          bd_inode;       /* will die */
        struct super_block *    bd_super;
        struct mutex            bd_mutex;       /* open/close mutex */
        struct list_head        bd_inodes;
        void *                  bd_claiming;
        void *                  bd_holder;
        int                     bd_holders;
        bool                    bd_write_holder;
#ifdef CONFIG_SYSFS
        struct list_head        bd_holder_disks;
#endif
        struct block_device *   bd_contains;
        unsigned                bd_block_size;
        struct hd_struct *      bd_part;
        /* number of times partitions within this device have been opened. */
        unsigned                bd_part_count;
        int                     bd_invalidated;
        struct gendisk *        bd_disk;
        struct request_queue *  bd_queue;
        struct list_head        bd_list;
        /*
         * Private data.  You must have bd_claim'ed the block_device
         * to use this.  NOTE:  bd_claim allows an owner to claim
         * the same device multiple times, the owner must take special
         * care to not mess up bd_private for that case.
         */
        unsigned long           bd_private;

        /* The counter of freeze processes */
        int                     bd_fsfreeze_count;
        /* Mutex for freeze */
        struct mutex            bd_fsfreeze_mutex;
};
#endif

    }
    return 0;
}

static void __exit wedge_exit(void)
{       
    printk("wedge_exit\n");
    //blk_stop_queue(queue);
    //bdev->bd_queue = orig_queue;
    //blk_start_queue(orig_queue);

    bdev->bd_disk->queue = orig_queue;
    
    blk_cleanup_queue(queue);
}

module_init(wedge_init);
module_exit(wedge_exit);
MODULE_LICENSE("GPL");

