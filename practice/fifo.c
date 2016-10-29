#include <stdio.h>
#include <stdlib.h>

struct _link {
    int k;
    struct _link *next;
};

struct fifo {
    struct _link *head;
    struct _link *tail;
};

struct fifo *create()
{
    struct fifo *f = malloc(sizeof(struct fifo));
    struct _link *l = malloc(sizeof(struct _link));
    l->next = NULL;
    f->head = f->tail = l;
    return f;
}

void delete(struct fifo *f)
{
}

void put(struct fifo *f, int v)
{
    struct _link *l = malloc(sizeof(struct _link));
    l->k = v;
    l->next = NULL;
    if (f->head->next == NULL) {
        l->next = f->head->next;
        f->head->next = l;
        f->tail = l;
    } else {
        l->next = f->tail->next;
        f->tail->next = l;
    }
}

int get(struct fifo *f)
{
    struct _link *l;
    int v = 0;
    if (f->head->next != NULL) {
        l = f->head->next;
        v = l->k;
        f->head->next = l->next;
        free(l);
        l = NULL;
    }
    return v;
}

int empty(struct fifo *f)
{
    printf("head %p, tail %p\n", f->head, f->tail);
    return (f->head->next != f->tail);
}

void show(struct fifo *f)
{
    printf("show...\n");
    struct _link *l = f->head->next;
    while (l) {
        printf("l->k: %d\n", l->k);
        l = l->next;
    }
}

int main()
{
    struct fifo *f = create();
    int i, x;
    for (i = 1; i <= 8; i++) {
        put(f, i);
    }
    show(f);
    //while (!empty(f)) {
        empty(f); x = get(f); printf("x: %d\n", x);
        empty(f); x = get(f); printf("x: %d\n", x);
        empty(f); x = get(f); printf("x: %d\n", x);
        empty(f); x = get(f); printf("x: %d\n", x);
        empty(f); x = get(f); printf("x: %d\n", x);
        empty(f); x = get(f); printf("x: %d\n", x);
        empty(f); x = get(f); printf("x: %d\n", x);
        empty(f); x = get(f); printf("x: %d\n", x);
    //}
}
