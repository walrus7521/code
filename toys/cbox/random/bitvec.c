#include <stdio.h>
#include <stdlib.h>

#define BITS_PER_WORD 32
#define dprintf printf
//#define dprintf(...)

typedef struct _bitvec {
    int size; /* in 32-bit words */
    unsigned int *vector;
} bitvec;

bitvec *create(int size_in_bits)
{
    bitvec *vector = NULL;
    int i, num;
    vector = (bitvec *) malloc(sizeof(bitvec));
    num = (size_in_bits/BITS_PER_WORD)+1;
    dprintf("num bits = %d, %d 32-bit words\n", num * BITS_PER_WORD, num);
    vector->vector = (unsigned int*) malloc(num * sizeof(unsigned int));
    vector->size = (size_in_bits/BITS_PER_WORD)+1;
    for (i = 0; i < vector->size; i++) {
        vector->vector[i] = 0;
    }
    return vector;   
}

int lookup(int x, bitvec *vector)
{
    int idx = (x / BITS_PER_WORD), bit = (x % BITS_PER_WORD), mask = (1 << bit);
    int set = (vector->vector[idx] & mask) ? 1 : 0;
    dprintf("lookup bit=%x mask=%x => %d:%08X\n", bit, mask, set, vector->vector[idx]);
    return set;
}

void delete(int x, bitvec *vector)
{
    int idx = (x / BITS_PER_WORD), bit = (x % BITS_PER_WORD), mask = (1 << bit);
    vector->vector[idx] &= ~mask;
    dprintf("delete bit=%x => [%d]:%08x\n", bit, idx, vector->vector[idx]);
}

void insert(int x, bitvec *vector)
{
    int idx = (x / BITS_PER_WORD), bit = (x % BITS_PER_WORD), mask = (1 << bit);
    vector->vector[idx] |= mask;
    dprintf("insert bit=%x => [%d]:%08x\n", bit, idx, vector->vector[idx]);
}

void printvector(bitvec *vector)
{
    int i;
    for (i = 0; i < vector->size; i++) {
        dprintf("vec[%d] = %08X\n", i, vector->vector[i]);
    }
}

int main()
{
    bitvec *vector;
    vector = create(256);
    insert(2, vector);
    insert(240, vector);
    lookup(2, vector);
    lookup(5, vector);
    lookup(240, vector);
    //delete(2, vector);
    lookup(2, vector);
    printvector(vector);
    return 0;
}
