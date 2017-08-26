#include <stdio.h>
#include <stdlib.h>
#include "slist.h"



int main()
{
    list *l = list_new();

    push(l, 23);
    push(l, 22);
    push(l, 21);
    push(l, 9);
    push(l, 7);
    push(l, 5);
    push(l, 3);
    push(l, 1);

    list_show(l);
}
