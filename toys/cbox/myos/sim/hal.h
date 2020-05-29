#ifndef __hal_h_
#define __hal_h_

// abstracts:
//    cpu
//    memory mgmt
//    interrupt routing
//    io resources
//    dma
//    timers
//    mutexes
//    events

typedef int (*irq_handler)(void *context);
int hal_register_interrupt(int vector, irq_handler cb);
int hal_init();
void hal_route_interrupt(int vector, void *context);


#endif // __hal_h_
