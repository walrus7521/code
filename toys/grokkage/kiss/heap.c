#include "types.h"

/* max heap
 */

heap_t *new()
{
    heap_t *heap = malloc(sizeof(heap_t));
    heap->h[0] = INT_MAX;
    heap->size = 0;
    return heap;
}

void sift_down(heap_t *h)
{
    int k = 1;
    int child, last;
    last = h->h[k];
    while (k <= h->size/2) {
        child = 2 * k;
        if (child < h->size && h->h[child] < h->h[child+1]) child++;
        if (last >= h->h[child]) break;
        h->h[k] = h->h[child];
        k = child;
    }
    h->h[k] = last;
}

void sift_up(heap_t *h)
{
    int k = h->size;
    int v = h->h[k];
    while (h->h[k/2] <= v) {
        h->h[k] = h->h[k/2];
        k /= 2;
    }
    h->h[k] = v;
}

void insert(heap_t *h, int key)
{
    h->size++;
    h->h[h->size] = key;
    sift_up(h);
}

int delete(heap_t *h)
{
    int max = h->h[1];
    h->h[1] = h->h[h->size--]; // copy bottom to top
    sift_down(h);
    return max;
}

int is_empty(heap_t *h)
{
    return (h->size) ? 0 : 1;
}

void show(heap_t *h)
{
    for (int i = 1; i <= h->size; i++) printf("a[%02d] = %02d\n", i, h->h[i]);
}

int main()
{
    int a[] = { 34, 5, 23, 12, 33, 98, 4, 13, 44, 37, 1, 86, 8};
    int len = sizeof(a) / sizeof(a[0]);

    heap_t *h = new();
    for (int i = 0; i < len; i++) {
        insert(h, a[i]);
    }
    show(h);

    while (!is_empty(h)) {
        int max = delete(h);
        printf("max: %d\n", max);
    }
}

