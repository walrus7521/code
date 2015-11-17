#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/blkdev.h>
#include <linux/buffer_head.h>
#define PARTITION_NAME "/dev/sdb"


char *ptr;
int i;
struct block_device *bd;
make_request_fn *orig_mrqfn;
 
static void filter_mrqfn(struct request_queue *rq, struct bio *b)
{
	printk(KERN_INFO "filter: Sector=lu Size=%d bi_rw=%lu\n", b->bi_sector, b->bi_size, b->bi_rw);

	ptr=(char *)bio_data(b);
	for(i=0;i<b->bi_size;i++)  //4096 as bio is going to be in 4kb chunk?????
	{
	   printk("%c",*ptr);
	   ptr++;
	}


	orig_mrqfn(rq, b); /* calling the original make_request_fn() */
}
 

/*
* set_mrqfn() - Change the original make_request_fn() to our
* modules request function
*/
static void set_mrqfn(void)
{
	struct super_block *sb;
	printk(KERN_DEBUG "filter: %s\n", __FUNCTION__);
	/* lock filesystem to prevent any further changes */
	fsync_bdev(bd);
	sb = freeze_bdev(bd);
	if (bd->bd_disk->queue->make_request_fn == filter_mrqfn) {
		printk(KERN_INFO "filter: modules request function is already active\n");
	} else {
		/* save the pointer to the original make_request_fn() */
		orig_mrqfn = bd->bd_disk->queue->make_request_fn;
		/* replace the original with our modules request function */
		bd->bd_disk->queue->make_request_fn = filter_mrqfn;
	}
	
	/* unlock filesystem */
	thaw_bdev(bd, sb);
}

/*
* restore_mrqfn() - Restore the original make_request_fn()
*/
static void restore_mrqfn(void)
{
	struct super_block *sb = bd->bd_super;
	printk(KERN_DEBUG "filter: %s\n", __FUNCTION__);
	if (orig_mrqfn) {
		/* lock filesystem to prevent any further changes */
		fsync_bdev(bd);
		sb = freeze_bdev(bd);
		/* restore the original request function */
		bd->bd_disk->queue->make_request_fn = orig_mrqfn;
		/* unlock filesystem */
		thaw_bdev(bd, sb);
	}
	orig_mrqfn = NULL;
}

static int __init filter_init(void)
{
	printk(KERN_DEBUG "filter: %s\n", __FUNCTION__);
	orig_mrqfn = NULL;
	// Read block device from path
	bd = blkdev_get_by_path(PARTITION_NAME, FMODE_READ, NULL);
	if (IS_ERR(bd)) {
		printk(KERN_ERR "filter: failed to get block device\n");
		return 0;
	}
	
	printk(KERN_INFO "filter: found block device with major number %d\n", bd->bd_disk->major);
	printk(KERN_INFO "filter: file system block size %d\n", bd->bd_block_size);
	printk(KERN_INFO "filter: start sector %lu\n", (unsigned long)bd->bd_part->start_sect);
	printk(KERN_INFO "filter: number of sectors %lu\n", (unsigned long)bd->bd_part->nr_sects);
	printk(KERN_INFO "filter: logical block size %d\n", bdev_logical_block_size(bd));
	printk(KERN_INFO "filter: physical block size %d\n", bdev_physical_block_size(bd));
	set_mrqfn();
	return 0;
}

static void __exit filter_exit(void)
{
	printk(KERN_DEBUG "filter: %s\n", __FUNCTION__);
	restore_mrqfn();
	if (!IS_ERR(bd)) {
		blkdev_put(bd, FMODE_READ);
	}
}

module_init(filter_init);
module_exit(filter_exit);
MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Me");
