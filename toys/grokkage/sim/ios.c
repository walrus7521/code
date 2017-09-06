#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sim.h"
#include "bus.h"
#include "ios.h"

struct io_queue *io_queue;

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


void ios_put(void *value)
{
    ioqueue_put(io_queue, value);
}


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

void ios_init()
{
    kthread io;
    io_queue = ioqueue_create();
    kthread_create(&io, NULL, &kio_thread, (void *) NULL);
}
void ios_rescan()
{
}
void add_devices()
{
}

int init_event(struct event *ev, int type, io_completion_routine cb)
{
    pthread_mutex_init(&ev->mtx, NULL);
    pthread_cond_init(&ev->cv, NULL);
    ev->type = type;
    ev->cb = cb;
    return 0;
}

