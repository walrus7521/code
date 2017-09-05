#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/cygdrive/c/cygwin64/usr/include/pthread.h"

// fake device needs a state machine

enum {
    EVENT_STATE_COMPLETE,
    EVENT_STATE_PENDING
};

enum {
    EVENT_TYPE_NOTIFICATION, // multiple waiters released
    EVENT_TYPE_SYNCHRONIZATION // only one waiter is released
};

struct EVENT {
    int state;
    int type;
    pthread_mutex_t mtx;
    pthread_cond_t cv;
};
 
enum {
    IO_REQUEST_READ,
    IO_REQUEST_WRITE,
    IO_REQUEST_IOCTL,
    IO_REQUEST_IRQ
};

struct IRP {
    int io_type;
    char *buffer;
    int size;
    struct EVENT event;
    void *dev;
};

#define IOQUEUE_INITIALIZER(buffer) { buffer, sizeof(buffer) / sizeof(buffer[0]), 0, 0, 0, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER }

struct IO_QUEUE {
    void **buffer;
    int capacity;
    int size;
    int write;
    int read;
    pthread_mutex_t mutex;
    pthread_cond_t full;
    pthread_cond_t empty;
};

struct IO_QUEUE *ioqueue_create()
{
    struct IO_QUEUE *fifo = (struct IO_QUEUE *) malloc(sizeof(struct IO_QUEUE));
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

void ioqueue_put(struct IO_QUEUE *fifo, void *value)
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

void *ioqueue_get(struct IO_QUEUE *fifo)
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

int ioqueue_size(struct IO_QUEUE *fifo)
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

struct DEVICE {
    int type;
    int ord;
    int state;
    struct fops ops;
};

enum {
    ERROR_SUCCESS,
    ERROR_NO_DEVS,
    ERROR_PENDING
};

#define MAX_DEVS (8)
struct DEVICE devices[8];
int dev_mgr_init()
{
    int i;
    struct DEVICE *dev;
    for (i = 0; i < MAX_DEVS; i++) {
        dev = &devices[i];
        dev->type = DEVICE_TYPE_NONE;
        dev->ord = -1;
        dev->state = DEVICE_STATE_NONE;
        return ERROR_SUCCESS;
    }
    return -ERROR_NO_DEVS;
}

int dev_mgr_register(struct DEVICE *device)
{
    int i;
    struct DEVICE *dev;
    for (i = 0; i < MAX_DEVS; i++) {
        dev = &devices[i];
        if (dev->state == DEVICE_STATE_NONE) {
            // grab it!!
            dev->state = DEVICE_STATE_CREATED;
            dev->type = device->ops.id;
            device->ops.dev = device;
            return ERROR_SUCCESS;
        }
    }
    return -ERROR_NO_DEVS;
}

struct IO_QUEUE *fifo;

void io_thread()
{
    printf("io thread running\n");
    struct DEVICE *dev;
    while (1) {
        struct IRP *irp = ioqueue_get(fifo);
        if (irp->io_type == IO_REQUEST_IRQ) {
            printf("got interrupt: %d\n", irp->size);
            dev = irp->dev;
            dev->ops.fpirq(irp->size);
        } else {
            sleep(3); // simulate IO
            printf("send notification:  io_type = %d\n", irp->io_type);
            irp->event.state = EVENT_STATE_COMPLETE;
            if (irp->event.type == EVENT_TYPE_NOTIFICATION) {
                pthread_cond_broadcast(&irp->event.cv); // wake all
            } else
            if (irp->event.type == EVENT_TYPE_SYNCHRONIZATION) {
                pthread_cond_signal(&irp->event.cv); // wake one
            }
        }     
    }
}

// fake device
int fake_irq_handler(int dev)
{
    printf("fake_irq_handler %d\n", dev); 
    return ERROR_SUCCESS;
}
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
    irp->io_type = IO_REQUEST_READ;
    irp->event.type = EVENT_TYPE_SYNCHRONIZATION;
    ioqueue_put(fifo, irp);
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

struct DEVICE* fake_dev_create(int i)
{
    struct DEVICE *dev = (struct DEVICE *) malloc(sizeof(struct DEVICE));
    dev->ops.id = i; //DEVICE_TYPE_FAKE;
    strcpy(dev->ops.nm, "fake\0");
    dev->ops.fpopen  = fake_open;
    dev->ops.fpread  = fake_read;
    dev->ops.fpreadasync  = fake_read_async;
    dev->ops.fpwrite = fake_write;
    dev->ops.fpwriteasync = fake_write_async;
    dev->ops.fpioctl = fake_ioctl;
    dev->ops.fpclose = fake_close;
    dev->ops.fptest  = fake_test;
    dev->ops.fpirq   = fake_irq_handler;
    if (ERROR_SUCCESS != dev_mgr_register(dev)) {
        printf("failed register %d\n", i);
        free(dev);
        return NULL;        
    } else {
        return dev;
    }
}

int init_event(int type, struct EVENT *ev)
{
    ev->mtx = PTHREAD_MUTEX_INITIALIZER;
    ev->cv = PTHREAD_COND_INITIALIZER;
    ev->type = type;
}

void test_fake(struct DEVICE* dev)
{
    struct IRP *irp = NULL;
    if (dev) {
        int id = dev->ops.fpopen("dude", 42);
        //dev->ops.fpread(op->id, NULL, 0);

        irp = (struct IRP *) malloc(sizeof(struct IRP));
        init_event(EVENT_TYPE_SYNCHRONIZATION, &irp->event);
        if (ERROR_PENDING == dev->ops.fpreadasync(dev->ops.id, irp, NULL, 0)) {
            printf("need to wait on event\n");
            while (irp->event.state != EVENT_STATE_COMPLETE) {
                pthread_cond_wait(&irp->event.cv, &irp->event.mtx);
            }
            printf("got the EVENT\n");
        }

        //dev->ops.fpwrite(op->id, NULL, 0);
        
        //if (ERROR_PENDING == dev->ops.fpwriteasync(op->id, EVENT, NULL, 0)) {
        //    printf("need to wait on event\n");
        //}

        //dev->ops.fpioctl(op->id, 17, NULL, 0);
        dev->ops.fpclose(dev->ops.id);
    }
}

void timer_thread(void *dev)
{
    int id = 0;
    clock_t current_time = clock();
    clock_t prev_time = 0;
    clock_t delta_t = 0;
    struct IRP *irp = (struct IRP *) malloc(sizeof(struct IRP));
    irp->io_type = IO_REQUEST_IRQ;
    irp->dev = dev;
    while (1) {
        current_time = clock();
        delta_t += (current_time - prev_time);
        sleep(1);
        if (delta_t >= 100) {
            delta_t = 0;
            irp->size = ++id;
            ioqueue_put(fifo, irp);
        }
        prev_time = current_time;
    }
}

int main()
{
    int i;
    pthread_t io;
    pthread_t timer;
    fifo = ioqueue_create();

    dev_mgr_init();

    i = 0;
    struct DEVICE* dev = fake_dev_create(i);

    // create an io thread
    pthread_create(&io, NULL, (void *) &io_thread, NULL);
    // create timer thread, simulate interrupts
    pthread_create(&timer, NULL, (void *) &timer_thread, dev);

    test_fake(dev);

    while (1) ;
}

