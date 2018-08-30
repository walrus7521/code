#include <stdio.h>
#include <stdlib.h>



#define LT(a,b) (a < b)
void swap(int *a, int i, int j) {
    int tmp;
    tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void show(int *A, int sz) {
    int i;
    for (i = 0; i < sz; ++i) {
        printf("S[%d] = %d, ", i, A[i]);
    }
    printf("\n");
}

int divide(int *A, int sz) {
    int part;
    if (sz % 2) part=(sz/2)+1;
    else part=sz/2;
    return part;
}


int *combine(int *A, int szA, int *B, int szB) {
    int i=0, j=0, k, *c;
    c = (int *) malloc(szA+szB);
    for (i = 0; i < szA; ++i) {
        c[i] = A[i];
    }
    for (j = 0; j < szB; ++j, ++i) {
        c[i] = B[j];
    }
    /* ainsert */
    for (i = 1; i < szA+szB; ++i) {
          for (k = i; k > 0; k--) {
              if (LT(c[k],c[k-1])) {
                  swap(c, k, k-1);
              }
          }
    }
    return c;
}

int *Mergesort(int *A, int sz) {
    int m, *low, *high, *comb;
    if (sz > 1) {
        m = divide(A, sz);
        low = A; high = A+m;
        Mergesort(low, m);
        Mergesort(high, sz-m);
        comb = combine(low, m, high, sz-m);
    }
    return comb;
}

void msorta_test()
{
    int a[] = {26,33,35,29,19,12,22,15,42,69,1};
    int *sorted;
    int sz = sizeof(a) / sizeof(a[0]);
    show(a, sz);
    sorted = Mergesort(a, sz);
    show(sorted, sz);
}


#include "slist.h"

#define LE(x, y) ((x) <= (y))

void mergel(list *first, list *second, list *out)
{
    link *p1, *p2;
    link *lastsorted;
    printf("calling merge...\n");
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

void dividel(list *l, list *secondhalf)
{
    link *current, *midpoint;
    printf("calling divide...\n");
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

void msortl(list *l)
{
    list *secondhalf = slist_init();
    if (slist_size(l) > 1) {
        dividel(l, secondhalf);
        slist_update_count(secondhalf);
        slist_update_count(l);
        msortl(l);
        msortl(secondhalf);
        mergel(l, secondhalf, l);
    }
    slist_update_count(l);
}

void mdump(void *l)
{
    link *list = (link *) l;
    printf("list->value = %c\n", list->value);
}

void msortl_test()
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
    slist_show(h, mdump);
    //divide(&list, &secondhalf);
    //show(&secondhalf);
    //show(&list);
    msortl(h);
    printf("show after msort\n");
    slist_show(h, mdump);
}

