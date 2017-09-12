#ifndef __ring_h_
#define __ring_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

struct ring;
//typedef void * e_type;
// adt
// private
// public methods
struct ring* ring_create(int size);
int ring_size(struct ring *r);
int ring_empty(struct ring *r);
int ring_full(struct ring *r);
void ring_push(struct ring *r, void *val);
void *ring_shift(struct ring *r);
void ring_dump(struct ring *r);


#endif // __ring_h_

