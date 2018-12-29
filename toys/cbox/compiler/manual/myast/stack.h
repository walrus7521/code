#ifndef _STACK_H_
#define _STACK_H_

#include "common.h"

#define MAXSTACKSIZE (100)

typedef struct {
    void *base[MAXSTACKSIZE];
    void **top;
} stack;

status init_stack(stack *p_S);
bool empty_stack(stack *p_S);
status push(stack *p_S, void *data);
status pop(stack *p_S, void **data);
status top(stack *p_S, void **data);

#endif // _STACK_H_
