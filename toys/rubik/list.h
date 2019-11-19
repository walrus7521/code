#ifndef __LIST__
#define __LIST__

typedef void * item_t;

typedef struct {
    item_t *base; item_t *top;
    int size;
} tstack_t;

tstack_t *create_stack(int size);
int stack_empty(tstack_t *st);
int push( item_t x, tstack_t *st);
item_t pop(tstack_t *st);
item_t top_element(tstack_t *st);
void remove_stack(tstack_t *st);

typedef struct qu_n_t {
    item_t item;
    struct qu_n_t *next;
} qu_node_t;

typedef struct {
    qu_node_t *remove;
    qu_node_t *insert;
} queue_t;

queue_t *create_queue();
void delete_queue(queue_t *qu);
qu_node_t *create_queue_node();
void delete_queue_node(qu_node_t *qn);
int queue_empty(queue_t *qu);
void enqueue(item_t x, queue_t *qu);
item_t dequeue(queue_t *qu);
item_t front_element(queue_t *qu);
void remove_queue(queue_t *qu);
qu_node_t *reverse_queue(queue_t *qu);
void show_queue(queue_t *qu);


#endif
