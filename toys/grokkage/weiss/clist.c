#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "clist.h"

clist *clist_create(void *data)
{
    clist *list = (clist *) malloc(sizeof(clist));
    list->next = list;
    list->last = list;
    list->size = 0;
    list->data = data;
    return list;
}

int clist_init(clist *l)
{
    l->next = NULL;
    l->last = NULL;
    l->size = 0;
    return 0;
}

bool clist_empty(clist *l)
{
    return (l->size == 0);
}

bool clist_valid(clist *l)
{
    return (l && (uint64_t) l->data != SENTINEL);
}

int clist_prepend(clist *head, void *data)
{
    clist *t = clist_create(data);
    clist_init(t);
    t->next = head->next;
    head->next = t;
    head->size++;
    return 0;
}

int clist_append(clist *head, void *data)
{
    clist *t = clist_create(data);
    clist_init(t);
    if (head->next == head) {
        printf("0 %lld\n", (uint64_t) data);
        t->next = head->next;
        head->next = t;
    } else {
        printf("+ %lld\n", (uint64_t) data);
        t->next = head->last->next;
        head->last = t;
    }
    head->size++;
    return 0;
}

int clist_delete(clist *head, void *data)
{
    if (head->next) {
        data = head->next->data;
        head->next = head->next->next;
    }
    return 0;
}  

void clist_dump(clist *head)
{
    int i;
    clist *t = head->next;
    //while (clist_valid(t)) {
    for (i = 0; i < 8; i++) {
        uint64_t x = (uint64_t) t->data;
        printf("%d\n", x);
        t = t->next;
    }
}

int main()
{
    clist *head = clist_create((void*)SENTINEL);
    int i;
    uint64_t data = 0;
    for (i = 0; i < 8; i++) {
        //clist_prepend(head, (void *) data++);
        clist_append(head, (void *) data++);
    }
    clist_dump(head);
}

