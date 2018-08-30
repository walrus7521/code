#include <linux/module.h>
#include <linux/init.h>
#include <linux/kmod.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <asm/param.h>
#include <linux/interrupt.h>

struct tasklet_struct tlet;
int loops;

void jit_tasklet_fn(unsigned long arg)
{
    int lp = (int )*(int *)arg;
    printk("tasklet_fn %d\n", lp);
    if (--lp > 0) {
       tasklet_schedule(&tlet);
    }
}

static int __init mytasklet_init(void)
{       
    printk("tasklet_init\n");
    loops = 4;
    tasklet_init(&tlet, jit_tasklet_fn, (void *) &loops);
    tasklet_schedule(&tlet);
    return 0;
}

static void __exit mytasklet_exit(void)
{       
    printk("tasklet_exit\n");
}

module_init(mytasklet_init);
module_exit(mytasklet_exit);
MODULE_LICENSE("GPL");

