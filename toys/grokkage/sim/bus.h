#include "dev.h"

#ifndef __bus_h_
#define __bus_h_

#ifdef __cplusplus
extern "C" {
#endif

int bus_init();
int bus_add_device(struct device *dev);
int bus_enum(struct device **devs);

#ifdef __cplusplus
}  //extern "C"
#endif

#endif // __bus_h_
