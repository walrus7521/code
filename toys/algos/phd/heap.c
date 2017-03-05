#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *h;
    int hcount; /* num elements in heap */
} heap;

heap *new(int sz) {
    int i;
    heap *h = (heap *) malloc(sizeof(heap));
    h->h = (int *) malloc((sz+1)*sizeof(int));
    h->hcount = 0;
    for (i = 0; i <= sz; ++i) h->h[i] = 0;
    return h;
}

void delete(heap *h) {
    if (h && h->h) {
        free(h->h);
        free(h);
    }
}

void swap(int *a, int i, int j) {
    int tmp;
    //printf("swap(a[%d]:%d, a[%d]:%d)\n", i, a[i], j, a[j]);
    tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

int less(int *a, int i, int j) {
    if (a[i] < a[j]) return 1;
    return 0;
}

int greater(int *a, int i, int j) {
    if (a[i] > a[j]) return 1;
    return 0;
}

void printtree(int s[], int count) {
    int i, level, j, k;
    int lvl[] = {0, 1,  2,  2,  4,  4,  4,  4, \
                    8,  8,  8,  8,  8,  8,  8,  8, \
                   16, 16, 16, 16, 16, 16, 16, 16, \
                   16, 16, 16, 16, 16, 16, 16, 16, 16};
    for (i = 1; i <= count; ) {
        level = lvl[i];
        switch (level) {
            case 1: printf("        "); break;
            case 2: printf("      "); break;
            case 4: printf("  "); break;
        }
        //printf("lvl %d i=%d\n", level, i);
        for (j = i, k = 1; (k <= level) && (i <= count); ++k, ++j) {
            printf("[%d] ", s[j]);
            ++i;
        }
        printf("\n");
    }
}

void show(int *a, int sz) {
    int i;
    for (i = 1; i <= sz; ++i) {
        printf("[%d] , ", a[i]);
    }
    printf("\n");
}

void min_siftdown(heap *h) {
    int i = 1, l, r, pos;
    i = 1;
    while (i <= h->hcount) {
        l = 2*i;
        r = l+1;
        if (greater(h->h, l, r)) pos = r;
        else pos = l;
        if ((l <= h->hcount) && (greater(h->h, i, pos))) {
            swap(h->h, i, pos);
            i = pos;
        } else {
            break;
        }
    }
}

void max_siftdown(heap *h) {
    int i = 1, l, r, pos;
    i = 1;
    while (i <= h->hcount) {
        l = 2*i;
        r = l+1;
        if (greater(h->h, l, r)) pos = l;
        else pos = r;
        if ((l <= h->hcount) && (less(h->h, i, pos))) {
            swap(h->h, i, pos);
            i = pos;
        } else {
            break;
        }
    }
}

void min_siftup(heap *h)
{
    int i = h->hcount;
    int x;
    x = h->h[h->hcount];
    while (i > 1) {
        if (less(h->h, i, i/2)) swap(h->h, i, i/2);
        i /=2;
    }
}

void max_siftup(heap *h)
{
    int i = h->hcount;
    int x;
    x = h->h[h->hcount];
    while (i > 1) {
        if (greater(h->h, i, i/2)) swap(h->h, i, i/2);
        i /=2;
    }
}

int peekmax(heap *h) {
    return h->h[1];
}

int peekmin(heap *h) {
    return h->h[1];
}

int getmin(heap *h) {
    int min = h->h[1];
    h->h[1] = h->h[h->hcount];
    h->hcount--;
    min_siftdown(h);
    return min;
}

int getmax(heap *h) {
    int max = h->h[1];
    h->h[1] = h->h[h->hcount];
    h->hcount--;
    max_siftdown(h);
    return max;
}

void min_insert(heap *h, int x) {
    h->hcount++;
    h->h[h->hcount] = x;
    min_siftup(h);
}

void max_insert(heap *h, int x) {
    h->hcount++;
    h->h[h->hcount] = x;
    max_siftup(h);
}

void max_test()
{
    //int x[] = {1,3,5,7,2,4,6,8};
    int key[] = { 34, 5, 23, 12, 33, 98, 4, 13, 44, 37, 1, 86, 8};
    int i, sz=sizeof(key)/sizeof(key[0]), max;
    heap *h = new(sz);
    for (i = 0; i < sz; i++) max_insert(h, key[i]);
    printtree(h->h, h->hcount);
    printf("\n");
    while (h->hcount) {
        max = getmax(h);
        printf("max = %d\n", max);
        printtree(h->h, h->hcount);
    }
    printf("\n");
    delete(h);
}

void min_test()
{
    //int x[] = {1,3,5,7,2,4,6,8};
    int key[] = { 34, 5, 23, 12, 33, 98, 4, 13, 44, 37, 1, 86, 8};
    int i, sz=sizeof(key)/sizeof(key[0]), min;
    heap *h = new(sz);
    for (i = 0; i < sz; i++) min_insert(h, key[i]);
    printtree(h->h, h->hcount);
    printf("\n");
    while (h->hcount) {
        min = getmin(h);
        printf("min = %d\n", min);
        printtree(h->h, h->hcount);
    }
    printf("\n");
    delete(h);
}

int main()
{
    min_test();
    max_test();
    return 0;
}

