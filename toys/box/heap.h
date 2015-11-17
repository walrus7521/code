#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define GE(x, y) ((x) >= (y))
#define LE(x, y) ((x) <= (y))
#define LT(x, y) ((x) < (y))

enum {
    MIN_HEAP,
    MAX_HEAP
};

typedef struct _heap {
    int *a;
    int size;
    int type;
} heap;

heap *create(int size, int type)
{
    heap *h = malloc(sizeof(heap));
    h->a = malloc(sizeof(int)*size);
    h->size = 0;
    h->type = type;
    switch (type) {
        case MIN_HEAP:
            h->a[0] = -INT_MAX;
            break;
        case MAX_HEAP:
            h->a[0] = INT_MAX;
            break;
    }
    return h;
}

int is_empty(heap *h)
{
    return (h->size == 0 ? 1 : 0);
}
 
int parent(heap *heap, int i)
{
    return (i)/2;
}

int left_child(heap *heap, int i)
{
    int left = (2 * i);
    return left;
}

int right_child(heap *h, int i)
{
    int right = (2 * i) + 1;
    return right;
}

void swap(heap *h, int x, int y)
{
    int tmp;
    tmp = h->a[x];
    h->a[x] = h->a[y];
    h->a[y] = tmp;
}

void downminheap(heap *h, int k)
{
    int child, last;
    last = h->a[k];
    while (k <= h->size/2) {
        child = left_child(h, k);
        if (child < h->size && h->a[child+1] < h->a[child] ) child++;
        if (last <= h->a[child]) break;
        h->a[k] = h->a[child];
        k = child;
    }
    h->a[k] = last;
}

int delete_min(heap *h)
{
    int min, last;
    min = h->a[1];
    last = h->a[h->size--];
    h->a[1] = last;
    downminheap(h, 1);
    return min;
}

void upminheap(heap *h, int k)
{
    int v;
    v = h->a[k];
    while(h->a[k/2] > v) {
        h->a[k] = h->a[k/2];
        k = parent(h, k);
    }
    h->a[k] = v;
}

void insert_min(heap *h, int element)
{
    h->a[++h->size] = element;
    upminheap(h, h->size);
}

void downmaxheap(heap *h, int k)
{
    int child, last;
    last = h->a[k]; /* grab max */
    while (k <= h->size/2) {
        child = left_child(h, k);
        if (child < h->size && h->a[child] < h->a[child+1]) child++;
        if (last >= h->a[child]) break;
        h->a[k] = h->a[child];
        k = child;
    }
    h->a[k] = last;
}

int delete_max(heap *h)
{
    int max, last;
    max = h->a[1];
    last = h->a[h->size--];
    h->a[1] = last;
    downmaxheap(h, 1);
    return max;
}

void upmaxheap(heap *h, int k)
{
    int v;
    v = h->a[k];
    while (h->a[k/2] <= v) {
        h->a[k] = h->a[k/2];
        k = parent(h, k);
    }
    h->a[k] = v;
}

void insert_max(heap *h, int v)
{
    h->a[++h->size] = v;
    upmaxheap(h, h->size);
}

void show(heap *h)
{
    int i;
    for (i = 0; i <= h->size; i++) {
        printf("a[%02d] = %02d\n", i, h->a[i]);
    }
}

void heapify(heap *h, int *a, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        switch (h->type) {
            case MIN_HEAP:
                insert_min(h, a[i]);
                break;
            case MAX_HEAP:
                insert_max(h, a[i]);
                break;
        }
    }
    printf("\n");
}

int heap_test()
{
    //heap *h = create(13, MIN_HEAP);
    heap *h = create(13, MAX_HEAP);
    int a[] = { 34, 5, 23, 12, 33, 98, 4, 13, 44, 37, 1, 86, 8};
    heapify(h, a, 13);
    show(h);
    while (!is_empty(h)) {
        //printf("%d ", delete_min(h));
        printf("%d ", delete_max(h));
    }
    printf("\n");
    return 0;
}

