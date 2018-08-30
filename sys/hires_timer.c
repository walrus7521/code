#include <linux/module.h>
#include <linux/init.h>
#include <linux/kmod.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <asm/param.h>
#include <linux/time.h>

#define SEC2NANO 1000000000.0f
struct timer_list my_timer;
int loops = 4;
struct timespec t1, t2;
u64 elapsed_time;

static void my_timer_callback(unsigned long data)
{
    int delay = 10; /* 10 seconds later */
    if (loops > 0) {
        my_timer.expires = jiffies + delay * HZ;
        my_timer.data = 0;
        my_timer.function = my_timer_callback;
        add_timer(&my_timer);        
        --loops;
    }
    getrawmonotonic(&t2);
    elapsed_time = ((t2.tv_sec * SEC2NANO + t2.tv_nsec) -
                    (t1.tv_sec * SEC2NANO + t1.tv_nsec));
    printk("timer loops remaining: %d, %lld\n", loops, elapsed_time);
}

static int __init timer_init(void)
{       
    int delay = 4; /* 10 seconds later */

    printk("timer_init\n");
    init_timer_on_stack(&my_timer);
    my_timer.expires = jiffies + delay * HZ;
    my_timer.data = 0;
    my_timer.function = my_timer_callback;
    getrawmonotonic(&t1);
    add_timer(&my_timer);
    return 0;
}

static void __exit timer_exit(void)
{       
    del_timer(&my_timer);  
    printk("timer_exit\n");
}

module_init(timer_init);
module_exit(timer_exit);
MODULE_LICENSE("GPL");

