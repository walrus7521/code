#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "ring2.h"


struct ring2* create(int size)
{
    capacity = size;
    array = (int *) malloc(size * sizeof(int));
}

int size(struct ring2 *r)
{
}

int empty(struct ring2 *r)
{
}

int full(struct ring2 *r)
{
}

int mask(struct ring2 *r, e_type val)
{
}

void push(struct ring2 *r, e_type val)
{
}

e_type shift(struct ring2 *r)
{
}

void dump(struct ring2 *r)
{
    int i;
    for (i = 0; i < capacity; i++) {
        printf("a[%d] = %d\n", i, array[i]);
    }
}


#if 0
#define RING_SIZE (8)
int main()
{
    int i;
    init(RING_SIZE); // must be power-of-two size
    for (i = 0; i < 32; i++) {
        printf("mask(%02d) = %02d\n", i, mask(i));
        if (!full()) {
            push(i);
        }
    }
    printf("full : %d\n", full());
    printf("empty: %d\n", empty());
    printf("size : %d\n", size());
    while (!empty()) {
        printf("shift: %d\n", shift());
    }
    dump();
}
#endif

