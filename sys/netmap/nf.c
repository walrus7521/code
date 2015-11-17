#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

// http://stackoverflow.com/questions/19342252/how-to-filter-and-intercept-linux-packets-by-using-net-dev-add-api
//
// Handler function
static unsigned int my_handler (
    unsigned int hook,
    struct sk_buff *skb,
    const struct net_device *in,
    const struct net_device *out,
    int (*okfn)(struct sk_buff *))
{
    printk("my_handler: hook %d\n", hook);
    return NF_ACCEPT;
// or
    return NF_DROP;
}

// Handler registering struct
static struct nf_hook_ops my_hook __read_mostly = {
    .hook = my_handler,
    .pf = NFPROTO_IPV4,
    .hooknum = (1 << NF_INET_PRE_ROUTING),
    .priority = NF_IP_PRI_FIRST // My hook will be run before any other netfilter hook
};

int my_init(void) {
    int err = nf_register_hook (&my_hook);
    if (err) {
            printk (KERN_ERR "Could not register hook\n");
            return err;
    }
    printk("yo nf...\n");
    return 0;
}

void my_exit(void) {
    printk("bye nf...\n");
    nf_unregister_hook(&my_hook);
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
