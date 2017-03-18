#include <stdio.h>
#include <stdlib.h>

#define qprintf printf
//#define qprintf(...)

//typedef void* e_v;
typedef int e_v;

typedef struct _link {
    struct _link *next;
    e_v value;
} link;

typedef struct {
    int count;
    link *front, *rear;
} list, queue;
#define slist_empty(head) ((head)->count == 0)

list *slist_init()
{
    list *h = (list *) malloc(sizeof(list));
    h->front = h->rear = NULL;
    h->count = 0;
    return h;
}

void queue_show(queue *head)
{
    link *list = head->front;
    if (slist_empty(head)) {
        qprintf("list is empty\n");
            return;
    }
    while (list) {
        qprintf("value => %d\n", list->value);
        list = list->next;
    }
}

void enqueue(queue *q, e_v x)
{
    link *t = (link *) malloc(sizeof(link));
    qprintf("enqueue %d\n", x);
    t->value = x;    
    t->next = NULL;
    if (slist_empty(q)) {
        q->front = q->rear = t;
    } else {
        q->rear->next = t;
        q->rear = t;
    }
    q->count++;
}

link *dequeue(queue *q)
{
    e_v x;
    link *t;
    if (slist_empty(q)) return NULL; //-1;
    t = q->front;
    q->front = q->front->next;
    q->count--;
    if (slist_empty(q)) q->rear = NULL;
    x = t->value;
    //free(t);
    qprintf("dequeue %d\n", x);
    return t;
}

void init_queue(queue *q)
{
    q->front = q->rear = NULL;
    q->count = 0;
}

int queue_empty(queue *q)
{
    return (slist_empty(q));
}

void queue_test()
{
    int i;
    queue *q = slist_init();
    for (i = 0; i < 8; i++) {
        enqueue(q, i);
    }
    queue_show(q);
    while (!queue_empty(q)) {
        link *n = dequeue(q);
    }
}
