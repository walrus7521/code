#ifndef _list_h_
#define _list_h_

#include "pch.h"
#include "heap.h"

enum {
    INVALID = -1
};

struct list {
    struct list *next;
    struct list *last;
    int key;
    struct heap *max; // need to manage max separately
};

void list_show(struct list *head);

struct list *list_create(int key)
{
    struct list *l = (struct list *) malloc(sizeof(struct list));
    l->next = NULL;
    l->key = key;
    l->max = heap_create(32);
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
    heap_insert(head->max, key);

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
    heap_insert(head->max, key);
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
        heap_extract(head->max, key);
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
        heap_extract(head->max, key);
        return key;
    }
}

int list_max(struct list *head)
{
    int mx = head->max->A[1];
    return mx;
}

int list_empty(struct list *head)
{
    if (head->next == NULL) {
        return 1;
    } else {
        return 0;
    }
}

struct list *merge_2_sorted_lists(struct list *l1, struct list *l2)
{
    struct list *m = NULL;
    struct list *n1 = l1->next;
    struct list *n2 = l2->next;
    struct list *q = NULL;
    while (n1 && n2) {
        if (n1->key <= n2->key) {
            printf("n1: %d\n", n1->key);
            if (m == NULL) {
                m = l1;
            }
            q = n1;
            n1 = n1->next;
            q->next = m->next;
            m->next = q;
        } else {
            printf("n2: %d\n", n2->key);
            if (m == NULL) {
                m = l2;
            }
            q = n2;
            n2 = n2->next;
            q->next = m->next;
            m->next = q;
        }
        m = m->next;
    }
    if (n1) {
        m->next = n1;
    } else if (n2) {
        m->next = n2;
    }
    return l1;
}

void list_show(struct list *head)
{
    printf("show list:\n");
    if (head->next == NULL) return;
    struct list *p = head->next;
    while (p) {
        printf("node: %d\n", p->key);
        p = p->next;
    }
}
#endif // _list_h_
