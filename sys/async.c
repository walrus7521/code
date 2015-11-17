#include <linux/bio.h>
#include <linux/bitops.h>
#include <linux/blkdev.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/genhd.h>
#include <linux/idr.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/kdev_t.h>
#include <linux/kthread.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/pci.h>
#include <linux/poison.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/types.h>
#include "common.h"
#include <asm-generic/io-64-nonatomic-lo-hi.h>

#define MAX_DEVS 32

static int gen_major;
module_param(gen_major, int, 0);
static int gen_char_major;
static struct class *gen_char_cl;
static struct task_struct *wq_thread;

__u32 pci_config[64];

static DEFINE_SPINLOCK(dev_list_lock);
static LIST_HEAD(dev_list);

static DEFINE_MUTEX(task_mutex);
static LIST_HEAD(task_q);

/* 
 * evil global pointer to dev
 * only used in the char device interface
 */
struct gen_dev *g_gen = NULL;

/*
 * Represents a gen device.  Each gen_dev is a PCI function.
 */
struct gen_dev {
    struct list_head node;
    wait_queue_head_t wq;
    wait_queue_t wqe;
    struct fasync_struct *async_queue; /* asynchronous readers */
    int nreaders, nwriters;            /* number of openings for r/w */
    int flags;
    int instance;
    u64 timeout;
    struct list_head namespaces;
};

static int wq_kthread(void *data)
{
    struct gen_dev *dev = (struct gen_dev*) g_gen;
    int count = 0;
    while (!kthread_should_stop()) {
        __set_current_state(TASK_RUNNING);
        printk("wq_kthread iterates [%d]!\n", ++count);
        if (dev->flags) {
            printk("found %d waiter(s) in queue.. setting them all free...\n", dev->flags);
            dev->flags = 0;
            //wake_up(&dev->wq);
            remove_wait_queue(&dev->wq, &dev->wqe);
        }
        __set_current_state(TASK_INTERRUPTIBLE);
        //schedule_timeout(10*HZ);
        schedule();
    }
    return 0;
}
        
typedef void (*completion_fn)(struct gen_dev *, void *,
        void *);

/* XXX: Use an ida or something to let remove / add work correctly */
static void gen_set_instance(struct gen_dev *dev)
{
    static int instance;
    dev->instance = instance++;
}
 
void report(struct gen_dev *dev, struct genu_cmd *cmd,
        int status, int data, int debug)
{
    printk("report_err: status %d, data %d, line %d\n", 
            status, data, debug);
    cmd->status = status;
    cmd->data = data;
    cmd->debug = debug;
}

static long gen_char_ioctl(struct file *f, unsigned int cmd, 
        unsigned long arg)
{
    struct gen_dev *dev = (struct gen_dev*) g_gen;
    int instance = 0; //iminor(f->f_dentry->d_inode);
    int ret = 0;
    struct genu_cmd *pcmd = (struct genu_cmd *) arg, genucmdo;
    printk("gen_char_ioctl - enter: cmd %x inst %d\n", cmd, instance);
    switch (cmd) {
        case GENU_IOCTL_PASS_THROUGH:
            switch (pcmd->op) {
                case genu_get_pci_cfg:
                    printk("genu_get_pci_cfg\n");
                    memcpy(&genucmdo.pci, &pci_config, 256);
                    ret = 0;
                    if (copy_to_user(pcmd, &genucmdo, 
                                sizeof(struct genu_cmd))) {
                        printk("genu_get_pci_cfg copy_to_user failed \n");
                        ret=-EFAULT;
                    }
                    break;
                case genu_add_wait:
                    printk("genu_add_wait\n");
                    //if (dev->flags) {
                    //    wait_event_interruptible(dev->wq, (dev->flags == 0));
                    //} else {
                    dev->flags++;
                    add_wait_queue(&dev->wq, &dev->wqe);
                    //}
                    break;
                case genu_wakeup:
                    printk("genu_wakeup\n");
                    wake_up_process(wq_thread);
                    break;
                case genu_start_wait:
                    printk("genu_start_wait\n");
                    dev->flags = 0;
                    wait_event_interruptible(dev->wq, dev->flags != 0);
                    printk("genu_start_wait - complete!!\n");
                    break;
                case genu_satisfy_wait:
                    printk("genu_satisfy_wait\n");
                    dev->flags = 1;
                    wake_up_interruptible(&dev->wq);
                    break;
                case genu_send_signal:
                    printk("genu_send_signal\n");
                    if (dev->async_queue)
                        kill_fasync(&dev->async_queue, SIGIO, POLL_IN);
                    break;
                 
            }
            break;
        default:
            ret = -EINVAL; /* or -ENOTTY */
            break;
    }
    return ret;
}

