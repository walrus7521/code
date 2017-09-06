#ifndef __bus_h_
#define __bus_h_

struct fops {
    void *dev;
    int id;
    char nm[8];
    int (*fpopen)(char *name, int mode);
    int (*fpread)(int dev, char* buf, int size);
    int (*fpreadasync)(int dev, struct irp *irp, char* buf, int size);
    int (*fpwrite)(int dev, char* buf, int size);
    int (*fpwriteasync)(int dev, struct irp *irp, char* buf, int size);
    int (*fpioctl)(int dev, int ioctl, char* buf, int size);
    int (*fpirq)(int dev);
    int (*fptest)(int dev, int testid, char* buf, int size);
    int (*fpclose)(int dev);
};

enum {
    DEVICE_TYPE_NONE,
    DEVICE_TYPE_FAKE,
    DEVICE_TYPE_REAL
};

enum {
    DEVICE_STATE_NONE,
    DEVICE_STATE_CREATED
};

struct device {
    int type;
    int ord;
    int state;
    struct fops ops;
};

int bus_init();
int bus_register(struct device *device);
int bus_add_device(struct device *dev);


#endif // __bus_h_
