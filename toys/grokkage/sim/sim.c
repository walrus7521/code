#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sim.h"
#include "bus.h"
#include "ios.h"
#include "dev.h"

int sim_startup()
{
    bus_init();
    ios_init();
    dev_init();
    ios_rescan();

    while (1) ;
}