static unsigned int gen_char_poll (struct file * file, poll_table * wait)
{
    unsigned int mask = 0;
    mask |= POLLIN | POLLRDNORM | POLLOUT | POLLWRNORM;
    printk("gen_char_poll - enter\n");
    return mask;
}

static unsigned int gen_char_fasync(int fd, struct file *file, int mode)
{
    struct gen_dev *dev = (struct gen_dev*) g_gen;
    printk("fasync called...\n");
    return fasync_helper(fd, file, mode, &dev->async_queue);
}

#if 0
static unsigned int gen_char_fsync(struct file *file, loff_t start, loff_t end, int datasync)
{
    return 0;
}
#endif

static int gen_char_open(struct inode *inode, struct file *filp)
{
    struct gen_dev *dev = (struct gen_dev*) g_gen;
    printk("gen_char_open called...\n");
    //dev = container_of(inode->i_cdev, struct gen_dev, cdev);
    filp->private_data = dev;
    /* use f_mode,not  f_flags: it's cleaner (fs/open.c tells why) */
    if (filp->f_mode & FMODE_READ)
        dev->nreaders++;
    if (filp->f_mode & FMODE_WRITE)
        dev->nwriters++;
    return 0;
}

static int gen_char_release(struct inode *inode, struct file *filp)
{
    struct gen_dev *dev = filp->private_data;
    /* remove this filp from the asynchronously notified filp's */
    gen_char_fasync(-1, filp, 0);
    if (filp->f_mode & FMODE_READ)
        dev->nreaders--;
    if (filp->f_mode & FMODE_WRITE)
        dev->nwriters--;
    if (dev->nreaders + dev->nwriters == 0) {
        printk("gen_char_release - no more readers and writers\n");
    }
    return 0;
}

static const struct file_operations gen_char_fops = {
    .owner          = THIS_MODULE,
    .unlocked_ioctl = gen_char_ioctl,
    .compat_ioctl   = gen_char_ioctl,
    .fasync         = gen_char_fasync,
    .poll           = gen_char_poll,
    .open           = gen_char_open,
    .release        = gen_char_release,
};

static int create_device(void)
{
    struct gen_dev *dev;
 
    dev = kzalloc(sizeof(*dev), GFP_KERNEL);
    if (!dev)
        return -ENOMEM;

    /*
     * create global alias for char ioctl functionality
     */
    g_gen = dev;
    dev->flags = 0;
    init_waitqueue_head(&dev->wq);
    init_waitqueue_entry(&dev->wqe, wq_thread);
    device_create(gen_char_cl, NULL, MKDEV(gen_char_major, 0), 
            dev, "gen%d", 0);

    spin_lock(&dev_list_lock);
    list_add(&dev->node, &dev_list);
    spin_unlock(&dev_list_lock);

    gen_set_instance(dev);
    
    wq_thread = kthread_run(wq_kthread, NULL, "nvme");
    if (IS_ERR(wq_thread))
        return PTR_ERR(wq_thread);

    printk("gen-kd: probed !! yay!\n");
    return 0;
 
}
 
static int __init gen_init(void)
{
    int result = -EBUSY;
 
    result = __register_chrdev(gen_char_major, 0, MAX_DEVS,
           "gen", &gen_char_fops);

    if (result < 0 )
        goto unregister_chrdev;
    else if (result > 0)
        gen_char_major = result;

    gen_char_cl = class_create(THIS_MODULE, "gen");
    if (!gen_char_cl) 
        goto destroy_class;

    result = create_device();
    return 0;
 
destroy_class:
    class_destroy(gen_char_cl);
unregister_chrdev:
    __unregister_chrdev(gen_char_major, 0, MAX_DEVS, "gen");
    return result;
}
 
static void __exit gen_exit(void)
{
    kthread_stop(wq_thread);
    device_destroy(gen_char_cl, MKDEV(gen_char_major, 0));
    class_destroy(gen_char_cl);
    __unregister_chrdev(gen_char_major, 0, MAX_DEVS, "gen");
    kfree(g_gen);
    printk("gen-kd: bye!!\n");
}
 
MODULE_LICENSE("GPL");
MODULE_VERSION("0.8");
module_init(gen_init);
module_exit(gen_exit);
 
