#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "ring2.h"

static int r_mask(struct ring2 *r, uint32_t index);

struct ring2 {
    uint32_t capacity;
    uint32_t read;
    uint32_t write;
    void **arr;
};

struct ring2 *ring2_create(int size)
{
    struct ring2 *r = (struct ring2 *) malloc(sizeof(struct ring2));
    r->capacity = size;
    r->write = r->read = 0;
    r->arr = (void **) malloc(size * sizeof(void *));
}

void ring2_destroy(struct ring2 *r)
{
    free(r->arr);
    free(r);
}

int ring2_size(struct ring2 *r)
{
    return (r->write - r->read);
}

int ring2_empty(struct ring2 *r)
{
    return (r->read == r->write);
}

int ring2_full(struct ring2 *r)
{
    return (ring2_size(r) == r->capacity);
}

void ring2_push(struct ring2 *r, void *val)
{
    assert(!ring2_full(r)); r->arr[r_mask(r, r->write++)] = val; 
}

void *ring2_shift(struct ring2 *r)
{
    assert(!ring2_empty(r)); return r->arr[r_mask(r, r->read++)];
}

void ring2_dump(struct ring2 *r)
{
    int i;
    for (i = 0; i < r->capacity; i++) {
        printf("a[%02d] = %08x\n", i, r->arr[i]);
    }
}

static int r_mask(struct ring2 *r, uint32_t index)
{
    return (index & (r->capacity - 1));
}

#define RING_SIZE (8)
void ring2_test()
{
    int i;
    struct ring2 *r1 = ring2_create(8);
    struct ring2 *r2 = ring2_create(16);

    for (i = 0; i < 32; i++) {
        if (!ring2_full(r1)) {
            ring2_push(r1, (void *) i);
        }
        if (!ring2_full(r2)) {
            ring2_push(r2, (void *) i);
        }
    }

    printf("full : %d\n", ring2_full(r1));
    printf("empty: %d\n", ring2_empty(r1));
    printf("size : %d\n", ring2_size(r1));

    printf("full : %d\n", ring2_full(r2));
    printf("empty: %d\n", ring2_empty(r2));
    printf("size : %d\n", ring2_size(r2));
    
    while (!ring2_empty(r1)) {
        printf("shift1: %d\n", ring2_shift(r1));
    }

    while (!ring2_empty(r2)) {
        printf("shift2: %d\n", ring2_shift(r2));
    }

    ring2_dump(r1);
    ring2_dump(r2);
}

