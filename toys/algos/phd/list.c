#include <stdio.h>
#include <stdlib.h>

typedef struct _link {
    struct _link *next, *tail;
    int value;
} link, list;

#define IST_EMPTY(list) (list->tail == NULL)

void list_show(list *head)
{
    if (head == NULL) return;
    link *n = head->next;
    while (n) {
        printf("n => %d\n", n->value);
        n = n->next;
    }
    printf("\n");
}

link *list_new()
{
    link *n = (link *) malloc(sizeof(link));
    n->next = n->tail = NULL;
    n->value = -1;
    return n;
}

void push_back(list *head, int value)
{
    link *n = list_new();
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

int push_front(list *head, int value)
{
    link *n = list_new();
    n->value = value;
    n->next = head->next;
    if (head->next == NULL) head->tail = n;
    head->next = n;
    return 0;
}

link *pop_front(list *head)
{
    link *n = NULL;
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

link *reverse(list *head)
{
    list *r = NULL;
    list *p = head->next;
    list *q;
    while (p) {
        q = p->next;
        p->next = r;
        r = p;
        p = q;
    }
    return r;
}

/* merge 2 sorted lists: only use nodes in lists, no 
   allocating new nodes, except for a new head
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

list *zip(list *l, list *f)
{
    list dummy;
    list *m = list_new();
    //list *m = &dummy;
    list *t = m;
    list *p = l->next;
    list *r = f->next;
    int alternate = 1;
    while (p && r) {
        if (alternate) {
            t->next = p;
            p = p->next;
        } else {
            t->next = r;
            r = r->next;
        }
        alternate ^= 1;
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

int main()
{
#if 1
    // test merge
    list *l = list_new();
    list *f = list_new();
    int i;
    for (i = 0; i < 8; i++) {
        push_back(l, 2*i);
        push_back(f, (2*i+1));
    }
    list_show(l);
    list_show(f);
    //list *m = merge(l, f);
    list *z = zip(l, f);
    list_show(z);
#endif
#if 0
    int i;
    list *l = list_new();
    list *r = list_new();
    for (i = 0; i < 8; i++) {
        push_back(l, i);
        //push_front(l, i+16);
    }
    printf("show the list...\n");
    list_show(l);
    l->next = reverse(l);
    //reverse_r(&l->next);
    printf("show the reversed list...\n");
    list_show(l);
    return 0;

    while (!LIST_EMPTY(l)) {
        link *n = pop_front(l);
        printf("pop: %d\n", n->value);
    }
#endif
    return 0;
}

