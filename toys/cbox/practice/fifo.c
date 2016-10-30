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

int is_empty(list *head)
{
    if (head->next == NULL) {
        return 1;
    }
    return 0;
}

int get(list *head)
{
    int x = -1;
    link *l;
    if (head->next != NULL) {
        l = head->next;
        x = l->k;
        head->next = l->next;
        free(l);
    }
    return x;
}

void show(list *head)
{
    link *t = head->next;
    while (t) {
        printf("link: %d\n", t->k);
        t = t->next;
    }
}

int main()
{
    list *head = create();
    int i, y;
    for (i = 0; i < 8; i++) {
        put(head, i);
    }
    show(head);
    while (!is_empty(head)) {
        y = get(head); printf("y=%d\n", y);
    }
}

