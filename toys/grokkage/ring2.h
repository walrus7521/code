#ifndef __ring2_h_
#define __ring2_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>


//typedef void * e_type;
// adt
// private
// public methods
struct ring2* create(int size);
int ring2_size(struct ring2 *r);
int ring2_empty(struct ring2 *r);
int ring2_full(struct ring2 *r);
void ring2_push(struct ring2 *r, void *val);
void *ring2_shift(struct ring2 *r);
void ring2_dump(struct ring2 *r);


#endif // __ring2_h_

