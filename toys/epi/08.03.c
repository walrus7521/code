#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

list *reverse_sublist(list *l, int s, int f)
{
    list *r = NULL, *p = l->next, *n, *t = l->next, *q;
    // fast forward to s
    int i = 2;
    while (i <= s) {
        //printf("skip: %d\n", p->value);
        p = p->next;
        i++;
    }
    q = p;
    //printf("skip: %d\n", p->value);
    p = p->next;
    // normal reversal code
    while (p) {
        n = p->next;
        p->next = r;
        r = p;
        p = n;
    }
    // reattach top - broken
    if (s > 1) {
        q->next = r;
        r = l->next;
    }
    
    return r;
}

int main()
{
    int a[] = {0,1,2,3,4,5,6,7};
    list *l = list_create(a, 8);
    list_show(l);
    l->next = reverse_sublist(l, 2, 8);
    list_show(l);
    return 0;
}

