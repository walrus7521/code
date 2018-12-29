#include "common.h"
#include "stack.h"


status init_stack(stack *p_S)
{
    p_S->top = p_S->base;
    return OK;
}

int current_stacksize(stack *p_S)
{
    int size = sizeof(void *);
    return (p_S->top - p_S->base);
}

bool empty_stack(stack *p_S)
{
    return (p_S->top == p_S->base) ? true : false;
}

status push(stack *p_S, void *p_data)
{
    if (current_stacksize(p_S) == MAXSTACKSIZE) {
        return ERROR;
    }
    *p_S->top = p_data;
    p_S->top++;
    return OK;
}

status pop(stack *p_S, void **p_data)
{
    if (empty_stack(p_S) == true) {
        return ERROR;
    }
    p_S->top--;
    *p_data = *p_S->top;
    return OK;
}

status top(stack *p_S, void **p_data)
{
    if (pop(p_S, p_data) == ERROR) {
        return ERROR;
    }
    return push(p_S, *p_data);
    return OK;
}



