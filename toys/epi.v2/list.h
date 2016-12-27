#ifndef _list_h_
#define _list_h_

#include "pch.h"

enum {
    INVALID = -1
};

struct list {
    struct list *next;
    struct list *last;
    int key;
    int max; // need to manage max separately
};

struct list *list_create(int key)
{
    struct list *l = (struct list *) malloc(sizeof(struct list));
    l->next = NULL;
    l->key = key;
    l->max = INT_MIN;
    return l;
}

void list_push(struct list *head, int key)
{
    struct list *n = list_create(key);
    if (head->next == NULL) {
        head->next = head->last = n;
    } else {
        n->next = head->next;
        head->next = n;
    }
}

void list_put(struct list *head, int key)
{
    struct list *n = list_create(key);
    if (head->last == NULL) {
        head->next = head->last = n;
    } else {
        head->last->next = n;
        head->last = n;
    }
}

int list_pop(struct list *head)
{
    if (head->next == NULL) {
        return INVALID;
    } else {
        struct list *n = head->next;
        head->next = n->next;
        int key = n->key;
        free(n);
        return key;
    }
}

int list_get(struct list *head)
{
    int key = INVALID;
    struct list *n = head->next;
    if (head->next == NULL) {
        return key;
    } else
    if (head->next->next == NULL) {
        key = n->key;
        free(n);
        head->next = head->last = NULL;
        return key;
    } else { 
        // find 2nd to last node
        while (n->next->next != NULL) {
            n = n->next;
        }
        struct list *r = head->last;
        head->last = n;
        n->next = NULL;
        key = r->key;
        free(r);
        return key;
    }
}

int list_empty(struct list *head)
{
    if (head->next == NULL) {
        return 1;
    } else {
        return 0;
    }
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
