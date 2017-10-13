#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"

typedef struct {
    uint32_t head;
    uint32_t tail;
    uint32_t data_avail;
    uint32_t size;
    uint8_t  status;
    uint8_t *buffer;
} fifo_t;
// space_avail = size - data_avail

struct fifo {
    struct fifo *next, *tail;
    void *val;
} fifo;

fifo_ptr fifo_new()
{
    fifo_ptr f = (fifo_ptr) malloc(sizeof(*f));
    f->next = f->tail = NULL;
    return f;
}

void *fifo_get(fifo_ptr list)
{
    fifo_ptr n = NULL;
    if (list->tail) {
        n = list->next;
        if (list->next == list->tail) {
            list->next = NULL;
            list->tail = NULL;
        } else {
            list->next = n->next;
        }
    }
    return n->val;
}

int fifo_empty(fifo_ptr list)
{
    return (list->tail == NULL); //list->next);
}

void fifo_show(fifo_ptr list)
{
    fifo_ptr n;
    if (list == NULL) return;
    n = list->next;
    while (n) {
        printf("n => %llx\n", (uint64_t) n->val);
        n = n->next;
    }
}

void fifo_clear(fifo_ptr list)
{
    while (!fifo_empty(list)) {
        fifo_get(list);
    }
}

void fifo_put(fifo_ptr list, void *x)
{
    fifo_ptr n = (fifo_ptr) fifo_new();
    n->val = x;
    if (list->tail) {
        list->tail->next = n;
    } else {
        n->next = list->next;
        list->next = n;
    }
    list->tail = n;
}


