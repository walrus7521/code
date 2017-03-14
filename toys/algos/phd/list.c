#include <stdio.h>
#include <stdlib.h>

typedef struct _link {
    struct _link *next, *tail;
    int value;
} link, list;

#define LIST_EMPTY(list) (list->tail == NULL)

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

link *list_new(int value)
{
    link *n = (link *) malloc(sizeof(link));
    n->next = n->tail = NULL;
    n->value = value;
    return n;
}

void push_back(list *head, int value)
{
    link *n = list_new(value);
    if (head->tail) {
        head->tail->next = n;
    } else {
        n->next = head->next;
        head->next = n;
    }
    head->tail = n;
}

int push_front(list *head, int value)
{
    link *n = list_new(value);
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
    list *m = list_new(-1);
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
    list *m = list_new(-1);
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

int has_loop(list *l)
{
    list *slow_p = l, *fast_p = l;
    while (slow_p && fast_p && fast_p->next) {
        slow_p = slow_p->next;
        fast_p  = fast_p->next->next;
        if (slow_p == fast_p) {
            //removeLoop(slow_p, list);
            return 1; // found loop
        }
    }
    return 0; // no loop
}

int main()
{
#if 0
    // test merge
    list *l = list_new(-1);
    list *f = list_new(-1);
    int i;
    for (i = 0; i < 8; i++) {
        push_back(l, 2*i);
        push_back(f, (2*i+1));
    }
    list_show(l);
    list_show(f);
    //printf("merge: \n");
    //list *m = merge(l, f);
    printf("zip: \n");
    list *z = zip(l, f);
    list_show(z);
    // create a loop
    //l->next->next->next->next->next = l->next->next;
    //printf("loop? %d\n", has_loop(l));
#endif
#if 1
    int i;
    list *l = list_new(-1);
    list *r = list_new(-1);
    for (i = 0; i < 8; i++) {
        push_back(l, i);
        //push_front(l, i+16);
    }
    printf("show the list...\n");
    list_show(l);
    printf("reverse: \n");
    l->next = reverse(l);
    printf("show the reversed list...\n");
    list_show(l);

    while (!LIST_EMPTY(l)) {
        link *n = pop_front(l);
        printf("pop: %d\n", n->value);
    }
#endif
    return 0;
}

