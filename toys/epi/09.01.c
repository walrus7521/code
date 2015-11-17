#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef int e_v;
#include "../toys/slist.h"

void mydump(void *l)
{
    link *list = (link *) l;
    printf("list->value = %d\n", list->value);
}

int main()
{
    int i, x;
    list *s = slist_init();
    link *tlnk;

    slist_push_front(s, 11);
    slist_push_front(s, 2);
    slist_push_front(s, 333);
    slist_push_front(s, 4);
    slist_push_front(s, 55);
    slist_push_front(s, 6);
    slist_push_front(s, 7);
    slist_push_front(s, 88);

    slist_show(s, mydump);

    printf("max = %d\n", slist_max(s)->max);
    printf("pop = %d\n", slist_pop_front(s)->value);
    printf("pop = %d\n", slist_pop_front(s)->value);
    printf("pop = %d\n", slist_pop_front(s)->value);
    printf("pop = %d\n", slist_pop_front(s)->value);
    printf("pop = %d\n", slist_pop_front(s)->value);
    printf("pop = %d\n", slist_pop_front(s)->value);
    printf("pop = %d\n", slist_pop_front(s)->value);
    printf("max = %d\n", slist_max(s)->max);

    return 0;
}
