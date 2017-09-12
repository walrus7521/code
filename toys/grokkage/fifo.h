#ifndef __fifo_h_
#define __fifo_h_

#if 1
struct link;
struct link *link_new(int val);
void show(struct link *list);
void put(struct link *list, void *x);
void *get(struct link *list);
int empty(struct link *list);
#endif

#if 0
typedef struct fifo;
fifo fifo_new(void *v);
void show(fifo *f);
void put(fifo *f, void *x);
void *get(fifo *f);
int empty(fifo *f);
#endif

#endif // __fifo_h_
