/*
 * sample tcp server that runs in linux kernel:
 * https://gist.github.com/llj098/752417
 * 
 * http://www.linuxquestions.org/questions/programming-9/socket-programming-in-kernel-tcp-ip-403685/
 * 
 * Very cool:
 * =========
 * https://github.com/gtungatkar/Linux-kernel-HTTP-server/tree/master/ksocket-0.0.2/sample
 * https://github.com/gtungatkar/Linux-kernel-HTTP-server/blob/master/ksocket-0.0.2/sample/ksocket_tcp_cli_demo.c
 * https://github.com/gtungatkar/Linux-kernel-HTTP-server/blob/master/ksocket-0.0.2/sample/ksocket_tcp_srv_demo.c
 *
 * http://stackoverflow.com/questions/19937598/linux-kernel-module-unix-domain-sockets
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/socket.h>
#include <linux/net.h>
#include <linux/un.h>
#include <net/sock.h>

#define SOCK_PATH   "/tmp/usocket"
#define LISTEN      10

struct socket *sock = NULL;
struct socket *newsock = NULL;

#if 0
struct msghdr {
        void            *msg_name;      /* ptr to socket address structure */
        int             msg_namelen;    /* size of socket address structure */
        struct iov_iter msg_iter;       /* data */
        void            *msg_control;   /* ancillary data */
        __kernel_size_t msg_controllen; /* ancillary data buffer length */
        unsigned int    msg_flags;      /* flags on received message */
        struct kiocb    *msg_iocb;      /* ptr to iocb for async requests */
};
size_t copy_to_iter(void *addr, size_t bytes, struct iov_iter *i);
size_t copy_from_iter(void *addr, size_t bytes, struct iov_iter *i);
#endif

static int __init server_module_init( void ) {

  int retval;
  char* string = "hello_world";

  struct sockaddr_un addr;
  struct msghdr msg;
  struct iovec iov;
  struct iov_iter iter;
  mm_segment_t oldfs;

  // create
  retval = sock_create(AF_UNIX, SOCK_STREAM, 0, &sock);

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path, SOCK_PATH);

  // bind
  //retval = sock->ops->bind(sock,(struct sockaddr *)&addr, sizeof(addr));
  retval = sock->ops->bind(sock,(struct sockaddr *)&addr, sizeof(addr) - 1);

  // listen
  retval = sock->ops->listen(sock, LISTEN);

  //accept
  retval = sock->ops->accept(sock, newsock, 0);



  //sendmsg
  memset(&msg, 0, sizeof(msg));
  memset(&iov, 0, sizeof(iov));
  iov_iter_init(&iter, 1, &iov, 1, sizeof(string));
  
  copy_to_iter((void *) string, strlen(string), &iter);


  msg.msg_name = 0;
  msg.msg_namelen = 0;
  msg.msg_iter = iter;
  msg.msg_control = NULL;
  msg.msg_controllen = 0;
  msg.msg_flags = 0;

  oldfs = get_fs();
  set_fs(KERNEL_DS);

  retval = sock_sendmsg(newsock, &msg, strlen(string)+1);

  set_fs(oldfs);

  return 0;
}

static void __exit server_module_exit( void ) {
  printk(KERN_INFO "Exit usocket.");
}

module_init( server_module_init );
module_exit( server_module_exit );
MODULE_LICENSE("GPL");

