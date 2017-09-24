#ifndef STACK_H
#define STACK_H

#define T Stack_t
typedef struct T *T;

T    Stack_new(void);
int  Stack_empty(T stk);
void Stack_push(T stk, void *x);
void *Stack_pop(T stk);
void Stack_free(T *stk); // we use ** to set the pointer to NULL after freeing

#undef T // clients must use Stack_t

#endif // STACK_H
