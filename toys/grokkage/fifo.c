#include <stdio.h>
#include <stdlib.h>

// make into ADT
struct link {
    struct link *next, *tail;
    int val;
};

struct link *link_new(int val)
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
        printf("n => %d\n", n->val);
        n = n->next;
    }
}

void put(struct link *list, int x)
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

struct link *get(struct link *list)
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
    return n;
}

int empty(struct link *list)
{
    return (list->tail == NULL); //list->next);
}

void main()
{
    struct link *h = (struct link *) link_new(0); 
    put(h, 0);
    put(h, 1);
    put(h, 2);
    put(h, 3);
    show(h);
    while (!empty(h)) {
        struct link *l = get(h);
        printf("=> %d\n", l->val);
    }
}

