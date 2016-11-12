#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

#if 0
typedef struct _link {
    struct _link *next, *tail;
    int value;
} link, list;

#define LIST_EMPTY(list) (list->tail == NULL)
#endif

_link *list_new()
{
    _link *n = (_link *) malloc(sizeof(_link));
    n->next = n->tail = NULL;
    return n;
}

void list_push_back(list *head, int value)
{
    _link *n = list_new();
    n->value = value;
    n->tail = n->next = NULL;
    if (head->tail) {
        head->tail->next = n;
        head->tail = n;
    } else {
        n->next = head->next;
        head->next = n;
        head->tail = n;
    }
}

int list_push_front(list *head, int value)
{
    _link *n = list_new();
    n->value = value;
    n->next = head->next;
    if (head->next == NULL) head->tail = n;
    head->next = n;
    return 0;
}

_link *list_pop_front(list *head)
{
    _link *n = NULL;
    if (head->tail) {
        n = head->next;
        if (head->next == head->tail) {
            head->next = NULL;
            head->tail = NULL;
        } else {
            head->next = n->next;
        }
    }
    return n;
}

_link *reverse(list *head)
{
    list *r, *p1, *p2;
    r = NULL;
    p1 = head->next;
    while (p1) {
        p2 = p1->next;
        p1->next = r;
        r = p1;
        p1 = p2;
    }
    return r;
}

void list_show(list *head)
{
    _link *n;
    if (head == NULL) return;
    n = head->next;
    while (n) {
        printf("n => %d\n", n->value);
        n = n->next;
    }
    printf("\n");
}

/* merge 2 sorted lists 
   only use nodes in lists, no 
   allocating new nodes, except
   for a new head
 */
list *merge(list *l, list *f)
{
    list dummy;
    list *m = list_new();
    //list *m = &dummy;
    list *t = m;
    list *p = l->next;
    list *r = f->next;
    while (p && r) {
        if (p->value < r->value) {
            t->next = p;
            p = p->next;
        } else {
            t->next = r;
            r = r->next;
        }
        t = t->next;
    }
    if (p != NULL) {
        t->next = p;
    }
    if (r != NULL) {
        t->next = r;
    }
    return m;
}

list *merge2(list *l, list *f)
{
    list *m = list_new();
    while (l->next && f->next) {
        if (l->next->value < f->next->value) {
            list_push_back(m, l->next->value);
            l = l->next;
        } else {
            list_push_back(m, f->next->value);
            f = f->next;
        }
    }
    if (l->next != NULL) {
        while (l->next) {
            list_push_back(m, l->next->value);
            l = l->next;
        }
    }
    if (f->next != NULL) {
        while (f->next) {
            list_push_back(m, f->next->value);
            f = f->next;
        }
    }
    return m;
}

void test_merge()
{
    list *l = list_new();
    list *f = list_new();
    list_push_back(l, 1);
    list_push_back(l, 3);
    list_push_back(l, 5);
    list_push_back(l, 7);
    list_push_back(l, 9);
    list_push_back(l, 21);
    list_push_back(l, 22);
    list_push_back(l, 23);
    list_push_back(f, 2);
    list_push_back(f, 4);
    list_push_back(f, 6);
    list_push_back(f, 8);
    list_push_back(f, 10);
    list_show(l);
    list_show(f);
    list *m = merge(l, f);
    list_show(m);
}

int main()
{
    test_merge();
#if 0
    int i;
    list *l = list_new();
    list *r = list_new();
    for (i = 0; i < 8; i++) {
        list_push_back(l, i);
        list_push_front(l, i+16);
    }
    list_show(l);
    r->next = reverse(l);
    list_show(r);
    return 0;
    while (!LIST_EMPTY(l)) {
        link *n = list_pop_front(l);
        printf("pop: %d\n", n->value);
    }
#endif
    return 0;
}

