#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sim.h"
#include "bus.h"
#include "ios.h"
#include "dev.h"


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
    //ioqueue_put(io_queue, (void *) irp);
    ios_put((void *) irp);
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
    if (ERROR_SUCCESS != bus_register(dev)) {
        printf("failed register %d\n", i);
        free(dev);
        return NULL;        
    } else {
        return dev;
    }
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
            //ioqueue_put(io_queue, irp);
            ios_put((void *) irp);
        }
        prev_time = current_time;
    }
    return NULL;
}

void dev_init()
{
    kthread timer;
    struct device* dev = fake_dev_create(42);
    kthread_create(&timer, NULL, &timer_thread, (void *) dev);
    bus_add_device(dev);
    test_fake(dev);

}

