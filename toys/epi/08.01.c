#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef int e_v;
#include "../toys/slist.h"

list *merge(list *first, list *second)
{
    list *m;
    link *fl, *sl;
    if (slist_empty(first)) return second;
    if (slist_empty(second)) return first;
    m = slist_init();
    fl = first->front;
    sl = second->front;
    while (fl && sl) {
        if (fl->value < sl->value) {
            slist_push_back(m, fl->value);
            fl = fl->next;
        } else
        if (fl->value == sl->value) {
            slist_push_back(m, fl->value);
            slist_push_back(m, sl->value);
            fl = fl->next;
            sl = sl->next;
        } else {
            slist_push_back(m, sl->value);
            sl = sl->next;
        }
    }
    if (fl) {
        while (fl) {
            slist_push_back(m, fl->value);
            fl = fl->next;
        }
    } else
    if (sl) {
        while (sl) {
            slist_push_back(m, sl->value);
            sl = sl->next;
        }
    }
    return m;
}

void mydump(void *l)
{
    link *list = (link *) l;
    printf("list->value = %d\n", list->value);
}

int main()
{
    int i, x;
    list *first = slist_init();
    list *second = slist_init();
    list *m;

    slist_push_back(first, 0);
    slist_push_back(first, 2);
    slist_push_back(first, 4);
    slist_push_back(first, 6);
    slist_push_back(first, 8);
    slist_show(first, mydump);

    slist_push_back(second, 1);
    slist_push_back(second, 3);
    slist_push_back(second, 5);
    slist_push_back(second, 7);
    slist_push_back(second, 9);
    slist_show(second, mydump);

    m = merge(first, second);
    slist_show(m, mydump);

    return 0;
}
