#ifndef _queue_h_
#define _queue_h_

#include <stdio.h>
#define QUEUESIZE 1004

//typedef int opcode;
typedef char opcode[4];

typedef struct {
    opcode q[QUEUESIZE+1];
    int head;
    int tail;
    int count;
} queue;

void queue_init(queue *q)
{
    q->head = 0;
    q->tail = QUEUESIZE-1;
    q->count = 0;
}

void enqueue(queue *q, opcode *x)
{
    /* printf("enqueue - q->count %d\n", q->count); */
    if (q->count >= QUEUESIZE)
        printf("warning: queue overflow\n");
    else {
        q->tail = (q->tail+1) % QUEUESIZE;
        memcpy(&q->q[q->tail], x, 4);
        q->count++;
        //printf("enqueueing: %s @ %d\n", q->q[q->tail], q->tail);
    }
}

opcode *dequeue(queue *q)
{
    opcode *x = NULL;
    /* printf("dequeue - q->count %d\n", q->count); */
    if (q->count <= 0)
        printf("warning: queue is empty\n");
    else {
        x = &q->q[q->head];
        //printf("dequeueing %s from %d\n", x, q->head);
        q->head = (q->head+1) % QUEUESIZE;
        q->count--;
    }
    return x;
}

void queue_show(queue *q)
{
    int i;
    for (i = 0; i < q->count; i++) {
        printf("queue[%d] = %s\n", i, q->q[i]);
    }
}

int queue_empty(queue *q)
{
    if (q->count <= 0) return 1;
    return 0;
}

#endif
