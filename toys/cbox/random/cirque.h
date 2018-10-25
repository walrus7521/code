#include <stdio.h>
#include <stdlib.h>

typedef char q_entry;
typedef struct {
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
        printf("Cannot append an entry to a full queue.");
    } else {
        q->count++;
        q->tail = (q->tail + 1) % q->size;
        q->entry[q->tail] = item;
    }
}

void cqget(q_entry *item, queue *q)
{
    if (cqempty(q)) {
        printf("Cannot server from an empty queue.");
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

void cqshow(queue *q, void (*Visit)())
{
    int i, cnt;
    printf("head %d, tail %d\n", q->head, q->tail);
    i = q->head;
    cnt = 0;
    while (cnt < q->count) {
        printf("%d -> %c\n", i, q->entry[i]);
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
    cqshow(&que, NULL);
    while (!cqempty(&que)) {
        cqget(&item, &que);
        putchar(item);
    }
}
