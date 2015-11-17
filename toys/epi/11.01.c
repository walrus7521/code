#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../toys/heap.h"

int *merge_arrays(int *a, int a_sz, int *b, int b_sz, int *c, int c_sz)
{
    heap *h = create(a_sz + b_sz + c_sz, MIN_HEAP);
    int *r = malloc(sizeof(int) * (a_sz + b_sz + c_sz));
    int i;
    for (i = 0; i < a_sz; i++) insert_min(h, a[i]);
    for (i = 0; i < b_sz; i++) insert_min(h, b[i]);
    for (i = 0; i < c_sz; i++) insert_min(h, c[i]);
    i = 0;
    while (!is_empty(h)) r[i++] = delete_min(h);
    return r;
}

int main()
{
    int a[] = { 34, 5, 23, 12, 33, 98, 4, 13, 44, 37, 1, 86, 8};
    int b[] = { 34, 5, 23, 12, 33, 98, 4, 13, 44, 37, 1, 86, 8};
    int c[] = { 34, 5, 23, 12, 33, 98, 4, 13, 44, 37, 1, 86, 8};
    int *r = merge_arrays(a, 13, b, 13, c, 13);
    if (r) {
        int i;
        for (i = 0; i < 13 * 3; i++) 
            printf("r[%d] = %d\n", i, r[i]);
    }
    return 0;
}

