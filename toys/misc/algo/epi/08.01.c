#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

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

int main()
{
    list *l = list_new();
    list *f = list_new();

    push(l, 23);
    push(l, 22);
    push(l, 21);
    push(l, 9);
    push(l, 7);
    push(l, 5);
    push(l, 3);
    push(l, 1);

    push(f, 10);
    push(f, 8);
    push(f, 6);
    push(f, 4);
    push(f, 2);

    list_show(l);
    list_show(f);
    list *m = merge(l, f);
    list_show(m);
}


