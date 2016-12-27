#ifndef _list_h_
#define _list_h_

#include "pch.h"


struct list {
    struct list *next;
    int key;
};

struct list *list_create()
{
    struct list *l = (struct list *) malloc(sizeof(struct list));
    l->next = NULL;
    return l;
}

void list_push(struct list *head, int key)
{
    struct list *n = list_create();
    n->key = key;
    n->next = head->next;
    head->next = n;
}

void list_show(struct list *head)
{
    if (head->next == NULL) return;
    struct list *p = head->next;
    while (p) {
        printf("node: %d\n", p->key);
        p = p->next;
    }
}
#endif // _list_h_
