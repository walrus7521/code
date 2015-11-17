#include <linux/module.h>
#include <linux/init.h>
#include <linux/kmod.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <asm/param.h>

struct timer_list my_timer;
int loops = 4;

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
    printk("timer loops remaining: %d\n", loops);
}

static int __init timer_init(void)
{       
    int delay = 10; /* 10 seconds later */
    printk("timer_init\n");
    init_timer_on_stack(&my_timer);
    my_timer.expires = jiffies + delay * HZ;
    my_timer.data = 0;
    my_timer.function = my_timer_callback;
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

