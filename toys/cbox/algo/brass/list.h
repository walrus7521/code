#ifndef __LIST__
#define __LIST__

typedef void * item_t;

typedef struct {
    item_t *base; item_t *top;
    int size;
} stack_t;

stack_t *create_stack(int size);
int stack_empty(stack_t *st);
int push( item_t x, stack_t *st);
item_t pop(stack_t *st);
item_t top_element(stack_t *st);
void remove_stack(stack_t *st);

void test_stack();

#endif
