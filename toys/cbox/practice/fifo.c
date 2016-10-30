#include <stdio.h>
#include <stdlib.h>

typedef struct _link {
    struct _link *next, *tail;
    int k;
} link, list;

list *create()
{
    list *l = malloc(sizeof(list));
    l->next = l->tail = NULL;
    return l;
}

void put(list *head, int x)
{
    link *t = malloc(sizeof(link));
    t->k = x;
    if (head->next == NULL) {
        t->next = head->next;
        head->next = t;
        head->tail = t;
    } else {
        head->tail->next = t;
        head->tail = t;
    }
}

int get(list *l)
{
    return 0;
}

void show(list *l)
{
    link *t = l->next;
    while (t) {
        printf("link: %d\n", t->k);
        t = t->next;
    }
}

int main()
{
    list *l = create();
    int i;
    for (i = 0; i < 8; i++) {
        put(l, i);
    }
    show(l);
}

