#include <linux/bitops.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/idr.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/kdev_t.h>
#include <linux/kthread.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define NUM_CMOS_BANKS          2
#define CMOS_BANK_SIZE          (0xFF*8)
#define DEVICE_NAME             "cmos"
#define CMOS_BANK0_INDEX_PORT   0x70
#define CMOS_BANK0_DATA_PORT    0x71
#define CMOS_BANK1_INDEX_PORT   0x72
#define CMOS_BANK1_DATA_PORT    0x73

unsigned char addrports[] = {CMOS_BANK0_INDEX_PORT,
                             CMOS_BANK1_INDEX_PORT,};

unsigned char dataports[] = {CMOS_BANK0_DATA_PORT,
                             CMOS_BANK1_DATA_PORT,};

static dev_t cmos_dev_number;
struct class *cmos_class = NULL;


struct cmos_dev {
    unsigned short current_pointer;
    unsigned int size;
    int bank_number;
    struct cdev cdev;
    char name[10];
} *cmos_devp[NUM_CMOS_BANKS];

int cmos_open(struct inode *inode, struct file *file)
{
    struct cmos_dev *cmos_devp;
    cmos_devp = container_of(inode->i_cdev, struct cmos_dev, cdev);
    file->private_data = cmos_devp;
    cmos_devp->size = CMOS_BANK_SIZE;
    cmos_devp->current_pointer = 0;

    printk("cmos_open...\n");
    return 0;
}

int cmos_release(struct inode *inode, struct file *file)
{
    struct cmos_dev *cmos_devp = file->private_data;
    cmos_devp->current_pointer = 0;
    printk("cmos_release...\n");
    return 0;
}

static ssize_t cmos_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
    struct cmos_dev *cmos_devp = file->private_data;
    char data[CMOS_BANK_SIZE];
    int xferred = 0, i = 0;
    int start_byte = cmos_devp->current_pointer/8;

    printk("cmos_read...\n");

    if (cmos_devp->current_pointer >= cmos_devp->size) {
        return 0; /* EOF */
    }

    if (cmos_devp->current_pointer + count > cmos_devp->size) {
        count = cmos_devp->size - cmos_devp->current_pointer;
    }

    while (xferred < count) {
        data[i] = 'A'+i;
        xferred += 1;
        start_byte++;
        i++;
    }

    if (!xferred) return -EIO;

    if (copy_to_user(buf, (void *)data, ((xferred/8)+1)) != 0) {
        return -EIO;
    }
    
    cmos_devp->current_pointer += xferred;
    return xferred;
}

static ssize_t cmos_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    struct cmos_dev *cmos_devp = file->private_data;
    int xferred = count;
    char *kbuf;

    kbuf = kzalloc(count, GFP_KERNEL);
    if (!kbuf) return -ENOMEM;

    if (copy_from_user(kbuf, buf, count)) {
        kfree(kbuf);
        return -EFAULT;
    }

    printk("cmos write: %s\n", kbuf);
    kfree(kbuf);
    cmos_devp->current_pointer += xferred;


    return xferred;
}

#if 0
struct file_operations {
    struct module *owner;
    loff_t (*llseek) (struct file *, loff_t, int);
    ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
    ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
    ssize_t (*read_iter) (struct kiocb *, struct iov_iter *);
    ssize_t (*write_iter) (struct kiocb *, struct iov_iter *);
    int (*iterate) (struct file *, struct dir_context *);
    unsigned int (*poll) (struct file *, struct poll_table_struct *);
    long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
    long (*compat_ioctl) (struct file *, unsigned int, unsigned long);
    int (*mmap) (struct file *, struct vm_area_struct *);
    int (*mremap)(struct file *, struct vm_area_struct *);
    int (*open) (struct inode *, struct file *);
    int (*flush) (struct file *, fl_owner_t id);
    int (*release) (struct inode *, struct file *);
    int (*fsync) (struct file *, loff_t, loff_t, int datasync);
    int (*aio_fsync) (struct kiocb *, int datasync);
    int (*fasync) (int, struct file *, int);
    int (*lock) (struct file *, int, struct file_lock *);
    ssize_t (*sendpage) (struct file *, struct page *, int, size_t, loff_t *, int);
    unsigned long (*get_unmapped_area)(struct file *, unsigned long, unsigned long, unsigned long, unsigned long);
    int (*check_flags)(int);
    int (*flock) (struct file *, int, struct file_lock *);
    ssize_t (*splice_write)(struct pipe_inode_info *, struct file *, loff_t *, size_t, unsigned int);
    ssize_t (*splice_read)(struct file *, loff_t *, struct pipe_inode_info *, size_t, unsigned int);
    int (*setlease)(struct file *, long, struct file_lock **, void **);
    long (*fallocate)(struct file *file, int mode, loff_t offset, loff_t len);
    void (*show_fdinfo)(struct seq_file *m, struct file *f);
#ifndef CONFIG_MMU
    unsigned (*mmap_capabilities)(struct file *);
#endif
};
#endif

