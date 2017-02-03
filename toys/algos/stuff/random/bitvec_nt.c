#include <stdio.h>
#include <stdlib.h>

#define BITS_PER_WORD 64
#define dprintf printf
//#define dprintf(...)

typedef unsigned long long vec_t;

typedef struct _bitvec {
    vec_t size; /* in 64-bit words */
    vec_t *vector;
} bitvec;

bitvec *create(vec_t size_in_bits)
{
    bitvec *vector = NULL;
    vec_t i, num;
    vector = (bitvec *) malloc(sizeof(bitvec));
    num = (size_in_bits/BITS_PER_WORD)+1;
    dprintf("num bits = %d, %d 64-bit words\n", num * BITS_PER_WORD, num);
    vector->vector = (vec_t *) malloc(num * sizeof(vec_t));
    vector->size = (size_in_bits/BITS_PER_WORD)+1;
    for (i = 0; i < vector->size; i++) {
        vector->vector[i] = 0;
    }
    return vector;   
}

vec_t lookup(vec_t x, bitvec *vector)
{
    vec_t idx = (x / BITS_PER_WORD), bit = (x % BITS_PER_WORD);
    vec_t mask = (1i64 << bit);
    vec_t set = (vector->vector[idx] & mask) ? 1 : 0;
    dprintf("lookup bit=%llx mask=%llx => %lld:%016llX\n", bit, mask, set, vector->vector[idx]);
    return set;
}

void delete(vec_t x, bitvec *vector)
{
    vec_t idx = (x / BITS_PER_WORD), bit = (x % BITS_PER_WORD);
    vec_t mask = (1i64 << bit);
    vector->vector[idx] &= ~mask;
    dprintf("delete bit=%llx => [%lld]:%016llx\n", bit, idx, vector->vector[idx]);
}

void insert(vec_t x, bitvec *vector)
{
    vec_t idx = (x / BITS_PER_WORD), bit = (x % BITS_PER_WORD);
    vec_t mask = (1i64 << bit);
    vector->vector[idx] |= mask;
    dprintf("insert bit=%llx => [%lld]:%016llx\n", bit, idx, vector->vector[idx]);
}

void printvector(bitvec *vector)
{
    vec_t i;
    for (i = 0; i < vector->size; i++) {
        dprintf("vec[%lld] = %016llX\n", i, vector->vector[i]);
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
