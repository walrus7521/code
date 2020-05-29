#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sim.h"
#include "bus.h"
#include "ios.h"
#include "dev.h"
#include "hal.h"


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
int fake_irq_handler(void *ctx)
{
    struct device *dev = (struct device *) ctx;
    printf("fake_irq_handler %d\n", dev->irq); 
    states[state]();
    state = next_state(state);
    return ERROR_SUCCESS;
}
int fake_open(char *name, char *mode) {
    printf("fake_open %s, mode %s\n", name, mode); 
    return ERROR_SUCCESS;
}
int fake_read(struct device *dev, char* buf, int size) { 
    printf("fake_read %d\n", dev->ord); 
    return ERROR_SUCCESS;
}
int fake_write(struct device *dev, char* buf, int size) { 
    printf("fake_write %d\n", dev->ord); 
    return ERROR_SUCCESS;
}
int fake_read_async(struct device *dev, struct irp *irp, char* buf, int size) { 
    printf("fake_read_async %d\n", dev->ord); 
    irp->event.state = EVENT_STATE_PENDING;
    irp->io_type = IO_REQUEST_READ;
    irp->event.type = EVENT_TYPE_SYNCHRONIZATION;
    ios_put((void *) irp);
    return ERROR_PENDING;
}
int fake_write_async(struct device *dev, struct irp *irp, char* buf, int size) { 
    printf("fake_write_async %d\n", dev->ord); 
    return ERROR_PENDING;
}
int fake_ioctl(struct device *dev, int ioctl, char* buf, int size) { 
    printf("fake_ioctl %d\n", dev->ord); 
    return ERROR_SUCCESS;
}
int fake_test(struct device *dev, int testid, char* buf, int size) { 
    printf("fake_test %d\n", dev->ord); 
    return ERROR_SUCCESS;
}
int fake_close(struct device *dev) { 
    printf("fake_close %d\n", dev->ord); 
    return ERROR_SUCCESS;
}

struct device* fake_dev_create()
{
    struct device *dev = (struct device *) malloc(sizeof(struct device));
    //dev->ops.id = i; //DEVICE_TYPE_FAKE;
    strcpy(dev->ops.nm, "fake\0");
    dev->ops.fpopen  = fake_open;
    dev->ops.fpread  = fake_read;
    dev->ops.fpreadasync  = fake_read_async;
    dev->ops.fpwrite = fake_write;
    dev->ops.fpwriteasync = fake_write_async;
    dev->ops.fpioctl = fake_ioctl;
    dev->ops.fpclose = fake_close;
    dev->ops.fptest  = fake_test;
    dev->irq = 7;
    dev->ord = 17;
    hal_register_interrupt(dev->irq, fake_irq_handler);
    return dev;
}

int fake_completion(void *dev, void *irp, void *ctx)
{
    //struct irp *my_irp = (struct irp *) irp;
    printf("fake_completion\n");
    //my_irp->event.state = EVENT_STATE_COMPLETE;
    return 0;
}


void test_fake(struct device* dev)
{
    struct irp *irp = NULL;
    if (dev) {
        dev->ops.fpopen((char *) "dude", (char *) "rb+");
        //int id = dev->ops.fpopen((char *) "dude", 42);
        //dev->ops.fpread(op->id, NULL, 0);

        irp = (struct irp *) malloc(sizeof(struct irp));
        //init_event(&irp->event, EVENT_TYPE_SYNCHRONIZATION, fake_completion);
        ios_init_event(&irp->event, EVENT_TYPE_SYNCHRONIZATION, NULL);
        if (ERROR_PENDING == dev->ops.fpreadasync(dev, irp, NULL, 0)) {
            printf("need to wait on event\n");
            while (irp->event.state != EVENT_STATE_COMPLETE) {
                ios_wait_event(&irp->event);
            }
            printf("got the EVENT\n");
        }

        //dev->ops.fpwrite(op->id, NULL, 0);
        
        //if (ERROR_PENDING == dev->ops.fpwriteasync(op->id, event, NULL, 0)) {
        //    printf("need to wait on event\n");
        //}

        //dev->ops.fpioctl(op->id, 17, NULL, 0);
        dev->ops.fpclose(dev);
    }
}

// device needs interrupts generated
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
            ios_put((void *) irp);
        }
        prev_time = current_time;
    }
    return NULL;
}

void dev_init()
{
    kthread timer;
    struct device* dev = fake_dev_create();
    kthread_create(&timer, NULL, &timer_thread, (void *) dev);
    bus_add_device(dev);
    test_fake(dev);

}

