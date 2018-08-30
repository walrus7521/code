#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/sched.h>
 
struct task_info {
    struct list_head entry;
    struct completion task_wait;
    struct task_struct *task;
    struct execute_work ew; /* contains struct work_struct work */
    int busy;
    unsigned long timeout;
    struct list_head task_list;
};

static struct workqueue_struct *wq = 0;
 
static void mywork_callback(struct work_struct *work)
{
    unsigned long now;
    unsigned long time_target;
    unsigned long timeout;
    struct task_info *main_task = container_of(work, struct task_info, ew.work);
    //Get the current time and compute timeout
    timeout = main_task->timeout;
    now = jiffies;
    time_target = now + timeout;
    printk("mywork_callback %u jiffies\n", (unsigned) now);
    do {
        msleep(500);
        now = jiffies;
        printk("time now=%ld, time_target=%ld \n", now, time_target);
        if (fatal_signal_pending(current)) {
            printk("get_tag_spin: fatal signal received\n");
            break;
        }
        if (time_after(now, time_target) != 0) {
            printk("get_tag_spin: timed out - 0n%ld secs\n", timeout/HZ);
            break;
        }
    } while (1);
    printk("killed worker...\n");
}
 
static void launch(void)
{
    struct task_info *task;
    task = kzalloc(sizeof(struct task_info), GFP_KERNEL);
    if (!task) {
        return;
    }
    task->timeout =  msecs_to_jiffies(10*1000); // 10 seconds
    init_completion(&task->task_wait);
    INIT_WORK(&task->ew.work, mywork_callback);
    queue_work(wq, &task->ew.work);
 }

static int my_wq_init(void)
{
    pr_info("my_wq_init\n");
    wq = alloc_workqueue("hvt", 0, 0);
    if (!wq) {
        printk("yo wq is hosed!!!\n");
    } else {
        launch();
    }
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

