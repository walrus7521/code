/*
 * Simulate a filter driver using device-mapper.
 * 
 * by Bart Bartel
 */

#include "dm.h"
#include <linux/module.h>
#include <linux/init.h>
#include <linux/blkdev.h>
#include <linux/bio.h>
#include <linux/slab.h>
#include <linux/device-mapper.h>

#define DM_MSG_PREFIX "vlun"
#define DM_MAX_DEVS 8

/*
 * Vlun: maps a range of a device.
 */
struct vlun_c {
    int num_devs;
    //struct dm_dev *dev;
    struct dm_dev *devs[DM_MAX_DEVS];
    //sector_t start;
    sector_t starters[DM_MAX_DEVS];
};

/*
 * Construct a vlun mapping: <dev_path> <offset>
 *                     e.g.: /dev/rd0n0 0
 */
static int vlun_ctr(struct dm_target *ti, unsigned int argc, char **argv)
{
    struct vlun_c *lc;
    //unsigned long long tmp;
    //char dummy;
    int i, num_devs, rc;
    sector_t start;

    printk("%s: called.\n", __FUNCTION__);
    //printk("argc = %d\n", argc);
    //for (i = 0; i < argc; i++) {
    //    printk("argv[%d] = %s\n", i, argv[i]);
    //}
    sscanf(argv[0], "%d", &num_devs);
    printk("num devices: %d\n", num_devs);
    //printk("%s: args %s %s\n", __FUNCTION__, argv[0], argv[1]);

    lc = kmalloc(sizeof(*lc), GFP_KERNEL);
    if (lc == NULL) {
        ti->error = "dm-vlun: Cannot allocate vlun context";
        printk("%s - %s\n", __FUNCTION__, ti->error);
        return -ENOMEM;
    }
    lc->num_devs = num_devs;
    //if (sscanf(argv[1], "%llu%c", &tmp, &dummy) != 1) {
    //    ti->error = "dm-vlun: Invalid device sector";
    //    printk("%s - %s\n", __FUNCTION__, ti->error);
    //    goto bad;
    //}
    //lc->start = tmp;
    /* this fails until we give it a valid device
     * lets use ramdisk: /dev/rd0n0
     */

    for (i = 0; i < lc->num_devs; i++) {
        printk("path: %s, start sector %s\n", argv[(2*i)+1], argv[(2*i)+2]);
        rc = dm_get_device(ti, argv[(2*i)+1], dm_table_get_mode(ti->table), &lc->devs[i]);
        if (rc) {
            ti->error = "dm-vlun: Device lookup failed";
            printk("%s - %s %s\n", __FUNCTION__, ti->error, argv[(2*i)+1]);
        } else {
            printk("%s - success lookup %s\n", __FUNCTION__, argv[(2*i)+1]);
            sscanf(argv[(2*i)+2], "%lu", &start);
            lc->starters[i] = start;
        }
    }

    //if (dm_get_device(ti, argv[0], dm_table_get_mode(ti->table), &lc->dev)) {
    //    ti->error = "dm-vlun: Device lookup failed";
    //    printk("%s - %s\n", __FUNCTION__, ti->error);
    //    goto bad;
    //}
    //printk("%s - successfully got the lc->dev %p\n", __FUNCTION__, lc->dev);
    //ti->num_flush_bios = 1;
    //ti->num_discard_bios = 1;
    //ti->num_write_same_bios = 1;
    ti->private = lc;
    return 0;

//bad:
//    kfree(lc);
//    return -EINVAL;
}

static void vlun_dtr(struct dm_target *ti)
{
    int i;
    struct vlun_c *lc = (struct vlun_c *) ti->private;
    printk("%s: called.\n", __FUNCTION__);
    for (i = 0; i < lc->num_devs; i++) {
        printk("vlun_dtr: dm_put_device[%d]\n", i);
        dm_put_device(ti, lc->devs[i]);
    }
    kfree(lc);

}

static sector_t vlun_map_sector(struct dm_target *ti, sector_t bi_sector)
{
    struct vlun_c *lc = ti->private;
    printk("%s: called.\n", __FUNCTION__);
    return lc->starters[0] + dm_target_offset(ti, bi_sector);
}

