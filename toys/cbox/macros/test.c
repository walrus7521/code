#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct device {
        struct list_head list;
        int fd;
        int tty_fd;
        int pid;
        int port;
        unsigned long stack;
};

// http://lxr.free-electrons.com/source/arch/um/drivers/line.c#L700
// coolness
// http://lxr.free-electrons.com/source/scripts/unifdef.c
// woo
// http://dotat.at

static LIST_HEAD(devices);

void add_dev(int i)
{
    struct device *dev;

    dev = malloc(sizeof(*dev));

    if (dev == NULL) {
             printf("dev - malloc failed\n");
             goto cleanup;
    }

    *dev = ((struct device) { .list   = LIST_HEAD_INIT(dev->list),
                              .fd     = i,
                              .tty_fd = 1,
                              .pid    = 2,
                              .port   = 3,
                              .stack  = 4 });

    list_add(&dev->list, &devices);

cleanup:
    return;
}


int main()
{
    INIT_LIST_HEAD(&devices);

    for (int i = 0; i < 4; i++) {
        add_dev(i);
    }

    struct list_head *ele, *next;
    struct device *dev;

    list_for_each_safe(ele, next, &devices) {
        dev = list_entry(ele, struct device, list);
        printf("dev: %d\n", dev->fd);
    }

}
