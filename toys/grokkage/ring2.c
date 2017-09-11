#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>


// adt
// private
uint8_t capacity; // = 8;
int *array; //int array[8];
uint32_t read;
uint32_t write;
// public methods
int size()     { return write - read; }
int empty()    { return read == write; }
int full()     { return size() == capacity; }
int mask(val)  { return val & (capacity - 1); }
void push(val) { assert(!full()); array[mask(write++)] = val; }
int shift()    { assert(!empty()); return array[mask(read++)]; }

void init(int size)
{
    capacity = size;
    array = (int *) malloc(size * sizeof(int));
}

void dump()
{
    int i;
    for (i = 0; i < capacity; i++) {
        printf("a[%d] = %d\n", i, array[i]);
    }
}

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
