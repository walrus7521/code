#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sim.h"
#include "bus.h"

#define MAX_NUM_SLOTS (8)
static struct device devices[MAX_NUM_SLOTS];
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

int bus_add_device(struct device *adev)
{
    int i;
    struct device *dev;
    for (i = 0; i < MAX_NUM_SLOTS; i++) {
        dev = &devices[i];
        if (dev->state == DEVICE_STATE_NONE) {
            printf("bus add device %d\n", adev->ord);
            dev->state = DEVICE_STATE_CREATED;
            dev->type = adev->ops.id;
            dev->ord = adev->ord;
            dev->ops.dev = adev;
            return ERROR_SUCCESS;
        }
    }
    return -ERROR_NO_DEVS;
}

int bus_remove_device(struct device *rdev)
{
    int i;
    struct device *dev;
    for (i = 0; i < MAX_NUM_SLOTS; i++) {
        dev = &devices[i];
        if (dev == rdev) {
            dev->state = DEVICE_STATE_NONE;
            dev->ops.dev = NULL;
        }
    }
    return ERROR_SUCCESS;    
}

int bus_enum(struct device **devs)
{
    int i, j=0;
    struct device *dev;
    if (devs == NULL) return MAX_NUM_SLOTS;
    for (i = 0; i < MAX_NUM_SLOTS; i++) {
        dev = &devices[i];
        if (dev->state != DEVICE_STATE_NONE) {
            printf("adding device %d\n", dev->ord);
            devs[j++] = dev;
        }
    }
    return j;
}

