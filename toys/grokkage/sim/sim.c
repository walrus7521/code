#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// abstract pthreads
//#include "/cygdrive/c/cygwin64/usr/include/pthread.h"
#include <pthread.h>
typedef pthread_mutex_t     kmutex;
typedef pthread_cond_t      kevent;
typedef pthread_t           kthread;
#define kmutex_lock         pthread_mutex_lock
#define kmutex_unlock       pthread_mutex_unlock
#define kevent_wait         pthread_cond_wait
#define kevent_notify_all   pthread_cond_broadcast
#define kevent_notify       pthread_cond_signal
#define kthread_create      pthread_create
#define KMUTEX_INIT        (PTHREAD_MUTEX_INITIALIZER)
#define KEVENT_INIT        (PTHREAD_COND_INITIALIZER)


// generic IO handling
enum {
    EVENT_STATE_COMPLETE,
    EVENT_STATE_PENDING
};

enum {
    EVENT_TYPE_NOTIFICATION, // multiple waiters released
    EVENT_TYPE_SYNCHRONIZATION // only one waiter is released
};

typedef int (*io_completion_routine)(void *dev, void *irp, void *ctx);

struct event {
    int state;
    int type;
    kmutex mtx;
    kevent cv;
    io_completion_routine cb;
};
 
enum {
    IO_REQUEST_READ,
    IO_REQUEST_WRITE,
    IO_REQUEST_IOCTL,
    IO_REQUEST_IRQ
};

struct irp {
    int io_type;
    char *buffer;
    int size;
    struct event event;
    void *dev;
};

struct io_queue {
    void **buffer;
    int capacity;
    int size;
    int write;
    int read;
    kmutex mutex;
    kevent full;
    kevent empty;
};

struct io_queue *ioqueue_create()
{
    struct io_queue *io_queue = (struct io_queue *) malloc(sizeof(struct io_queue));
    void *buffer = (void *) malloc(32*sizeof(void*));
    io_queue->buffer = (void **) buffer;
    io_queue->capacity = 32;
    io_queue->size = 0;
    io_queue->write = 0;
    io_queue->read = 0;
    pthread_mutex_init(&io_queue->mutex, NULL);
    pthread_cond_init(&io_queue->full, NULL);
    pthread_cond_init(&io_queue->empty, NULL);
    return io_queue;
}

void ioqueue_put(struct io_queue *io_queue, void *value)
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

void *ioqueue_get(struct io_queue *io_queue)
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

int ioqueue_size(struct io_queue *io_queue)
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

int dev_mgr_register(struct device *device)
{
    int i;
    struct device *dev;
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

struct io_queue *io_queue;

void *kio_thread(void *arg)
{
    printf("io thread running\n");
    struct device *dev;
    while (1) {
        struct irp *irp = (struct irp *) ioqueue_get(io_queue);
        if (irp->io_type == IO_REQUEST_IRQ) {
            printf("got interrupt: %d\n", irp->size);
            dev = (struct device *) irp->dev;
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
    return NULL;
}

// fake device needs a state machine
typedef void (*fake_dev_state)();
void stop(){printf("fake stop\n");}
void start(){printf("fake start\n");}
void caution(){printf("fake caution\n");}
enum STATES { GREEN, YELLOW, RED };
fake_dev_state states[3] = {start, caution, stop};
int next_state(int state) {
    switch (state) {
        case GREEN:  return YELLOW;
        case YELLOW: return RED;
        case RED:    return GREEN;
    }
    return -1;
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
int fake_read_async(int dev, struct irp *irp, char* buf, int size) { 
    printf("fake_read_async %d\n", dev); 
    irp->event.state = EVENT_STATE_PENDING;
    irp->io_type = IO_REQUEST_READ;
    irp->event.type = EVENT_TYPE_SYNCHRONIZATION;
    ioqueue_put(io_queue, (void *) irp);
    return ERROR_PENDING;
}
int fake_write_async(int dev, struct irp *irp, char* buf, int size) { 
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

struct device* fake_dev_create(int i)
{
    struct device *dev = (struct device *) malloc(sizeof(struct device));
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

int init_event(struct event *ev, int type, io_completion_routine cb)
{
    pthread_mutex_init(&ev->mtx, NULL);
    pthread_cond_init(&ev->cv, NULL);
    ev->type = type;
    ev->cb = cb;
    return 0;
}

int fake_completion(void *dev, void *irp, void *ctx)
{
    struct irp *my_irp = (struct irp *) irp;
    printf("fake_completion\n");
    my_irp->event.state = EVENT_STATE_COMPLETE;
    return 0;
}


void test_fake(struct device* dev)
{
    struct irp *irp = NULL;
    if (dev) {
        dev->ops.fpopen((char *) "dude", 42);
        //int id = dev->ops.fpopen((char *) "dude", 42);
        //dev->ops.fpread(op->id, NULL, 0);

        irp = (struct irp *) malloc(sizeof(struct irp));
        init_event(&irp->event, EVENT_TYPE_SYNCHRONIZATION, fake_completion);
        if (ERROR_PENDING == dev->ops.fpreadasync(dev->ops.id, irp, NULL, 0)) {
            printf("need to wait on event\n");
            while (irp->event.state != EVENT_STATE_COMPLETE) {
                kevent_wait(&irp->event.cv, &irp->event.mtx);
            }
            printf("got the EVENT\n");
        }

        //dev->ops.fpwrite(op->id, NULL, 0);
        
        //if (ERROR_PENDING == dev->ops.fpwriteasync(op->id, event, NULL, 0)) {
        //    printf("need to wait on event\n");
        //}

        //dev->ops.fpioctl(op->id, 17, NULL, 0);
        dev->ops.fpclose(dev->ops.id);
    }
}

void *timer_thread(void *dev)
{
    int id = 0;
    clock_t current_time = clock();
    clock_t prev_time = 0;
    clock_t delta_t = 0;
    struct irp *irp = (struct irp *) malloc(sizeof(struct irp));
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
    return NULL;
}

int sim_startup()
{
    int i;
    kthread io;
    kthread timer;
    io_queue = ioqueue_create();

    dev_mgr_init();

    i = 0;
    struct device* dev = fake_dev_create(i);

    // create an io thread
    kthread_create(&io, NULL, &kio_thread, (void *) NULL);
    // create timer thread, simulate interrupts
    kthread_create(&timer, NULL, &timer_thread, (void *) dev);

    test_fake(dev);

    while (1) ;
}

