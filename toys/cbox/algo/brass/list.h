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

typedef struct qu_n_t {
    item_t item;
    struct qu_n_t *next;
} qu_node_t;

typedef struct {
    qu_node_t *remove;
    qu_node_t *insert;
} queue_t;

queue_t *create_queue();
int queue_empty(queue_t *qu);
void enqueue(item_t x, queue_t *qu);
item_t dequeue(queue_t *qu);
item_t front_element(queue_t *qu);
void remove_queue(queue_t *qu);
qu_node_t *reverse_queue(queue_t *qu);
void show_queue(queue_t *qu);


#endif
