#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

enum {
    MIN_HEAP,
    MAX_HEAP
};

typedef struct _entry {
    char val;
    int wt;
} entry;

typedef struct _heap {
    struct _entry *e;
    int size;
    int type;
} heap;

heap *create(int size, int type)
{
    heap *h = malloc(sizeof(heap));
    h->e = malloc(sizeof(entry) * size);
    h->size = 0;
    h->type = type;
    switch (type) {
        case MIN_HEAP:
            h->e[0].wt = -INT_MAX;
            break;
        case MAX_HEAP:
            h->e[0].wt = INT_MAX;
            break;
    }
    return h;
}

static int is_empty(heap *h)
{
    return (h->size == 0 ? 1 : 0);
}

static int parent(heap *heap, int i)
{
    return (i)/2;
}

static int left_child(heap *heap, int i)
{
    int left = (2 * i);
    return left;
}

#if 0
static int right_child(heap *heap, int i)
{
    int right = (2 * i) + 1;
    return right;
}
#endif

static void downminheap(heap *h, int k)
{
    int child, last, val;
    last = h->e[k].wt; /* grab min weight */
    val  = h->e[k].val; /* grab val of min */
    while (k <= h->size/2) {
        child = left_child(h, k);
        if (child < h->size && h->e[child+1].wt < h->e[child].wt) child++;
        if (last <= h->e[child].wt) break;
        h->e[k]  = h->e[child];
        k = child;
    }
    h->e[k].wt  = last;
    h->e[k].val = val;
}

static entry *delete_min(heap *h)
{
    entry *last, *min = (entry *) malloc(sizeof(entry));
    *min = h->e[1];
    last = &h->e[h->size--];
    h->e[1] = *last;
    downminheap(h, 1);
    return min;
}

static void upminheap(heap *h, int k)
{
    int w, v;
    w = h->e[k].wt;
    v = h->e[k].val;
    while (h->e[k/2].wt > w) {
        h->e[k]  = h->e[k/2];
        k = parent(h, k);
    }
    h->e[k].wt = w;
    h->e[k].val= v;
}

static void insert_min(heap *h, char v, int w)
{
    int sz = ++h->size;
    h->e[sz].val = v;
    h->e[sz].wt = w;
    upminheap(h, h->size);
}

static void downmaxheap(heap *h, int k)
{
    int child, last, val;
    last = h->e[k].wt; /* grab max */
    val  = h->e[k].val; /* grab val of max */
    while (k <= h->size/2) {
        child = k*2;
        if (child < h->size && h->e[child].wt < h->e[child+1].wt) child++;
        if (last >= h->e[child].wt) break;
        h->e[k]  = h->e[child];
        k = child;
    }
    h->e[k].wt  = last;
    h->e[k].val = val;
}

static entry *delete_max(heap *h)
{
    entry *e_last, *e = (entry *) malloc(sizeof(entry));
    *e = h->e[1];
    e_last = &h->e[h->size--];
    h->e[1] = *e_last;
    downmaxheap(h, 1);
    return e;
}

static void upmaxheap(heap *h, int k)
{
    int w, v;
    w = h->e[k].wt;
    v = h->e[k].val;
    while (h->e[k/2].wt <= w) {
        h->e[k]  = h->e[k/2];
        k = k/2;
    }
    h->e[k].wt = w;
    h->e[k].val= v;
}

static void insert_max(heap *h, char v, int w)
{
    int sz = ++h->size;
    h->e[sz].val = v;
    h->e[sz].wt = w;
    upmaxheap(h, h->size);
}

#if 0
static void update_max_wt(heap *h, char val, int new_wt)
{
    int i;
    entry tmp;
    for (i = 1; i <= h->size; i++) {
        if (h->e[i].val == val) {
            h->e[i].wt = new_wt;
            // swap i with last
            tmp = h->e[h->size];
            h->e[h->size] = h->e[i];
            h->e[i] = tmp;
            break;
        }
    }
    upmaxheap(h, h->size);
}
#endif

void pq_insert(heap *h, char v, int w)
{
    switch (h->type) {
        case MIN_HEAP:
            insert_min(h, v, w);
            break;
        case MAX_HEAP:
            insert_max(h, v, w);
            break;
    }
}

entry *pq_delete(heap *h)
{
    switch (h->type) {
        case MIN_HEAP:
            return delete_min(h);
        case MAX_HEAP:
            return delete_max(h);
    }
    return NULL;
}

void show(heap *h)
{
    int i;
    printf("size: %d\n", h->size);
    for (i = 1; i <= h->size; i++) {
        printf("e[%02d] :v[%c]-w[%02d]\n", i, h->e[i].val, h->e[i].wt);
    }
}

int pq_test()
{
    //heap *h = create(32, MIN_HEAP);
    heap *h = create(32, MAX_HEAP);
    entry *e = NULL;
    pq_insert(h, 'a', 34);
    pq_insert(h, 'b', 5);
    pq_insert(h, 'c', 23);
    pq_insert(h, 'd', 12);
    pq_insert(h, 'e', 33);
    pq_insert(h, 'f', 98);
    pq_insert(h, 'g', 4);
    pq_insert(h, 'h', 13);
    pq_insert(h, 'i', 44);
    pq_insert(h, 'j', 37);
    pq_insert(h, 'k', 1);
    pq_insert(h, 'l', 86);
    pq_insert(h, 'm', 8);
    show(h); 
    while (!is_empty(h)) {
        e = pq_delete(h);
        printf("wt %d val %c\n", e->wt, e->val);
    }
    printf("\n");
    return 0;
}
