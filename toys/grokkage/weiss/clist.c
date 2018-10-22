#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "clist.h"

clist *clist_create(void *data)
{
    clist *list = (clist *) malloc(sizeof(clist));
    list->next = list;
    list->size = 0;
    list->data = data;
    return list;
}

int clist_init(clist *l)
{
    l->next = NULL;
    l->size = 0;
    return 0;
}

bool clist_empty(clist *l)
{
    return (l->size == 0);
}

int clist_insert(clist *l, void *data)
{
    clist *t = clist_create(data);
    t->next = l->next;
    l->next = t;
    l->size++;
    return 0;
}

int clist_append(clist *l, void *data)
{
    return 0;
}

int clist_delete(clist *l, void *data)
{
    if (l->next) {
        data = l->next->data;
        l->next = l->next->next;
    }
    return 0;
}  

void clist_dump(clist *l)
{
    clist *t = l->next;
    while (t) {
        int x = (int) t->data;
        if (x == SENTINEL) break;
        printf("%d\n", x);
        t = t->next;
    }
}

int main()
{
    clist *head = clist_create(SENTINEL);
    int i;
    for (i = 0; i < 8; i++) {
        clist_insert(head, (void *) i);
    }
    clist_dump(head);
}

