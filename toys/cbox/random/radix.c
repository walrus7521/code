#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

//#define dprintf printf
#define dprintf(...)

#define MAXQUEUEARRAY 28
#define KEYSIZE 3

typedef struct _link {
    struct _link *next;
    char entry[KEYSIZE+1];
} Link, Node;

typedef struct {
    int count;
    Link *front, *rear;
} List, Queue;

void CreateQueue(Queue *q)
{
    q->front = q->rear = NULL;
    q->count = 0;
}

int ListEmpty(List *list)
{
    return (list->count > 0) ? 0 : 1;
}

int QueueEmpty(Queue *que)
{
    return ListEmpty(que);
}

void ListShow(List *list)
{
    Node *x;
    if (ListEmpty(list)) return;
    x = list->front;
    while (x) {
        printf("-> %s\n", x->entry);
        x = x->next;
    }
}

void DeleteList(int position, Link **x, List *list)
{
    Link *t;
    t = list->front;
    list->front = list->front->next;
    list->count--;
    if (ListEmpty(list)) list->rear = NULL;
    *x = t;
}

void AppendNode(Link *x, Queue *que)
{
    if (QueueEmpty(que)) {
        que->front = que->rear = x;
    } else {
        que->rear->next = x;
        que->rear = que->rear->next;
    }
    que->count++;
    dprintf("appended %s\n", x->entry);
}

int ListSize(List *list)
{
    return list->count;
}

void ServeNode(Node **x, Queue *que)
{
    if (QueueEmpty(que))
        dprintf("error queue is empty...\n");
    else {
        *x = que->front;
        que->front =que->front->next;
        que->count--;
        if (QueueEmpty(que))
            que->rear = NULL;
    }
    dprintf("ServeNode...%s\n", (*x)->entry);
}

void SetPosition(int p, List *list, Node **current)
{
    int count;
    Node *q;
    if (p < 0 || p >= list->count)
        dprintf("error bad position\n");
    else {
        q = list->front;
        for (count = 1; count <= p; count++)
            q = q->next;
        *current = q;
    }
}

void InsertListTail(Node *x, List *list)
{
    Node *newnode = (Node *) malloc(sizeof(Node));
    newnode->next = NULL;
    strcpy(newnode->entry, x->entry);
    if (ListEmpty(list)) {
        list->front = list->rear = newnode;
    } else {
        list->rear->next = newnode;
        list->rear = newnode;
    }
    list->count++;
}

void InsertList(int p, Node *x, List *list)
{
    Node *newnode, *current;
    if (p < 0 || p > list->count)
        dprintf("error inserting bad position\n");
    else {
        newnode = (Node *) malloc(sizeof(Node));
        newnode->next = NULL;
        if (p == 0) {
            newnode->next = list->front;
            list->front = newnode;
        } else {
            SetPosition(p-1, list, &current);
            newnode->next = current->next;
            current->next = newnode;
        }
        list->count++;
    }
}

void Rethread(List *list, Queue queues[])
{
    int i;
    Node *x;
    dprintf("rethreading...\n");
    for (i = 0; i < MAXQUEUEARRAY; i++) {
        dprintf("rethreading[%d]\n", i);
        while (!QueueEmpty(&queues[i])) {
            ServeNode(&x, &queues[i]);
            dprintf("rethreading[%d] x=%s\n", i, x->entry);
            //InsertList(ListSize(list), x, list);
            InsertListTail(x, list);
        }
        //ListShow(list);
    }
    dprintf("rethreaded...\n");
}

int QueuePosition(char c)
{
    if (c == ' ')
        return 0;
    else if (isalpha(c))
        return tolower(c) - 'a' + 1;
    else
        return 27;
}

void ShowQueues(Queue queues[])
{
    int i;
    for (i = 0; i < MAXQUEUEARRAY; i++) {
        printf("Queue[%d]\n", i);
        ListShow(&queues[i]);
    }
}

void RadixSort(List *list)
{
    int i, j, q_pos;
    Node *x;
    Queue queues[MAXQUEUEARRAY];
    for (i = 0; i < MAXQUEUEARRAY; i++)
        CreateQueue(&queues[i]);
    for (j = KEYSIZE-1; j >= 0; j--) {
        while (!ListEmpty(list)) {
            DeleteList(0, &x, list);
            q_pos = QueuePosition(x->entry[j]);
            dprintf("deleted %d: %s  qpos %d\n", j, x->entry, q_pos);
            AppendNode(x, &queues[q_pos]);
        }
        //ShowQueues(queues);
        Rethread(list, queues);
    }
}

Node *MakeNode(char *name)
{
    Node *x;
    x = (Node *) malloc(sizeof(Node));
    x->next = NULL;
    sprintf(x->entry, "%s", name);
    return x;
}

void Init(List *list)
{
    Node *x;
    list->front = list->rear = NULL;
    list->count = 0;

    x = MakeNode("rat\0");
    AppendNode(x, list);

    x = MakeNode("mop\0");
    AppendNode(x, list);

    x = MakeNode("cat\0");
    AppendNode(x, list);

    x = MakeNode("map\0");
    AppendNode(x, list);

    x = MakeNode("car\0");
    AppendNode(x, list);

    x = MakeNode("top\0");
    AppendNode(x, list);

    x = MakeNode("cot\0");
    AppendNode(x, list);

    x = MakeNode("tar\0");
    AppendNode(x, list);

    x = MakeNode("rap\0");
    AppendNode(x, list);
}

void Init2(List *list)
{
    Node *x;
    list->front = list->rear = NULL;
    list->count = 0;

    x = MakeNode("Tim\0");
    AppendNode(x, list);

    x = MakeNode("Dot\0");
    AppendNode(x, list);

    x = MakeNode("Eva\0");
    AppendNode(x, list);

    x = MakeNode("Roy\0");
    AppendNode(x, list);

    x = MakeNode("Tom\0");
    AppendNode(x, list);

    x = MakeNode("Kim\0");
    AppendNode(x, list);

    x = MakeNode("Guy\0");
    AppendNode(x, list);

    x = MakeNode("Amy\0");
    AppendNode(x, list);

    x = MakeNode("Jon\0");
    AppendNode(x, list);

    x = MakeNode("Ann\0");
    AppendNode(x, list);

    x = MakeNode("Jim\0");
    AppendNode(x, list);

    x = MakeNode("Kay\0");
    AppendNode(x, list);

    x = MakeNode("Ron\0");
    AppendNode(x, list);

    x = MakeNode("Jan\0");
    AppendNode(x, list);

}

int main()
{
    List list;
    Init2(&list);
    printf("list before radix sort\n");
    ListShow(&list);
    RadixSort(&list);
    printf("\nlist after radix sort\n");
    ListShow(&list);
    return 0;
}

