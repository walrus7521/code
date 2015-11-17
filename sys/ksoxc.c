#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/un.h>
#include <linux/net.h>
#include <net/sock.h>
#include <linux/socket.h>

#define SOCK_PATH   "/tmp/usocket"
#define MAX     100

struct socket *sock = NULL;


static int __init client_module_init( void ) {

  int retval;
  char str[MAX];

  struct sockaddr_un addr;
  struct msghdr msg;
  struct iovec iov;
  struct iov_iter iter;
  mm_segment_t oldfs;

  printk(KERN_INFO "Start client module.\n");

  // create
  retval = sock_create(AF_UNIX, SOCK_STREAM, 0, &sock); 

  // connect
  memset(&addr, 0, sizeof(addr));  
  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path, SOCK_PATH);

  //retval = sock->ops->connect(sock, (struct sockaddr *)&addr, sizeof(addr), 0);
  retval = sock->ops->connect(sock, (struct sockaddr *)&addr, sizeof(addr) - 1, 0);
  // recvmsg

  memset(&msg, 0, sizeof(msg));
  memset(&iov, 0, sizeof(iov));
  iov_iter_init(&iter, 1, &iov, 1, sizeof(str));

  msg.msg_name = 0;
  msg.msg_namelen = 0;
  msg.msg_iter = iter;
  msg.msg_control = NULL;
  msg.msg_controllen = 0;
  msg.msg_flags = 0;

  oldfs = get_fs();
  set_fs(KERNEL_DS);

  retval = sock_recvmsg(sock, &msg, strlen(str)+1, 0);

  set_fs(oldfs);

  // print str
  printk(KERN_INFO "client module: %s.\n",str);

  // release socket
  sock_release(sock);

  return 0;
}

static void __exit client_module_exit( void )
{
  printk(KERN_INFO "Exit client module.\n");
}

 module_init( client_module_init );
 module_exit( client_module_exit );
 MODULE_LICENSE("GPL");
