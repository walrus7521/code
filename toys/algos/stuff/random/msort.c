#include <stdio.h>
#include <stdlib.h>

typedef char e_v;
#include "../toys/slist.h"

#define LE(x, y) ((x) <= (y))

void msort_merge(list *first, list *second, list *out)
{
    link *p1, *p2;
    link *lastsorted;
    printf("calling merge...sz1: %d, sz2: %d\n", slist_size(first), slist_size(second));
    if (!first->front) 
        *out = *second;
    else if (!second->front) 
        *out = *first;
    else {
        p1 = first->front;
        p2 = second->front;
        if (LE(p1->value, p2->value)) {
            *out = *first;
            p1 = p1->next;
        } else {
            *out = *second;
            p2 = p2->next;
        }
        lastsorted = out->front;
        while (p1 && p2) {
            if (LE(p1->value, p2->value)) {
                lastsorted->next = p1;
                lastsorted = p1;
                p1 = p1->next;
            } else {
                lastsorted->next = p2;
                lastsorted = p2;
                p2 = p2->next;
            }
        }
        if (p1)
            lastsorted->next = p1;
        else
            lastsorted->next = p2;
    }
}

void msort_divide(list *l, list *secondhalf)
{
    link *current, *midpoint;
    printf("calling msort_divide...\n");
    if ((midpoint = l->front) == NULL) {
        secondhalf->front = NULL;
    } else {
        for (current = midpoint->next; current; ) {
            current = current->next;
            if (current) {
                midpoint = midpoint->next;
                current = current->next;
            }
        }
        secondhalf->front = midpoint->next;
        midpoint->next = NULL;
    }
}

void msort_sort(list *l)
{
    list *secondhalf = slist_init();
    if (slist_size(l) > 1) {
        msort_divide(l, secondhalf);
        slist_update_count(secondhalf);
        slist_update_count(l);
        msort_sort(l);
        msort_sort(secondhalf);
        msort_merge(l, secondhalf, l);
    }
    slist_update_count(l);
}

void msort_dump(void *l)
{
    link *list = (link *) l;
    printf("list->value = %c\n", list->value);
}

int main()
{
    list *h = slist_init();
    slist_push_back(h, 'a');
    slist_push_back(h, 'e');
    slist_push_back(h, 'z');
    slist_push_back(h, 'b');
    slist_push_back(h, 'p');
    slist_push_back(h, 'd');
    slist_push_back(h, 'l');
    slist_push_back(h, 'x');
    slist_push_back(h, 'f');
    slist_push_back(h, 'c');
    slist_push_back(h, 'g');
    slist_push_back(h, 'm');
    slist_show(h, msort_dump);
    //msort_divide(&list, &secondhalf);
    //msort_show(&secondhalf);
    //msort_show(&list);
    msort_sort(h);
    printf("show after msort\n");
    slist_show(h, msort_dump);
    return 0;
}

