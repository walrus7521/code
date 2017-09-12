#ifndef __ring2_h_
#define __ring2_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

typedef int e_type;
struct ring2 {
    uint8_t capacity;
    e_type *array;
    int32_t read;
    uint32_t write;
};

// adt
// private
// public methods
struct ring2* create(int size);
int size(struct ring2 *r);
int empty(struct ring2 *r);
int full(struct ring2 *r);
int mask(struct ring2 *r, e_type val);
void push(struct ring2 *r, e_type val);
e_type shift(struct ring2 *r);
void dump(struct ring2 *r);


#endif // __ring2_h_

