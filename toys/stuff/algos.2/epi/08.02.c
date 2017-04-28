#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

list *reverse(list *l)
{
    list *r = NULL, *p = l->next, *n;
    while (p) {
        n = p->next;
        p->next = r;
        r = p;
        p = n;
    }
    return r;
}

int main()
{
    int a[] = {0,1,2,3,4,5,6,7};
    list *l = list_create(a, 8);
    list_show(l);
    l->next = reverse(l);
    list_show(l);
    return 0;
}


