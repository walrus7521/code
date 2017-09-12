#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "ring2.h"

struct ring2 {
    uint32_t capacity;
    uint32_t read;
    uint32_t write;
    void **arr;
};

struct ring2* create(int size)
{
    struct ring2 *r = (struct ring2 *) malloc(sizeof(struct ring2));
    r->capacity = size;
    r->write = r->read = 0;
    r->arr = (void **) malloc(size * sizeof(void *));
}

void destroy(struct ring2 *r)
{
    free(r->arr);
    free(r);
}

int size(struct ring2 *r)
{
    return (r->write - r->read);
}

int empty(struct ring2 *r)
{
    return (r->read == r->write);
}

int full(struct ring2 *r)
{
    return (size(r) == r->capacity);
}

int mask(struct ring2 *r, uint32_t index)
{
    return (index & (r->capacity - 1));
}

void push(struct ring2 *r, void *val)
{
    assert(!full(r)); r->arr[mask(r, r->write++)] = val; 
}

e_type shift(struct ring2 *r)
{
    assert(!empty(r)); return r->arr[mask(r, r->read++)];
}

void dump(struct ring2 *r)
{
    int i;
    for (i = 0; i < r->capacity; i++) {
        printf("a[%02d] = %08x\n", i, r->arr[i]);
    }
}

#define RING_SIZE (8)
void ring2_test()
{
    int i;
    struct ring2 *r1 = create(8);
    struct ring2 *r2 = create(16);
    for (i = 0; i < 32; i++) {
        printf("mask1(%02d) = %02d\n", i, mask(r1, i));
        if (!full(r1)) {
            push(r1, (void *) i);
        }
        printf("mask2(%02d) = %02d\n", i, mask(r2, i));
        if (!full(r2)) {
            push(r2, (void *) i);
        }
    }
    printf("full : %d\n", full(r1));
    printf("empty: %d\n", empty(r1));
    printf("size : %d\n", size(r1));

    printf("full : %d\n", full(r2));
    printf("empty: %d\n", empty(r2));
    printf("size : %d\n", size(r2));
    
    while (!empty(r1)) {
        printf("shift1: %d\n", shift(r1));
    }
    while (!empty(r2)) {
        printf("shift2: %d\n", shift(r2));
    }

    dump(r1);
    dump(r2);
}

