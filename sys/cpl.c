#include <linux/bio.h>
#include <linux/bitops.h>
#include <linux/blkdev.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/fs.h>
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
#include "cpl.h"
#include <asm-generic/io-64-nonatomic-lo-hi.h>

#define CPL_MAX_DEVS   (32)

static int cpl_major;
module_param(cpl_major, int, 0);
static int cpl_char_major;
static struct class *cpl_char_cl;

static DEFINE_MUTEX(task_mutex);
static LIST_HEAD(task_q);
static struct task_struct *cpl_task_thread; /* task queue */
struct task_info {
    struct completion task_wait;
    struct task_struct *task;
    int busy;
    int tid;
    struct list_head task_list;
    struct cpl_dev *dev;
    struct cplu_cmd cmd;
};

static DEFINE_SPINLOCK(dev_list_lock);
static LIST_HEAD(dev_list);

struct cpl_dev {
    struct list_head node;
    int instance;
    struct list_head namespaces;
};

struct cpl_dev *g_cpl = NULL;

#define QUEUE_TIMEOUT 10
static int task_queue_thread(void *data)
{
    struct task_info *h = NULL;
    struct cplu_cmd *cmd;
    int busy;

    printk("enter - task_queue_thread\n");
    busy = 0;
    while (1) {
        set_current_state(TASK_INTERRUPTIBLE);
        schedule();
        if (kthread_should_stop())
            break;

        while (1) {
            printk("wait for task_mutex\n");
            mutex_lock(&task_mutex);
            printk("got task_mutex\n");
            if (list_empty(&task_q)) {
                mutex_unlock(&task_mutex);
                break;
            }
            if (busy) {
                printk("busy wait..\n");
                mutex_unlock(&task_mutex);
                break;
            }
            h = list_entry(task_q.next, struct task_info, task_list);
            if (NULL == h) {
                mutex_unlock(&task_mutex);
                break;
            }
            //printk("task %d op %d received\n", h->tid, h->cmd.op);
            list_del(&h->task_list);
            busy = 1;
            h->task = current;
            cmd = &h->cmd;
            mutex_unlock(&task_mutex);

            switch (h->cmd.op) {
                case cplu_test_queue:
                    printk("cplu_test_queue\n");
                    complete(&h->task_wait);
                    printk("cplu_test_queue - done!\n");
                    break;
                default:
                    printk("unknown command - done!\n");
                    complete(&h->task_wait);
                    break;
            }
            mutex_lock(&task_mutex);
            busy = 0;
            mutex_unlock(&task_mutex);
        }
    }
    return 0;
}

int cpl_enqueue_task(struct cpl_dev *dev, struct cplu_cmd *cplucmd)
/* locks: only uses task_mutex */
{
    struct task_info *task;
    int ret = 0;
    static int taskid = 0;
    if (taskid >= 1024) taskid = 0;
    task = kzalloc(sizeof(struct task_info), GFP_KERNEL);
    if (!task) {
        ret = -5;
        return ret;
    }
    task->dev = dev;
    task->tid = ++taskid;
    memcpy(&task->cmd, cplucmd, sizeof(struct cplu_cmd));
    init_completion(&task->task_wait);
    mutex_lock(&task_mutex);
    list_add_tail(&task->task_list, &task_q);
    printk("task %d op %d has been queued\n", task->tid, cplucmd->op);
    mutex_unlock(&task_mutex);
    wake_up_process(cpl_task_thread);
    wait_for_completion(&task->task_wait);
    printk("task %d op %d complete\n", task->tid, cplucmd->op);
    kfree(task);
    return ret;
}

static long cpl_char_ioctl(struct file *f, unsigned int cmd, 
        unsigned long arg)
{
    struct cpl_dev *dev = (struct cpl_dev*) g_cpl;
    int instance = 0; //iminor(f->f_dentry->d_inode);
    int ret = 0;
    struct cplu_cmd *pcmd = (struct cplu_cmd *) arg;
    printk("cpl_char_ioctl - enter: cmd %d inst %d\n", cmd, instance);
    switch (cmd) {
        case CPLU_IOCTL_PASS_THROUGH:
            switch (pcmd->op) {
                case cplu_test_queue:
                    ret = cpl_enqueue_task(dev, pcmd);
                    pcmd->status = ret;
                    printk("cplu_queue: op %d, ret %d\n", pcmd->op, ret);
                    break;
            }
            break;
        default:
            ret = -EIO;
            break;
    }
    return ret;
}

static const struct file_operations cpl_char_fops = {
    .owner          = THIS_MODULE,
    .unlocked_ioctl = cpl_char_ioctl,
    .compat_ioctl   = cpl_char_ioctl,
};

static int cpl_create(void)
{
    struct cpl_dev *dev;
 
    dev = kzalloc(sizeof(*dev), GFP_KERNEL);
    if (!dev)
        return -ENOMEM;
    g_cpl = dev;
    device_create(cpl_char_cl, NULL, MKDEV(cpl_char_major, 0), 
            dev, "cpl%d", 0);
    spin_lock(&dev_list_lock);
    list_add(&dev->node, &dev_list);
    spin_unlock(&dev_list_lock);
    printk("cpl-kd: probed !! yay!\n");
    return 0;
}
 
static int __init cpl_init(void)
{
    int result = -EBUSY;
    cpl_task_thread = kthread_run(task_queue_thread, NULL, "cpl_task");
    if (IS_ERR(cpl_task_thread))
        return PTR_ERR(cpl_task_thread);
    result = __register_chrdev(cpl_char_major, 0, CPL_MAX_DEVS,
           "cpl", &cpl_char_fops);
    if (result < 0 )
        goto unregister_chrdev;
    else if (result > 0)
        cpl_char_major = result;
    cpl_char_cl = class_create(THIS_MODULE, "cpl");
    if (!cpl_char_cl) 
        goto destroy_class;
    cpl_create();
    return 0;
destroy_class:
    class_destroy(cpl_char_cl);
unregister_chrdev:
    __unregister_chrdev(cpl_char_major, 0, CPL_MAX_DEVS, "cpl");
    kthread_stop(cpl_task_thread);
    return result;
}
 
static void __exit cpl_exit(void)
{
    struct cpl_dev *dev = g_cpl;
    kthread_stop(cpl_task_thread);
    device_destroy(cpl_char_cl, MKDEV(cpl_char_major, 0));
    kfree(dev);
    class_destroy(cpl_char_cl);
    __unregister_chrdev(cpl_char_major, 0, CPL_MAX_DEVS, "cpl");
    printk("cpl-kd: bye!!\n");
}
 
MODULE_LICENSE("GPL");
MODULE_VERSION("0.8");
module_init(cpl_init);
module_exit(cpl_exit);
 