static void vlun_map_bio(struct dm_target *ti, struct bio *bio)
{
    struct vlun_c *lc = ti->private;
    printk("%s: called.\n", __FUNCTION__);
    bio->bi_bdev = lc->devs[0]->bdev; /* patch in the new rd dev - sneaky */
    if (bio_sectors(bio))
        bio->bi_sector = vlun_map_sector(ti, bio->bi_sector);
        //bio->bi_iter.bi_sector = vlun_map_sector(ti, bio->bi_iter.bi_sector);
}

static int vlun_map(struct dm_target *ti, struct bio *bio, union map_info *map_context)
{
    printk("%s: called.\n", __FUNCTION__);
    vlun_map_bio(ti, bio);
    return DM_MAPIO_REMAPPED;
}

static void vlun_status(struct dm_target *ti, status_type_t type,
                          char *result, unsigned maxlen)
{
    struct vlun_c *lc = (struct vlun_c *) ti->private;
    printk("%s: called, type %d : ", __FUNCTION__, type);
    switch (type) {
        case STATUSTYPE_INFO:
            result[0] = '\0';
            printk(" STATUSTYPE_INFO.\n");
            break;
        case STATUSTYPE_TABLE:
            snprintf(result, maxlen, "%s %llu", lc->devs[0]->name,
                                (unsigned long long)lc->starters[0]);
            printk(" STATUSTYPE_TABLE.\n");
            break;
        default:
            printk(" STATUSTYPE_UNKNOWN.\n");
            break;
    }
}

static int vlun_ioctl(struct dm_target *ti, unsigned int cmd,
                        unsigned long arg)
{
    struct vlun_c *lc = (struct vlun_c *) ti->private;
    struct dm_dev *dev = lc->devs[0];
    int r = 0;
    printk("%s: called.\n", __FUNCTION__);
    /*
     * Only pass ioctls through if the device sizes match exactly.
     */
    if (lc->starters[0] ||
        ti->len != i_size_read(dev->bdev->bd_inode) >> SECTOR_SHIFT)
            r = scsi_verify_blk_ioctl(NULL, cmd);
    if (r == 0) {
        r = __blkdev_driver_ioctl(dev->bdev, dev->mode, cmd, arg);
        printk("ioctl %d returned %d\n", cmd, r);
    }
    return 0;
}

static int vlun_merge(struct dm_target *ti, struct bvec_merge_data *bvm,
                        struct bio_vec *biovec, int max_size)
{
    struct vlun_c *lc = ti->private;
    struct request_queue *q = bdev_get_queue(lc->devs[0]->bdev);
    printk("%s: called.\n", __FUNCTION__);
    if (!q->merge_bvec_fn)
        return max_size;
    bvm->bi_bdev = lc->devs[0]->bdev;
    bvm->bi_sector = vlun_map_sector(ti, bvm->bi_sector);
    return min(max_size, q->merge_bvec_fn(q, bvm, biovec));
}

static int vlun_iterate_devices(struct dm_target *ti,
                                  iterate_devices_callout_fn fn, void *data)
{
    int i, rc;
    struct vlun_c *lc = ti->private;
    //printk("%s: called. start %lx, len %lx\n", __FUNCTION__, lc->starters[0], ti->len);
    printk("%s: called.\n", __FUNCTION__);

    for (i = 0; i < lc->num_devs; i++) {
        printk("vlun_iterate_devices: calling fn[%d]\n", i);
        rc = fn(ti, lc->devs[i], lc->starters[i], ti->len, data);
        if (rc)
            goto out;
    }
 
out:
	return rc;


}

static struct target_type vlun_target = {
        .name   = "vlun",
        .version = {1, 2, 1},
        .module = THIS_MODULE,
        .ctr    = vlun_ctr,
        .dtr    = vlun_dtr,
        .map    = vlun_map,
        .status = vlun_status,
        .ioctl  = vlun_ioctl,
        .merge  = vlun_merge,
        .iterate_devices = vlun_iterate_devices,
};

int __init dm_vlun_init(void)
{
    int r = dm_register_target(&vlun_target);
    if (r < 0)
        DMERR("register failed %d", r);
    else
        DMINFO("registration success");
    return r;
}

void dm_vlun_exit(void)
{
    DMINFO("unloading");
    dm_unregister_target(&vlun_target);
}

MODULE_LICENSE("GPL");
MODULE_VERSION("0.24");
module_init(dm_vlun_init);
module_exit(dm_vlun_exit);

