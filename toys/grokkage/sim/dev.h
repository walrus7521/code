#ifndef __dev_h_
#define __dev_h_

struct fops {
    void *dev;
    int id;
    char nm[8];
    int (*fpopen)(char *name, char *mode);
    int (*fpread)(struct device *dev, char* buf, int size);
    int (*fpreadasync)(struct device *dev, struct irp *irp, char* buf, int size);
    int (*fpwrite)(struct device *dev, char* buf, int size);
    int (*fpwriteasync)(struct device *dev, struct irp *irp, char* buf, int size);
    int (*fpioctl)(struct device *dev, int ioctl, char* buf, int size);
    int (*fptest)(struct device *dev, int testid, char* buf, int size);
    int (*fpseek)(struct device *dev, int offset, int origin);
    int (*fptell)(struct device *dev);
    int (*fpflush)(struct device *dev);
    int (*fpclose)(struct device *dev);
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
    int irq;
    int state;
    struct fops ops;
};

void dev_init();
void test_fake(struct device* dev);



#endif // __dev_h_
