#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* #define dprintf printf */
#define dprintf(...)

/***** HEAP *******/
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

void hclear(heap *h)
{
    h->size = 0;
    h->a[0] = -INT_MAX;
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
        dprintf("a[%02d] = %02d\n", i, h->a[i]);
    }
}

void heapify(heap *h, int *a, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        insert_min(h, a[i]);
    }
    dprintf("\n");
}

/********** CIRQUE ***********/

typedef int q_entry;
typedef struct queue {
    int count;
    int head;
    int tail;
    int size;
    q_entry *entry;
} queue;

void cqinit(queue *q, int size)
{
    q->count = 0;
    q->head = 0;
    q->tail = -1;
    q->size = size;
    q->entry = (q_entry *) malloc(size * sizeof(q_entry));
}

int cqempty(queue *q)
{
    return (q->count <= 0);
}

int cqfull(queue *q)
{
    return (q->count >= q->size);
}

void cqput(q_entry item, queue *q)
{
    if (cqfull(q)) {
        dprintf("Cannot append an entry to a full queue.");
    } else {
        q->count++;
        q->tail = (q->tail + 1) % q->size;
        q->entry[q->tail] = item;
    }
}

void cqget(q_entry *item, queue *q)
{
    if (cqempty(q)) {
        dprintf("Cannot server from an empty queue.");
    } else {
        q->count--;
        *item = q->entry[q->head];
        q->head = (q->head + 1) % q->size;
    }
}

int cqcount(queue *q)
{
    return q->count;
}

void cqclear(queue *q)
{
    q->count = 0;
    q->head = 0;
    q->tail = -1;
}

void cqhead(q_entry *item, queue *q)
{
    *item = q->entry[q->head];	    
}

void cqtail(q_entry *item, queue *q)
{
    *item = q->entry[q->tail];
}

void cqshow(queue *q)
{
    int i, cnt;
    dprintf("head %d, tail %d\n", q->head, q->tail);
    i = q->head;
    cnt = 0;
    while (cnt < q->count) {
        dprintf("%2d -> %2d\n", i, q->entry[i]);
        i = (i + 1) % q->size;
        cnt++;
    }
}

void cirque_test()
{
    queue que;
    q_entry item;
    cqinit(&que, 10);
    while (!cqfull(&que) && (item = (q_entry) getchar()) != '\n') {
        cqput(item, &que);
    }
    cqshow(&que);
    while (!cqempty(&que)) {
        cqget(&item, &que);
        putchar(item);
    }
}

/********** SORT **********************/
void isort(int a[], int n)
{
    int c, d, t;
    for (c = 1 ; c <= n - 1; c++) {
        d = c;
        while ( d > 0 && a[d] < a[d-1]) {
            t = a[d];
            a[d] = a[d-1];
            a[d-1] = t;
            d--;
        }
    }    
}

void show_a(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++) 
        dprintf("a[%d] = %d\n", i, a[i]);
}

/********* MAIN PROBLEM ***************/
/*
 * #include "queue.h"
 * #include "heap.h"
 * #include "sort.h"
 */

void clear_order(int a[], int len)
{
    int i;
    for (i = 0; i < len; i++)
        a[0] = 0;
}

void show_order(int a[], int len)
{
    int i, k = 0, d = len/3;
    dprintf("len: %d, d: %d\n", len, d);
    for (i = 0, k = 0; i < len; i+=3, k++) {
        printf("%d %d\n", a[i], a[i+1]);
        dprintf("k::%d - d::%d\n", k, d);
        if (k != d)
            printf("%d\n", a[i+2]);
    }
}

#define MAX_LEN 1004
#define MAX(a, b) ((a) > (b) ? (a) : (b))
int order[MAX_LEN];
int order_in;
int main()
{
    int i, j, t, accum, ncases = 0, num_people = 4;
    queue q;
    heap *h;

    /*
     * if there are only 3 items, quick calculation
     * on sorted array.
     */

    /*
     * otherwise it is a series...
     * ...no need to actually use data structures...
     */
    h = create(MAX_LEN);
    cqinit(&q, MAX_LEN);
    scanf("%d\n", &ncases);
    for (i = 0; i < ncases; i++) {
        clear_order(order, MAX_LEN);
        order_in = 0;
        cqclear(&q);
        hclear(h);
        scanf("%d\n", &num_people);
        dprintf("case %d - num people %d\n", i, num_people);
        for (j = 0; j < num_people; j++) {
            scanf("%d\n", &t);
            dprintf("  t = %d\n", t);
            cqput(t, &q);
        }
        isort(q.entry, num_people);
        accum = 0;
        while (1) {
            int c1, c2, s;
            if (q.count == 0) goto end;
            if (q.count <= 2) {
                if (q.count == 1) {
                    dprintf("count == 1\n");
                    cqget(&c1, &q);
                    accum += c1;
                    order[order_in++] = c1;
                    insert_min(h, c1);
                    goto end;
                } else {
                    cqget(&c1, &q);
                    insert_min(h, c1);
                    cqget(&c2, &q);
                    dprintf("crossed final 2: %d %d\n", c1, c2);
                    order[order_in++] = c1;
                    order[order_in++] = c2;
                    accum += MAX(c1, c2);
                    insert_min(h, c2);
                    goto end;
                }
            }
            cqget(&c1, &q);
            insert_min(h, c1);
            cqget(&c2, &q);
            insert_min(h, c2);
            dprintf("crossed: %d %d\n", c1, c2);
            order[order_in++] = c1;
            order[order_in++] = c2;
            accum += MAX(c1, c2);
            s = delete_min(h);
            dprintf("shuttle: %d\n", s);
            order[order_in++] = s;
            accum += s;
            cqput(s, &q);
        }
end:
        printf("%d\n", accum);
        show_order(order, order_in);
        if (i < ncases - 1) printf("\n");
    }
    return 0;
    /*
     * 1. sort array
     * - if only 1 or 2 in array goto 8
     * 2. pop_front 2 <-- still may fail, use queue counter?
     * 3. if queue empty goto 8 -- halting condition
     * 4. add both to heap and accumulate 2
     * 5. get_min heap 
     * 6. push_back and accumulate 1
     * 7. goto 2
     * 8. add to heap and accumulate
     * 9. print accumulator
     */
    return 0;
}

