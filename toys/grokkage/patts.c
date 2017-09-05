#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/cygdrive/c/cygwin64/usr/include/pthread.h"

enum {
    EVENT_STATE_COMPLETE,
    EVENT_STATE_PENDING
};

struct EVENT {
    int state;
    pthread_mutex_t mtx;
    pthread_cond_t cv;
};
 
enum {
    IO_REQUEST_READ,
    IO_REQUEST_WRITE,
    IO_REQUEST_IOCTL
};

struct IRP {
    int io_type;
    char *buffer;
    int size;
    struct EVENT event;
};

#define FIFO_INITIALIZER(buffer) { buffer, sizeof(buffer) / sizeof(buffer[0]), 0, 0, 0, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER }

struct fifo {
    void **buffer;
    int capacity;
    int size;
    int write;
    int read;
    pthread_mutex_t mutex;
    pthread_cond_t full;
    pthread_cond_t empty;
};

struct fifo *fifo_create()
{
    struct fifo *fifo = (struct fifo *) malloc(sizeof(struct fifo));
    void *buffer = (void *) malloc(32*sizeof(void*));
    fifo->buffer = buffer;
    fifo->capacity = 32;
    fifo->size = 0;
    fifo->write = 0;
    fifo->read = 0;
    fifo->mutex = PTHREAD_MUTEX_INITIALIZER;
    fifo->full = PTHREAD_COND_INITIALIZER;
    fifo->empty = PTHREAD_COND_INITIALIZER;
    return fifo;
}

void fifo_put(struct fifo *fifo, void *value)
{
    pthread_mutex_lock(&(fifo->mutex));
    while (fifo->size == fifo->capacity) pthread_cond_wait(&(fifo->full), &(fifo->mutex));
    fifo->buffer[fifo->write] = value;
    ++fifo->size;
    ++fifo->write;
    fifo->write %= fifo->capacity;
    pthread_mutex_unlock(&(fifo->mutex));
    pthread_cond_broadcast(&(fifo->empty));
}

void *fifo_get(struct fifo *fifo)
{
    pthread_mutex_lock(&(fifo->mutex));
    while (fifo->size == 0) pthread_cond_wait(&(fifo->empty), &(fifo->mutex));
    void *value = fifo->buffer[fifo->read];
    --fifo->size;
    ++fifo->read;
    fifo->read %= fifo->capacity;
    pthread_mutex_unlock(&(fifo->mutex));
    pthread_cond_broadcast(&(fifo->full));
    return value;
}

int fifo_size(struct fifo *fifo)
{
    pthread_mutex_lock(&(fifo->mutex));
    int size = fifo->size;
    pthread_mutex_unlock(&(fifo->mutex));
    return size;
}

struct fops {
    void *dev;
    int id;
    char nm[8];
    int (*fpopen)(char *name, int mode);
    int (*fpread)(int dev, char* buf, int size);
    int (*fpreadasync)(int dev, struct IRP *irp, char* buf, int size);
    int (*fpwrite)(int dev, char* buf, int size);
    int (*fpwriteasync)(int dev, struct IRP *irp, char* buf, int size);
    int (*fpioctl)(int dev, int ioctl, char* buf, int size);
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
    struct fops *ops;
};

enum {
    ERROR_SUCCESS,
    ERROR_NO_DEVS,
    ERROR_PENDING
};

#define MAX_DEVS (8)
struct device devices[8];
int dev_mgr_init()
{
    int i;
    struct device *dev;
    for (i = 0; i < MAX_DEVS; i++) {
        dev = &devices[i];
        dev->type = DEVICE_TYPE_NONE;
        dev->ord = -1;
        dev->state = DEVICE_STATE_NONE;
        return ERROR_SUCCESS;
    }
    return -ERROR_NO_DEVS;
}

int dev_mgr_register(struct fops *ops)
{
    int i;
    struct device *dev;
    for (i = 0; i < MAX_DEVS; i++) {
        dev = &devices[i];
        if (dev->state == DEVICE_STATE_NONE) {
            // grab it!!
            dev->state = DEVICE_STATE_CREATED;
            dev->type = ops->id;
            ops->dev = dev;
            return ERROR_SUCCESS;
        }
    }
    return -ERROR_NO_DEVS;
}

