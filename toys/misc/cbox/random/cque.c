#include <stdio.h>
#define QUEUESIZE 1004

typedef struct {
    int q[QUEUESIZE+1];
    int head;
    int tail;
    int count;
} queue;

void qinit(queue *q)
{
    q->head = 0;
    q->tail = QUEUESIZE-1;
    q->count = 0;
}

void enqueue(queue *q, int x)
{
    /* printf("enqueue - q->count %d\n", q->count); */
    if (q->count >= QUEUESIZE)
        printf("warning: queue overflow\n");
    else {
        q->tail = (q->tail+1) % QUEUESIZE;
        q->q[q->tail] = x;
        q->count++;
        //printf("enqueueing: %s @ %d\n", q->q[q->tail], q->tail);
    }
}

int dequeue(queue *q)
{
    int x = -1;
    /* printf("dequeue - q->count %d\n", q->count); */
    if (q->count <= 0)
        printf("warning: queue is empty\n");
    else {
        x = q->q[q->head];
        //printf("dequeueing %s from %d\n", x, q->head);
        q->head = (q->head+1) % QUEUESIZE;
        q->count--;
    }
    return x;
}

void qshow(queue *q)
{
    int i;
    for (i = 0; i < q->count; i++) {
        printf("queue[%d] = %d\n", i, q->q[i]);
    }
}

int qempty(queue *q)
{
    if (q->count <= 0) return 1;
    return 0;
}

int main()
{
    int i;
    queue q;
    qinit(&q);
    for (i = 0; i < 16; i++) {
        enqueue(&q, i);
    }
    while (!qempty(&q)) {
        int x = dequeue(&q);
        printf("dequeued: %d\n", x);
    }

    return 0;
}
