#include "dev.h"

#ifndef __bus_h_
#define __bus_h_

int bus_init();
int bus_add_device(struct device *dev);
int bus_enum(struct device **devs);


#endif // __bus_h_
