#include "types.h"

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

void push_front(list_t *list, int key)
{
    link_t *l = link(key);
    l->next = list->head->next;
    list->head->next = l;
    if (list->tail == NULL) {
        list->tail = l;
    }
}

link_t *pop_front(list_t *list)
{
    link_t *t;
    if (list->head->next) {
        t = list->head->next;
        list->head->next = t->next;
    }
    if (list->head->next == NULL) {
        list->tail = NULL;
    }
    return t;
}

void push_back(link_t *list, int key)
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
    push_front(list, 42);
    push_front(list, 17);
    show(list);
}
