#include <stdio.h>
#include <stdlib.h>


typedef struct link {
    struct link *next;
    int key;
} link_t;

typedef struct {
    link_t *head;
    link_t *tail;
} list_t;


link_t *new(int key)
{
    link_t *p = (link_t *) malloc(sizeof(link_t));
    p->next = NULL;
    p->key = key;
    return p;
}

void push(list_t *list, int key)
{
    link_t *p = new(key);
    if (list->head == NULL) {
        list->head = list->tail = p;
    } else {
        p->next = list->head;
        list->head = p;
    }
}

void append(list_t *list, int key)
{
    link_t *p = new(key);
    if (list->head == NULL) {
        list->head = list->tail = p;
    } else {
        list->tail->next = p;
        list->tail = p;
    }
}

link_t *reverse(list_t *list)
{
    link_t *p = list->head, *q, *r = NULL;
    while (p) {
        q = p->next;
        p->next = r;
        r = p;
        p = q;
    }
    return r;
}

link_t *deque(list_t *list)
{   
    // need tail->prev
    link_t *r = NULL;
    if (list->tail) {
        // get prev
        link_t *prev;
        prev = r = list->head;
        while (r) {
            if (r == list->tail) break;
            prev = r;
            r = r->next;
        }
        r = list->tail;
        list->tail = list->tail->next;
    }
    return r;
}

link_t *pop(list_t *list)
{   
    link_t *r = NULL;
    if (list->head) {
        r = list->head;
        list->head = list->head->next;
    }
    return r;
}

void show(list_t *list)
{
    link_t *p = list->head;
    while (p) {
        printf("%d\n", p->key);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    list_t *list = (list_t *) malloc(sizeof(list_t));
    list->head = list->tail = NULL;
    list_t *t;
    int i;
    for (i = 0; i < 8; i++) {
        //append(list, i);
        push(list, i);
    }
    show(list);
    link_t *p;
    //while ((p = pop(list))) {
    while ((p = deque(list))) {
        //printf("pop: %d\n", p->key);
        printf("deque: %d\n", p->key);
    }
    //show(list);
    //list->head = reverse(list);
    //show(list);

}

