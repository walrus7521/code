#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "ring.h"

static int r_mask(struct ring *r, uint32_t index);

struct ring {
    uint32_t capacity;
    uint32_t read;
    uint32_t write;
    void **arr;
};

struct ring *ring_create(int size)
{
    struct ring *r = (struct ring *) malloc(sizeof(struct ring));
    r->capacity = size;
    r->write = r->read = 0;
    r->arr = (void **) malloc(size * sizeof(void *));
}

void ring_destroy(struct ring *r)
{
    free(r->arr);
    free(r);
}

int ring_size(struct ring *r)
{
    return (r->write - r->read);
}

int ring_empty(struct ring *r)
{
    return (r->read == r->write);
}

int ring_full(struct ring *r)
{
    return (ring_size(r) == r->capacity);
}

void ring_push(struct ring *r, void *val)
{
    assert(!ring_full(r)); r->arr[r_mask(r, r->write++)] = val; 
}

void *ring_shift(struct ring *r)
{
    assert(!ring_empty(r)); return r->arr[r_mask(r, r->read++)];
}

void ring_dump(struct ring *r)
{
    int i;
    for (i = 0; i < r->capacity; i++) {
        printf("a[%02d] = %08x\n", i, r->arr[i]);
    }
}

static int r_mask(struct ring *r, uint32_t index)
{
    return (index & (r->capacity - 1));
}

#define RING_SIZE (8)
void ring_test()
{
    int i;
    struct ring *r1 = ring_create(8);
    struct ring *r2 = ring_create(16);

    for (i = 0; i < 32; i++) {
        if (!ring_full(r1)) {
            ring_push(r1, (void *) i);
        }
        if (!ring_full(r2)) {
            ring_push(r2, (void *) i);
        }
    }

    printf("full : %d\n", ring_full(r1));
    printf("empty: %d\n", ring_empty(r1));
    printf("size : %d\n", ring_size(r1));

    printf("full : %d\n", ring_full(r2));
    printf("empty: %d\n", ring_empty(r2));
    printf("size : %d\n", ring_size(r2));
    
    while (!ring_empty(r1)) {
        printf("shift1: %d\n", ring_shift(r1));
    }

    while (!ring_empty(r2)) {
        printf("shift2: %d\n", ring_shift(r2));
    }

    ring_dump(r1);
    ring_dump(r2);
}

