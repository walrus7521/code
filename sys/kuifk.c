#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>


static int __init kmode_callout_init(void)
{
    int ret = 0;
    char *argv[] = {"/home/bart/src/repo/utils/sys/callee", "2", NULL };
    char *envp[] = {"HOME=/", "PATH=/sbin:/usr/sbin:/bin:/usr/bin", NULL };

    printk("kmode_callout_init\n");
    /* last parameter: 1 -> wait until execution has finished, 0 go ahead without waiting*/
    /* returns 0 if usermode process was started successfully, errorvalue otherwise*/
    /* no possiblity to get return value of usermode process*/
    ret = call_usermodehelper("/home/bart/src/repo/utils/sys/callee", argv, envp, UMH_WAIT_EXEC);
    if (ret != 0)
        printk("error in call to usermodehelper: %i\n", ret);
    else
        printk("everything all right\n");
    return 0;
}

static void __exit kmode_callout_exit(void)
{
    printk("kmode_callout_exit\n");
}

module_init(kmode_callout_init);
module_exit(kmode_callout_exit);
MODULE_LICENSE("GPL");

