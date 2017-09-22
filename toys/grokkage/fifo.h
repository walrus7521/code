#ifndef __fifo_h_
#define __fifo_h_

typedef struct fifo *fifo_ptr;

fifo_ptr fifo_new();
void fifo_show(fifo_ptr f);
void fifo_put(fifo_ptr f, void *x);
void *fifo_get(fifo_ptr f);
int fifo_empty(fifo_ptr f);
void fifo_clear(fifo_ptr f);


#endif // __fifo_h_
