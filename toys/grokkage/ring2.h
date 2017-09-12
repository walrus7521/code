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
int size(struct ring2 *r);
int empty(struct ring2 *r);
int full(struct ring2 *r);
void push(struct ring2 *r, void *val);
void *shift(struct ring2 *r);
void dump(struct ring2 *r);


#endif // __ring2_h_

