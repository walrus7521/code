#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sim.h"
#include "bus.h"
#include "ios.h"
#include "hal.h"

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

struct ios {
    struct device *dev;
    char name[32];
    int ord;
};

#define MAX_NUM_IOS (32)
static struct ios namespaces[MAX_NUM_IOS];

static struct io_queue *io_queue;

static struct io_queue *ioqueue_create()
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

static void ioqueue_put(struct io_queue *io_queue, void *value)
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

static void *ioqueue_get(struct io_queue *io_queue)
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

#if 0
// commented out because not used -- compiler warning
static int ioqueue_size(struct io_queue *io_queue)
{
    kmutex_lock(&(io_queue->mutex));
    int size = io_queue->size;
    kmutex_unlock(&(io_queue->mutex));
    return size;
}
#endif

// interrupts from devices also end up here
void *kio_thread(void *arg)
{
    printf("io thread running\n");
    struct device *dev;
    while (1) {
        struct irp *irp = (struct irp *) ioqueue_get(io_queue);
        if (irp->io_type == IO_REQUEST_IRQ) {
            printf("got interrupt: %d\n", irp->size);
            dev = (struct device *) irp->dev;
            hal_route_interrupt(dev->irq, dev);
        } else {
            sleep(3); // simulate IO
            printf("send notification:  io_type = %d\n", irp->io_type);
            if (irp->event.type == EVENT_TYPE_NOTIFICATION) {
                kevent_notify_all(&irp->event.cv); // wake all
            } else
            if (irp->event.type == EVENT_TYPE_SYNCHRONIZATION) {
                kevent_notify(&irp->event.cv); // wake one
            }
            irp->event.state = EVENT_STATE_COMPLETE;            
            if (NULL != irp->event.cb) {
                irp->event.cb(irp->dev, irp, NULL);
            }
        }     
    }
    return NULL;
}

void ios_put(void *value)
{
    ioqueue_put(io_queue, value);
}

void ios_init()
{
    kthread io;
    io_queue = ioqueue_create();
    kthread_create(&io, NULL, &kio_thread, (void *) NULL);
}

void ios_rescan()
{
    struct device *devs[MAX_NUM_IOS];
    // call bus for list of devices
    int n = bus_enum(devs);
    int i;
    struct ios *z;
    struct device *d;
    // populate ios namespace
    for (i = 0; i < n; i++) {
        z = &namespaces[i];
        d = devs[i];
        sprintf(z->name, "%s%d", "dev\\", d->ord);
        printf("device: %s\n", z->name);
    }
}

int ios_init_event(struct event *ev, int type, io_completion_routine cb)
{
    pthread_mutex_init(&ev->mtx, NULL);
    pthread_cond_init(&ev->cv, NULL);
    ev->type = type;
    ev->cb = cb;
    return 0;
}

void ios_wait_event(struct event *ev)
{
    kevent_wait(&ev->cv, &ev->mtx);
}

void ios_list_devs()
{
    // return a list of ios namespaces
}

