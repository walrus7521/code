#include <stdio.h>
#include <stdlib.h>

// make into ADT
struct link {
    struct link *next, *tail;
    void *val;
};

struct link *link_new(void *val)
{
    struct link *n = (struct link *) malloc(sizeof(struct link));
    n->next = n->tail = NULL;
    n->val = val;
    return n;
}

void show(struct link *list)
{
    struct link *n;
    if (list == NULL) return;
    n = list->next;
    while (n) {
        printf("n => %x\n", n->val);
        n = n->next;
    }
}

void put(struct link *list, void *x)
{
    struct link *n = (struct link *) link_new(x); 
    if (list->tail) {
        list->tail->next = n;
    } else {
        n->next = list->next;
        list->next = n;
    }
    list->tail = n;
}

void *get(struct link *list)
{
    struct link *n = NULL;
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

int empty(struct link *list)
{
    return (list->tail == NULL); //list->next);
}

#if 0
void fifo_test()
{
    struct link *h = (struct link *) link_new(0); 
    put(h, (void *) 0);
    put(h, (void *) 1);
    put(h, (void *) 2);
    put(h, (void *) 3);
    show(h);
    while (!empty(h)) {
        struct link *l = get(h);
        printf("=> %x\n", l->val);
    }
}
#endif

