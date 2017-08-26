#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//#define dprintf printf
#define dprintf(...)

/* Queue - Begin
 */

typedef struct _link {
    struct _link *next;
    int value;
} link;

typedef struct {
    int count;
    link *front, *rear;
} queue;
#define queue_empty(head) ((head)->count == 0)

void enqueue(queue *q, int x)
{
    dprintf("enqueue %d\n", x);
    link *t = (link *) malloc(sizeof(link));
    t->value = x;    
    t->next = NULL;
    if (queue_empty(q)) {
        q->front = q->rear = t;
    } else {
        q->rear->next = t;
        q->rear = t;
    }
    q->count++;
}

int dequeue(queue *q)
{
    int x;
    link *t;
    if (queue_empty(q)) return -1;
    t = q->front;
    q->front = q->front->next;
    q->count--;
    if (queue_empty(q)) q->rear = NULL;
    x = t->value;
    free(t);
    dprintf("dequeue %d\n", x);
    return x;
}

void init_queue(queue *q)
{
    q->front = q->rear = NULL;
    q->count = 0;
}

/* Queue - End
 */

/* 
 *  perform BFS
 *  ===========
 *  0. implicit graph
 *  1. convert all forbidden numbers to nums
 *  2. mark all forbidden numbers as visited
 *  3. record destination
 *  4. there are a total of 10,000 states
 *  5. perform bfs
 *  6. for each dequeued value
 *  7. check for halting condition (= destination)
 *  8. compute all 8 child states and queue
 *
 */


#define MAXV        10002

int visited[MAXV];
int press_cnt[MAXV];

void disassemble(int p, int d[4])
{
    int i;
    dprintf("parent:      %d\n", p);
    for (i = 0; i < 4; i++) {
        d[i] = p % 10;
        p /= 10;
    }
    dprintf("disassemble: ");
    for (i = 3; i >= 0; i--) {
        dprintf("%d ", d[i]);
    }
    dprintf("\n");
}

int reassemble(int d[4])
{
    int i, p;
    for (p = i = 0; i < 4; i++) {
        p += pow(10, i) * d[i];
    }
    dprintf("reassembled: %d\n", p);
    return p;
}

int reassemble_rev(int d[4])
{
    int i, p;
    for (p = i = 0; i < 4; i++) {
        p += pow(10, 3-i) * d[i];
    }
    dprintf("reassembled: %d\n", p);
    return p;
}

void rollup(queue *q, int p, int d[4])
{
    int i, v, t;
    dprintf("roll up:\n");
    for (i = 0; i < 4; i++) {
        t = d[i]; /* save original */
        ++d[i];
        d[i] %= 10;
        v = reassemble(d);
        if (!visited[v]) enqueue(q, v);
        press_cnt[v] = press_cnt[p] + 1;;
        d[i] = t; /* restore original */
    }
}

void rolldown(queue *q, int p, int d[4])
{
    int i, v, t;
    dprintf("roll down\n");
    for (i = 0; i < 4; i++) {
        t = d[i];
        if (t == 0) d[i] = 9;
        else --d[i];
        v = reassemble(d);
        if (!visited[v]) enqueue(q, v);
        press_cnt[v] = press_cnt[p] + 1;;
        d[i] = t;
    }
}

int gen_children(int start, int dest)
{
    int d[4], v, p, found;
    queue q;
    dprintf("start %d, search for %d\n", start, dest);
    init_queue(&q);
    p = start;
    enqueue(&q, p);
    while (!queue_empty(&q)) {
        v = dequeue(&q);
        if (visited[v]) continue;
        visited[v] = 1;
        dprintf("dequeued: %d\n", v);
        if (v == dest) {
            dprintf("found it!!! %d, press count %d\n", dest, press_cnt[dest]);
            return press_cnt[dest];
        }
        disassemble(v, d);
        rollup(&q, v, d);
        rolldown(&q, v, d);
    }
    return 0;
}

void init()
{
    int i;
    for (i = 0; i < MAXV; i++) {
        visited[i] = 0;
        press_cnt[i] = 0;
    }
}

int get_num()
{
    int i, a[4], x;
    for (i = 0; i < 4; i++) scanf("%d ", &a[i]);
    x = reassemble_rev(a);
    return x;
}

void scan_excludes(int n)
{
    int i, x;
    for (i = 0; i < n; i++) {
        x = get_num();
        visited[x] = 1;
        dprintf("x = %04d\n", x);
    }
}

int main()
{
    int start, dest, nr_cases, nr_exclude, i, nump;

    scanf("%d\n\n", &nr_cases);
    dprintf("num cases: %d\n", nr_cases);
    for (i = 0; i < nr_cases; i++) {
        init();
        start = get_num();
        dest = get_num();
        scanf("%d\n", &nr_exclude);
        dprintf("start: %d, dest: %d, num to exclude: %d\n", start, dest, nr_exclude);
        scan_excludes(nr_exclude);
        nump = gen_children(start, dest);
        if (nump) {
            dprintf("found path %d\n", nump);
            printf("%d\n", nump);
        } else {
            dprintf("path does not exist\n");
            printf("%d\n", -1);
        }
    }
    return 0;
}
