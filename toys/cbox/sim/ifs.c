#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sim.h"
#include "bus.h"
#include "ios.h"
#include "dev.h"

struct device *ifsdev;
FILE *fp;
//fp=fopen("c:\\test.bin", "wb");
//char x[10]="ABCDEFGHIJ";
//fwrite(x, sizeof(x[0]), sizeof(x)/sizeof(x[0]), fp);

int ifs_open(char *name, char *mode) {
    printf("ifs_open %s, mode %s\n", name, mode); 
    fp = fopen(name, mode);
    return ERROR_SUCCESS;
}
int ifs_read(struct device *dev, char* buf, int size) { 
    int n = fread(buf, 1, size, fp);
    printf("ifs_read %d ->%d\n", dev->ord, n);
    return ERROR_SUCCESS;
}
int ifs_write(struct device *dev, char* buf, int size) { 
    int n = fwrite(buf, 1, size, fp);
    printf("ifs_write %d -> %d\n", dev->ord, n); 
    return ERROR_SUCCESS;
}
int ifs_read_async(struct device *dev, struct irp *irp, char* buf, int size) { 
    printf("ifs_read_async %d\n", dev->ord); 
    irp->event.state = EVENT_STATE_PENDING;
    irp->io_type = IO_REQUEST_READ;
    irp->event.type = EVENT_TYPE_SYNCHRONIZATION;
    ios_put((void *) irp);
    return ERROR_PENDING;
}
int ifs_write_async(struct device *dev, struct irp *irp, char* buf, int size) { 
    printf("ifs_read_async %d\n", dev->ord); 
    irp->event.state = EVENT_STATE_PENDING;
    irp->io_type = IO_REQUEST_WRITE;
    irp->event.type = EVENT_TYPE_SYNCHRONIZATION;
    ios_put((void *) irp);
    return ERROR_PENDING;
}
int ifs_ioctl(struct device *dev, int ioctl, char* buf, int size) { 
    printf("ifs_ioctl %d\n", dev->ord); 
    return ERROR_SUCCESS;
}
int ifs_test(struct device *dev, int testid, char* buf, int size) { 
    printf("ifs_test %d\n", dev->ord); 
    return ERROR_SUCCESS;
}
int ifs_flush(struct device *dev) { 
    printf("ifs_flush %d\n", dev->ord); 
    fflush(fp);
    return ERROR_SUCCESS;
}
int ifs_tell(struct device *dev) { 
    int n = ftell(fp);
    printf("ifs_tell %d -> %d\n", dev->ord, n);
    return n;
}
int ifs_seek(struct device *dev, int offset, int origin) { 
    int n = fseek(fp, offset, origin);
    printf("ifs_seek %d -> %d\n", dev->ord, n);
    return ERROR_SUCCESS;
}
int ifs_close(struct device *dev) { 
    printf("ifs_close %d\n", dev->ord); 
    fclose(fp);
    return ERROR_SUCCESS;
}

struct device* ifs_dev_create(int i)
{
    struct device *dev = (struct device *) malloc(sizeof(struct device));
    dev->ops.id = i; //DEVICE_TYPE_FAKE;
    strcpy(dev->ops.nm, "ifs\0");
    dev->ops.fpopen  = ifs_open;
    dev->ops.fpread  = ifs_read;
    dev->ops.fpreadasync  = ifs_read_async;
    dev->ops.fpwrite = ifs_write;
    dev->ops.fpwriteasync = ifs_write_async;
    dev->ops.fpioctl = ifs_ioctl;
    dev->ops.fpseek = ifs_seek;
    dev->ops.fptell = ifs_tell;
    dev->ops.fpflush = ifs_flush;
    dev->ops.fpclose = ifs_close;
    dev->ops.fptest  = ifs_test;
    dev->ord = 42;
    if (ERROR_SUCCESS != bus_add_device(dev)) {
        printf("failed register %d\n", i);
        free(dev);
        return NULL;        
    } else {
        return dev;
    }
}

int ifs_completion(void *dev, void *irp, void *ctx)
{
    //struct irp *my_irp = (struct irp *) irp;
    printf("ifs_completion\n");
    //my_irp->event.state = EVENT_STATE_COMPLETE;
    return 0;
}

void ifs_test()
{
    char buf[] = "dude wusup";
    char buf2[32];
    int sz = sizeof(buf)/sizeof(buf[0]);
    ifsdev->ops.fpopen((char *) "test.bin", (char *) "wb");
    ifsdev->ops.fpwrite(ifsdev, buf, sz);
    printf("tell: %d\n", ifsdev->ops.fptell(ifsdev));
    ifsdev->ops.fpflush(ifsdev);
    ifsdev->ops.fpseek(ifsdev, 0, SEEK_SET);
    printf("tell: %d\n", ifsdev->ops.fptell(ifsdev));
    memset(buf2, 32, '\0');
    ifsdev->ops.fpread(ifsdev, buf2, sz);
    printf("read: %s\n", buf2);
    ifsdev->ops.fpclose(ifsdev);
}


void ifs_init()
{
    ifsdev = ifs_dev_create(42);
    ifs_test();

}

