#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

// {11,11,7,5,3,2,2}; k = 3 becomes
// {3,2,2,11,7,5,11};
list *reverse_sublist_k_at_a_time(list *l, int k)
{
    return NULL;
}

int main()
{
    int a[] = {11,11,7,5,3,2,2};
    list *l = list_create(a, 7);
    list_show(l);
    l->next = reverse_sublist_k_at_a_time(l, 3);
    list_show(l);
    return 0;
}

