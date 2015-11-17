#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <net/sock.h>

struct packet_type my_proto;

int packet_interceptor(struct sk_buff *skb,
    struct net_device *dev,
    struct packet_type *pt,
    struct net_device *orig_dev) {

    printk("packet interceptor ...\n");
    // I dont want certain packets go to upper in net_devices for further processing.
    // How can I drop sk_buff here?!

  return 0;
}

static int hello_init( void ) {
    printk(KERN_INFO "Hello, world!\n");

    my_proto.type = htons(ETH_P_ALL);
    my_proto.dev = NULL;
    my_proto.func = packet_interceptor;

    dev_add_pack(&my_proto);
    return 0;
}    

static void hello_exit(void) {
  dev_remove_pack(&my_proto);
  printk(KERN_INFO "Bye, world\n");
}

module_init(hello_init);
module_exit(hello_exit);
