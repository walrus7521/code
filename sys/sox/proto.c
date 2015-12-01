#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/skbuff.h>
#include <net/sock.h>
#include <linux/net.h>
#include <net/inet_common.h>

void test_close(struct sock *sk, long timeout) {}
int test_connect(struct sock *sk, struct sockaddr *uaddr, int addr_len) { return 0; }
int test_disconnect(struct sock *sk, int flags) { return 0; }
struct sock* test_accept(struct sock *sk, int flags, int *err) { return NULL; }
int test_ioctl(struct sock *sk, int cmd, unsigned long arg) { return 0; }
int test_init(struct sock *sk) { return 0; }
int test_destroy(struct sock *sk) { return 0; }
void test_shutdown(struct sock *sk, int how) {}
int test_setsockopt(struct sock *sk, int level, int optname, char *optval, int optlen) { return 0; }
int test_getsockopt(struct sock *sk, int level, int optname, char *optval, int *option) { return 0; }
int test_sendmsg(struct kiocb *iocb, struct sock *sk, struct msghdr *msg, size_t len) { return 0; }
int test_recvmsg(struct kiocb *iocb, struct sock *sk, struct msghdr *msg, size_t len, int noblock, int flags, int *addr_len) { return 0; }
int test_sendpage(struct sock *sk, struct page *page, int offset, size_t size, int flags) { return 0; }
int test_bind(struct sock *sk, struct sockaddr *uaddr, int addr_len) { return 0; }
int test_backlog_rcv(struct sock *sk, struct sk_buff *skb) { return 0; }
void test_hash(struct sock *sk) {}
void test_unhash(struct sock *sk) {}
int test_get_port(struct sock *sk, unsigned short snum) { return 0; }

struct proto test_prot =
{
    .name           = "TEST",
    .owner          = THIS_MODULE,
    .close          = test_close,
    .connect        = test_connect,
    .disconnect     = test_disconnect,
    .accept         = test_accept,
    .ioctl          = test_ioctl,
    .init           = test_init,
    //.destroy        = test_destroy,
    .shutdown       = test_shutdown,
    //.setsockopt     = test_setsockopt,
    .getsockopt     = test_getsockopt,
    .sendmsg        = test_sendmsg,
    .recvmsg        = test_recvmsg,
    .backlog_rcv    = test_backlog_rcv,
    .hash           = test_hash,
    .unhash         = test_unhash,
    .get_port       = test_get_port,
};

#define PF_INET_NEW_TCP 0x77
#define AF_INET_NEW_TCP 0x77


static struct proto_ops my_proto_ops = {
    .family = PF_INET,
    .owner = THIS_MODULE,
    .release = inet_release,
    //.bind = my_bind,
    .connect = inet_stream_connect,
    .socketpair = sock_no_socketpair,
    .accept = inet_accept,
    .getname = inet_getname,
    //.poll = my_poll,
    .ioctl = inet_ioctl,
    //.listen = my_inet_listen,
    .shutdown = inet_shutdown,
    .setsockopt = sock_common_setsockopt,
    .getsockopt = sock_common_getsockopt,
    .sendmsg = inet_sendmsg,
    .recvmsg = sock_common_recvmsg,
};


static int my_create_socket(struct net *net, struct socket *sock, int protocol, int kern)
{
    struct sock *sk;
    //int rc;

    sk = sk_alloc(net, PF_INET_NEW_TCP, GFP_KERNEL, &test_prot);
    //sk = sk_alloc(net, PF_INET, GFP_KERNEL, &test_prot);
    if (!sk) {
        printk("failed to allocate socket.\n");
        return -ENOMEM;
    }

    sock_init_data(sock, sk);
    sk->sk_protocol = 0x0;

    sock->ops = &my_proto_ops;
    sock->state = SS_UNCONNECTED;

    /* Do the protocol specific socket object initialization */
    return 0;
};

struct net_proto_family my_net_proto = {
    .family = AF_INET_NEW_TCP,
    .create = my_create_socket,
    .owner	= THIS_MODULE,
};

static int __init init_proto(void)
{
    int rc = -EINVAL;
    printk("loading test protocol...\n");

    rc = proto_register(&test_prot, 0);/*2nd parameter 0 or 1?*/
    if (rc) {
        printk("failed to register protocol (%d)\n", rc);
        return rc;
    }

    rc = sock_register(&my_net_proto);
    if (rc) {
        printk("failed to register socket (%d)\n", rc);
        return rc;
    }

    return rc;
}

static void __exit exit_proto(void)
{
    printk("unloading test protocol...\n");
    proto_unregister(&test_prot);
}

module_init(init_proto);
module_exit(exit_proto);

