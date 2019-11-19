#include <stdio.h>
#include <stdlib.h>
#include "list.h"

tstack_t *create_stack(int size)
{ 
    tstack_t *st;
    st = (tstack_t *) malloc( sizeof(tstack_t) );
    st->base = (item_t *) malloc( size * sizeof(item_t) );
    st->size = size;
    st->top = st->base;
    return( st );
}

int stack_empty(tstack_t *st)
{ 
    return( st->base == st->top );
}

int push( item_t x, tstack_t *st)
{ 
    if ( st->top < st->base + st->size ) { 
        *(st->top) = x; 
        st->top += 1; 
        return( 0 );
    }
    return (-1);
}

item_t pop(tstack_t *st)
{ 
    st->top -= 1;
    return( *(st->top) );
}

item_t top_element(tstack_t *st)
{ 
    return( *(st->top -1) );
}

void remove_stack(tstack_t *st)
{ 
    free( st->base );
    free( st );
}

queue_t *create_queue()
{
    queue_t *qu;
    qu = (queue_t *) malloc(sizeof(queue_t));
    qu->remove = qu->insert = NULL;
    return(qu);
}

qu_node_t *create_queue_node()
{
    qu_node_t *qn;
    qn = (qu_node_t *) malloc(sizeof(qu_node_t));
    return(qn);
}

void delete_queue(queue_t *qu)
{
    free(qu);
}

void delete_queue_node(qu_node_t *qn)
{
    free(qn);
}

int queue_empty(queue_t *qu)
{ 
    return(qu->insert ==NULL);
}

void enqueue(item_t x, queue_t *qu)
{ 
    qu_node_t *tmp;
    tmp = create_queue_node();
    tmp->item = x;
    tmp->next = NULL; /* end marker */
    if (qu->insert != NULL) { /* queue nonempty */
        qu->insert->next = tmp;
        qu->insert = tmp;
    } else { /* insert in empty queue */
        qu->remove = qu->insert = tmp;
    }
}

item_t dequeue(queue_t *qu)
{ 
    qu_node_t *tmp; 
    item_t tmp_item;
    tmp = qu->remove; 
    tmp_item = tmp->item;
    qu->remove = tmp->next;
    if (qu->remove == NULL) { /* reached end */
        qu->insert = NULL; /* make queue empty */
    }
    delete_queue_node(tmp);
    return (tmp_item);
}

item_t front_element(queue_t *qu)
{
    return(qu->remove->item);
}

void remove_queue(queue_t *qu)
{
    qu_node_t *tmp;
    while (qu->remove != NULL) {
        tmp = qu->remove;
        qu->remove = tmp->next;
        delete_queue_node(tmp);
    }
    free(qu);
}

void show_queue(queue_t *qu)
{
    qu_node_t *p = qu->remove;
    while (p != NULL) {
        printf("qu: %d\n", p->item);
        p = p->next;
    }
}

qu_node_t *reverse_queue(queue_t *qu)
{
    qu_node_t *p = qu->remove;
    qu_node_t *q;
    qu_node_t *r = NULL;
    while (p) {
        q = p->next;
        p->next = r;
        r = p;
        p = q;
    }
    return r;
}


