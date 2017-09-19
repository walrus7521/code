#include <stdio.h>
#include <stdlib.h>

// make into ADT
typedef struct link {
    struct link *next, *tail;
    void *val;
} fifo;

fifo *fifo_new()
{
    fifo *f = (fifo *) malloc(sizeof(fifo));
    f->next = f->tail = NULL;
    return f;
}

void *fifo_get(fifo *list)
{
    fifo *n = NULL;
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

int fifo_empty(fifo *list)
{
    return (list->tail == NULL); //list->next);
}

void fifo_show(fifo *list)
{
    fifo *n;
    if (list == NULL) return;
    n = list->next;
    while (n) {
        printf("n => %x\n", n->val);
        n = n->next;
    }
}

void fifo_clear(fifo *list)
{
    while (!fifo_empty(list)) {
        fifo_get(list);
    }
}

void fifo_put(fifo *list, void *x)
{
    fifo *n = (fifo *) fifo_new();
    n->val = x;
    if (list->tail) {
        list->tail->next = n;
    } else {
        n->next = list->next;
        list->next = n;
    }
    list->tail = n;
}

#if 0
int fifo_test()
{
    fifo *f = fifo_new(); 
    fifo_put(f, (void *) 0);
    fifo_put(f, (void *) 1);
    fifo_put(f, (void *) 2);
    fifo_put(f, (void *) 3);
    fifo_show(f);
    while (!fifo_empty(f)) {
        int l = (int) fifo_get(f);
        printf("=> %x\n", l);
    }
}
#endif

