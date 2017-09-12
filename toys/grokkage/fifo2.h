#ifndef __fifo_h_
#define __fifo_h_

typedef struct fifo *fifo;

fifo fifo_new();
void fifo_show(fifo *f);
void fifo_put(fifo *f, void *x);
void *fifo_get(fifo *f);
int fifo_empty(fifo *f);


#endif // __fifo_h_
