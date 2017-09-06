#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// abstract pthreads
#include "/cygdrive/c/cygwin64/usr/include/pthread.h"
typedef pthread_mutex_t     kmutex;
typedef pthread_cond_t      kevent;
typedef pthread_t           kthread;
#define kmutex_lock         pthread_mutex_lock
#define kmutex_unlock       pthread_mutex_unlock
#define kevent_wait         pthread_cond_wait
#define kevent_notify_all   pthread_cond_broadcast
#define kevent_notify       pthread_cond_signal
#define kthread_create      pthread_create
#define KMUTEX_INIT         PTHREAD_MUTEX_INITIALIZER
#define KEVENT_INIT         PTHREAD_COND_INITIALIZER


// generic IO handling
enum {
    EVENT_STATE_COMPLETE,
    EVENT_STATE_PENDING
};

enum {
    EVENT_TYPE_NOTIFICATION, // multiple waiters released
    EVENT_TYPE_SYNCHRONIZATION // only one waiter is released
};

typedef int IO_COMPLETION_ROUTINE (void *dev, void *irp, void *ctx);

struct EVENT {
    int state;
    int type;
    kmutex mtx;
    kevent cv;
    IO_COMPLETION_ROUTINE *cb;
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

struct IO_QUEUE {
    void **buffer;
    int capacity;
    int size;
    int write;
    int read;
    kmutex mutex;
    kevent full;
    kevent empty;
};

struct IO_QUEUE *ioqueue_create()
{
    struct IO_QUEUE *io_queue = (struct IO_QUEUE *) malloc(sizeof(struct IO_QUEUE));
    void *buffer = (void *) malloc(32*sizeof(void*));
    io_queue->buffer = buffer;
    io_queue->capacity = 32;
    io_queue->size = 0;
    io_queue->write = 0;
    io_queue->read = 0;
    io_queue->mutex = KMUTEX_INIT;
    io_queue->full = KEVENT_INIT;
    io_queue->empty = KEVENT_INIT;
    return io_queue;
}

void ioqueue_put(struct IO_QUEUE *io_queue, void *value)
{
    kmutex_lock(&(io_queue->mutex));
    while (io_queue->size == io_queue->capacity) kevent_wait(&(io_queue->full), &(io_queue->mutex));
    io_queue->buffer[io_queue->write] = value;
    ++io_queue->size;
    ++io_queue->write;
    io_queue->write %= io_queue->capacity;
    kmutex_unlock(&(io_queue->mutex));
    kevent_notify_all(&(io_queue->empty));
}

void *ioqueue_get(struct IO_QUEUE *io_queue)
{
    kmutex_lock(&(io_queue->mutex));
    while (io_queue->size == 0) kevent_wait(&(io_queue->empty), &(io_queue->mutex));
    void *value = io_queue->buffer[io_queue->read];
    --io_queue->size;
    ++io_queue->read;
    io_queue->read %= io_queue->capacity;
    kmutex_unlock(&(io_queue->mutex));
    kevent_notify_all(&(io_queue->full));
    return value;
}

int ioqueue_size(struct IO_QUEUE *io_queue)
{
    kmutex_lock(&(io_queue->mutex));
    int size = io_queue->size;
    kmutex_unlock(&(io_queue->mutex));
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
            dev->state = DEVICE_STATE_CREATED;
            dev->type = device->ops.id;
            device->ops.dev = device;
            return ERROR_SUCCESS;
        }
    }
    return -ERROR_NO_DEVS;
}

struct IO_QUEUE *io_queue;

void kio_thread()
{
    printf("io thread running\n");
    struct DEVICE *dev;
    while (1) {
        struct IRP *irp = ioqueue_get(io_queue);
        if (irp->io_type == IO_REQUEST_IRQ) {
            printf("got interrupt: %d\n", irp->size);
            dev = irp->dev;
            dev->ops.fpirq(irp->size);
        } else {
            sleep(3); // simulate IO
            printf("send notification:  io_type = %d\n", irp->io_type);
            if (irp->event.type == EVENT_TYPE_NOTIFICATION) {
                kevent_notify_all(&irp->event.cv); // wake all
            } else
            if (irp->event.type == EVENT_TYPE_SYNCHRONIZATION) {
                kevent_notify(&irp->event.cv); // wake one
            }
            irp->event.cb(irp->dev, irp, NULL);
        }     
    }
}

// fake device needs a state machine
typedef int (*fake_dev_state)();
int stop(){printf("fake stop\n");}
int start(){printf("fake start\n");}
int caution(){printf("fake caution\n");}
enum STATES { GREEN, YELLOW, RED };
fake_dev_state states[3] = {start, caution, stop};
int next_state(int state) {
    switch (state) {
        case GREEN:  return YELLOW;
        case YELLOW: return RED;
        case RED:    return GREEN;
    }
}
int state = GREEN;

// fake device operations
int fake_irq_handler(int dev)
{
    printf("fake_irq_handler %d\n", dev); 
    states[state]();
    state = next_state(state);
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
    ioqueue_put(io_queue, irp);
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

int init_event(struct EVENT *ev, int type, IO_COMPLETION_ROUTINE *cb)
{
    ev->mtx = KMUTEX_INIT;
    ev->cv = KEVENT_INIT;
    ev->type = type;
    ev->cb = cb;
}

int fake_completion(void *dev, void *irp, void *ctx)
{
    struct IRP *my_irp = (struct IRP *) irp;
    printf("fake_completion\n");
    my_irp->event.state = EVENT_STATE_COMPLETE;
    return 0;
}


void test_fake(struct DEVICE* dev)
{
    struct IRP *irp = NULL;
    if (dev) {
        int id = dev->ops.fpopen("dude", 42);
        //dev->ops.fpread(op->id, NULL, 0);

        irp = (struct IRP *) malloc(sizeof(struct IRP));
        init_event(&irp->event, EVENT_TYPE_SYNCHRONIZATION, fake_completion);
        if (ERROR_PENDING == dev->ops.fpreadasync(dev->ops.id, irp, NULL, 0)) {
            printf("need to wait on event\n");
            while (irp->event.state != EVENT_STATE_COMPLETE) {
                kevent_wait(&irp->event.cv, &irp->event.mtx);
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
            ioqueue_put(io_queue, irp);
        }
        prev_time = current_time;
    }
}

int main()
{
    int i;
    kthread io;
    kthread timer;
    io_queue = ioqueue_create();

    dev_mgr_init();

    i = 0;
    struct DEVICE* dev = fake_dev_create(i);

    // create an io thread
    kthread_create(&io, NULL, (void *) &kio_thread, NULL);
    // create timer thread, simulate interrupts
    kthread_create(&timer, NULL, (void *) &timer_thread, dev);

    test_fake(dev);

    while (1) ;
}