static struct file_operations cmos_fops = {
    .owner      = THIS_MODULE,
    .open       = cmos_open,
    .release    = cmos_release,
    .read       = cmos_read,
    .write      = cmos_write,
    //.read_iter  = cmos_read_iter,
    //.write_iter = cmos_write_iter,
    //.llseek     = cmos_llseek,
    //.ioctl      = cmos_ioctl,
    //.mmap       = cmos_mmap,
};

static int __init cmos_init(void)
{
    int i, ret;
    if (alloc_chrdev_region(&cmos_dev_number, 0,
                            NUM_CMOS_BANKS, DEVICE_NAME) < 0) {
        printk(KERN_DEBUG "Can't register device\n");
        return -1;
    }
    printk("cmos major = %x\n", cmos_dev_number);

    cmos_class = class_create(THIS_MODULE, DEVICE_NAME);

    for (i = 0; i < NUM_CMOS_BANKS; i++) {
        cmos_devp[i] = kmalloc(sizeof(struct cmos_dev), GFP_KERNEL);
        if (!cmos_devp[i]) {
            printk("Bad kmalloc\n");
            ret = -ENOMEM;
            goto err_out;
        }

        /* request I/O region */
        sprintf(cmos_devp[i]->name, "cmos%d", i);
        //if (!(request_region(addrports[i], 2, cmos_devp[i]->name))) {
        //    printk("cmos: I/O port 0x%x is not free\n", addrports[i]);
        //    ret = -EIO;
        //    goto err_out;
        //}

        /* fill in the bank number to correlate the device with the BANK */
        cmos_devp[i]->bank_number = i;

        cdev_init(&cmos_devp[i]->cdev, &cmos_fops);
        cmos_devp[i]->cdev.owner = THIS_MODULE;

        ret = cdev_add(&cmos_devp[i]->cdev, (cmos_dev_number + i), 1);
        if (ret) {
            printk("bad cdev..\n");
            goto err_out;
        }

        device_create(cmos_class, NULL, MKDEV(MAJOR(cmos_dev_number), i), NULL, "cmos%d", i);

    }
    printk("cmos: initialized!!\n");
    /* root@bart-dev:/home/bart/src/cmos# ll /sys/class/cmos/
     * lrwxrwxrwx  1 root root 0 Oct 13 14:08 cmos0 -> ../../devices/virtual/cmos/cmos0/
     * lrwxrwxrwx  1 root root 0 Oct 13 14:08 cmos1 -> ../../devices/virtual/cmos/cmos1/
     *
     * root@bart-dev:/home/bart/src/cmos# ll /dev/cmos0 
     * crw------- 1 root root 241, 0 Oct 13 14:08 /dev/cmos0
     * root@bart-dev:/home/bart/src/cmos# ll /dev/cmos1
     * crw------- 1 root root 241, 1 Oct 13 14:08 /dev/cmos1
     */

    return 0;

err_out:
    printk("cmos: failed to initialized!!\n");
    if (cmos_class) {
        class_destroy(cmos_class);
    }

    return ret;
}
 
static void __exit cmos_cleanup(void)
{
    int i;
    unregister_chrdev_region((cmos_dev_number), NUM_CMOS_BANKS);

    /* release I/O region */
    if (cmos_class) {
        printk("cmos: releasing class resources\n");
        for (i = 0; i < NUM_CMOS_BANKS; i++) {
            device_destroy(cmos_class, MKDEV(MAJOR(cmos_dev_number), i));
            //release_region(addrports[i], 2);
            cdev_del(&cmos_devp[i]->cdev);
            kfree(cmos_devp[i]);
        }
        class_destroy(cmos_class);
    }
    printk("cmos: bye!!\n");
}
 
MODULE_LICENSE("GPL");
MODULE_VERSION("0.8");
module_init(cmos_init);
module_exit(cmos_cleanup);
