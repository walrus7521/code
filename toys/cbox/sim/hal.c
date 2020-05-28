#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sim.h"
#include "bus.h"
#include "ios.h"
#include "dev.h"
#include "hal.h"


#define NUM_IRQS    (32)
static irq_handler vector[NUM_IRQS];

int hal_init()
{
    int i;
    for (i = 0; i < NUM_IRQS; i++) {
        vector[i] = NULL;
    }
    return ERROR_SUCCESS;
}

int hal_register_interrupt(int irq_num, irq_handler cb)
{
    if (vector[irq_num] == NULL) {
        vector[irq_num] = cb;
        return ERROR_SUCCESS;
    }
    return -ERROR_NO_DEVS;
}

void hal_route_interrupt(int irq_num, void *context)
{
    if (vector[irq_num]) {
        vector[irq_num](context);
    }
}

