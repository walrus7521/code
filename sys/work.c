#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>
 
static void mywork_callback(struct work_struct *work);
static struct workqueue_struct *wq = 0;
static DECLARE_DELAYED_WORK(mykmod_work, mywork_callback);
static unsigned long onesec;
 
static void
mywork_callback(struct work_struct *work)
{
    printk("mywork_callback %u jiffies\n", (unsigned)onesec);
}
 
 
static int my_wq_init(void)
{
    onesec = msecs_to_jiffies(1000);
    pr_info("my_wq_init %u jiffies\n", (unsigned)onesec);
    if (!wq)
        wq = create_singlethread_workqueue("my_wq_init");
    if (wq)
        queue_delayed_work(wq, &mykmod_work, onesec);
    return 0;
}
 
static void my_wq_exit(void)
{
    if (wq)
        destroy_workqueue(wq);
    printk("my_wq_exit\n");
}
module_init(my_wq_init);
module_exit(my_wq_exit);
MODULE_DESCRIPTION("mykmod");
MODULE_LICENSE("GPL");

