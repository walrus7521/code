#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct link {
    struct link *next;
    int key;
} link_t;

typedef struct {
    link_t *head;
    link_t *tail;
} list_t;

list_t *new()
{
    list_t *list = malloc(sizeof(list_t));
    list->head = malloc(sizeof(link_t));
    list->head->next = NULL;
    list->tail = NULL;
    return list;
}

link_t *link(int key)
{
    link_t *link = malloc(sizeof(link_t));
    link->key = key;
    link->next = NULL;
    return link;
}

void push(list_t *list, int key)
{
    link_t *l = link(key);
    l->next = list->head->next;
    list->head->next = l;
    if (list->tail == NULL) {
        list->tail = l;
    }
}

link_t *pop(link_t *head)
{
    return NULL;
}

void append(link_t *head, int key)
{
    link_t *l = link(key);
}


void show(list_t *list)
{
    link_t *t = list->head->next;
    while (t) {
        printf("t->%d\n", t->key);
        t = t->next;
    }
}

int main()
{
    list_t *list = new();
    push(list, 42);
    push(list, 17);
    show(list);
}
