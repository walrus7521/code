#include <stdio.h>
#include <stdint.h>
#include <assert.h>


// adt
uint8_t capacity = 8;
int array[8];
uint32_t read;
uint32_t write;
int size()     { return write - read; }
int empty()    { return read == write; }
int full()     { return size() == capacity; }
int mask(val)  { return val & (capacity - 1); }
void push(val) { assert(!full()); array[mask(write++)] = val; }
int shift()    { assert(!empty()); return array[mask(read++)]; }


void dump()
{
    int i;
    for (i = 0; i < capacity; i++) {
        printf("a[%d] = %d\n", i, array[i]);
    }
}

int main()
{
    int i;
    for (i = 0; i < 32; i++) {
        printf("mask(%02d) = %02d\n", i, mask(i));
        if (!full()) {
            push(i);
        }
    }
    printf("full : %d\n", full());
    printf("empty: %d\n", empty());
    printf("size : %d\n", size());
    printf("mask : %d\n", mask(8));
    while (!empty()) {
        printf("shift: %d\n", shift());
    }
    dump();
}
