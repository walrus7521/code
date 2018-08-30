#include <stddef.h>
#include <assert.h> // "assert.h"
#include <stdlib.h> //#include "mem.h"
#include "stack.h"

#define T Stack_t

#define NEW(x) malloc(sizeof(x))
#define FREE(x) { \
    free(x); \
    x = NULL; }

struct T {
    int count;
    struct elem {
        void *x;
        struct elem *link;
    } *head;
};

T Stack_new(void)
{
    T stk;
    stk = NEW(stk);
    stk->count = 0;
    stk->head = NULL;
    return stk;
}

int Stack_empty(T stk)
{
    assert(stk);
    return (stk->count == 0);
}

void Stack_push(T stk, void *x)
{
    struct elem *t;
    assert(stk);
    t = NEW(t);
    t->x = x;
    t->link = stk->head;
    stk->head = t;
    stk->count++;
}

void *Stack_pop(T stk)
{
    void *x;
    struct elem *t;

    assert(stk);
    assert(stk->count > 0);
    t = stk->head;
    stk->head = t->link;
    stk->count--;
    x = t->x;
    FREE(t);
    return x;
    return x;
}

void Stack_free(T *stk)
{
    struct elem *t, *u;

    assert(stk && *stk);
    for (t = (*stk)->head; t; t = u) {
        u = t->link;
        FREE(t);
    }
    FREE(*stk);
}


