#ifndef __ring_h_
#define __ring_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

typedef struct ring *ring_ptr;

ring_ptr ring_create(int size);
int ring_size(ring_ptr r);
int ring_empty(ring_ptr r);
int ring_full(ring_ptr r);
void ring_push(ring_ptr r, void *val);
void *ring_shift(ring_ptr r);
void ring_dump(ring_ptr r);


#endif // __ring_h_

