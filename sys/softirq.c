#include <linux/module.h>
#include <linux/init.h>
#include <linux/kmod.h>
#include <linux/slab.h>
#include <linux/interrupt.h>

/*
 * Note: this has not been tested, when loading on my kernel, I get 
 * [261392.760478] mysoftirq: Unknown symbol raise_softirq (err 0)
 * [261392.760511] mysoftirq: Unknown symbol open_softirq (err 0)
 *
 */

static void analyze(struct softirq_action *h)
{
    printk("softirq: analyze\n");
}

static int __init my_softirq_init(void)
{       
    printk("softirq_init\n");
    open_softirq(SCHED_SOFTIRQ, analyze);
    raise_softirq(SCHED_SOFTIRQ);
    return 0;
}

static void __exit my_softirq_exit(void)
{       
    printk("softirq_exit\n");
}

module_init(my_softirq_init);
module_exit(my_softirq_exit);
MODULE_LICENSE("GPL");

