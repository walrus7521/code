#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define GE(x, y) ((x) >= (y))
#define LE(x, y) ((x) <= (y))
#define LT(x, y) ((x) < (y))

typedef struct _heap {
    int *a;
    int size;
} heap;

heap *create(int size)
{
    heap *h = malloc(sizeof(heap));
    h->a = malloc(sizeof(int)*size);
    h->size = 0;
    h->a[0] = -INT_MAX;
    return h;
}

int is_empty(heap *h)
{
    return (h->size == 0 ? 1 : 0);
}
 
void down_min(heap *h, int k)
{
    int child, last;
    last = h->a[k];
    while (k <= h->size/2) {
        child = 2 * k;
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
    down_min(h, 1);
    return min;
}

void up_min(heap *h, int k)
{
    int v;
    v = h->a[k];
    while(h->a[k/2] > v) {
        h->a[k] = h->a[k/2];
        k = k / 2;
    }
    h->a[k] = v;
}

void insert_min(heap *h, int element)
{
    h->a[++h->size] = element;
    up_min(h, h->size);
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
        insert_min(h, a[i]);
    }
    printf("\n");
}

int main()
{
    heap *h = create(13);
    int a[] = { 34, 5, 23, 12, 33, 98, 4, 13, 44, 37, 1, 86, 8};
    heapify(h, a, 13);
    show(h);
    while (!is_empty(h)) {
        printf("%d ", delete_min(h));
    }
    printf("\n");
    return 0;
}