struct fifo *fifo;

void io_thread()
{
    printf("io thread running\n");
    while (1) {
        struct IRP *irp = fifo_get(fifo);
        sleep(3);
        printf("send notification\n");
        irp->event.state = EVENT_STATE_COMPLETE;
        pthread_cond_broadcast(&irp->event.cv); // wake all
        //pthread_mutex_unlock(&EVENT->mtx);
    }
}

// fake device
int fake_open(char *name, int mode) {
    printf("fake_open %s, mode %x\n", name, mode); 
    return ERROR_SUCCESS;
}
int fake_read(int dev, char* buf, int size) { 
    printf("fake_read %d\n", dev); 
    return ERROR_SUCCESS;
}
int fake_write(int dev, char* buf, int size) { 
    printf("fake_write %d\n", dev); 
    return ERROR_SUCCESS;
}
int fake_read_async(int dev, struct IRP *irp, char* buf, int size) { 
    printf("fake_read_async %d\n", dev); 
    irp->event.state = EVENT_STATE_PENDING;
    fifo_put(fifo, irp);
    return ERROR_PENDING;
}
int fake_write_async(int dev, struct IRP *irp, char* buf, int size) { 
    printf("fake_write_async %d\n", dev); 
    return ERROR_PENDING;
}
int fake_ioctl(int dev, int ioctl, char* buf, int size) { 
    printf("fake_ioctl %d\n", dev); 
    return ERROR_SUCCESS;
}
int fake_test(int dev, int testid, char* buf, int size) { 
    printf("fake_test %d\n", dev); 
    return ERROR_SUCCESS;
}
int fake_close(int dev) { 
    printf("fake_close %d\n", dev); 
    return ERROR_SUCCESS;
}

struct fops* fake_dev_create(int i)
{
    struct fops *ops = (struct fops *) malloc(sizeof(struct fops));
    ops->id = i; //DEVICE_TYPE_FAKE;
    strcpy(ops->nm, "fake\0");
    ops->fpopen  = fake_open;
    ops->fpread  = fake_read;
    ops->fpreadasync  = fake_read_async;
    ops->fpwrite = fake_write;
    ops->fpwriteasync = fake_write_async;
    ops->fpioctl = fake_ioctl;
    ops->fpclose = fake_close;
    if (ERROR_SUCCESS != dev_mgr_register(ops)) {
        printf("failed register %d\n", i);
        free(ops);
        return NULL;        
    } else {
        return ops;
    }
}

void test_fake(struct fops* op)
{
    struct IRP *irp = NULL;
    if (op) {
        int dev = op->fpopen("dude", 42);
        //op->fpread(op->id, NULL, 0);

        irp = (struct IRP *) malloc(sizeof(struct IRP));
        irp->event.mtx = PTHREAD_MUTEX_INITIALIZER;
        irp->event.cv = PTHREAD_COND_INITIALIZER;
        if (ERROR_PENDING == op->fpreadasync(op->id, irp, NULL, 0)) {
            printf("need to wait on event\n");
            while (irp->event.state != EVENT_STATE_COMPLETE) {
                pthread_cond_wait(&irp->event.cv, &irp->event.mtx);
            }
            printf("got the EVENT\n");
        }

        //op->fpwrite(op->id, NULL, 0);
        
        //if (ERROR_PENDING == op->fpwriteasync(op->id, EVENT, NULL, 0)) {
        //    printf("need to wait on event\n");
        //}

        //op->fpioctl(op->id, 17, NULL, 0);
        op->fpclose(op->id);
    }
}

int main()
{
    int i;
    pthread_t thread;
    fifo = fifo_create();

    dev_mgr_init();

    // create an io thread
    pthread_create(&thread, NULL, (void *) &io_thread, NULL);

    //for (i = 0; i < 12; i++) {
    i = 0;
        struct fops* op = fake_dev_create(i);
        test_fake(op);
    //}
}

