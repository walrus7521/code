#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sim.h"
#include "bus.h"

#define MAX_NUM_SLOTS (8)
struct device devices[8];
int bus_init()
{
    int i;
    struct device *dev;
    for (i = 0; i < MAX_NUM_SLOTS; i++) {
        dev = &devices[i];
        dev->type = DEVICE_TYPE_NONE;
        dev->ord = -1;
        dev->state = DEVICE_STATE_NONE;
        return ERROR_SUCCESS;
    }
    return -ERROR_NO_DEVS;
}

int bus_register(struct device *device)
{
    int i;
    struct device *dev;
    for (i = 0; i < MAX_NUM_SLOTS; i++) {
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

int bus_add_device(struct device *dev)
{
    return ERROR_SUCCESS;
}

