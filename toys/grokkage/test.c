#include "ring.h"
#include <stdio.h>
//#include "linalg.h"
#if 0
//#include "fifo.h"
//extern void ring_test();
//extern void fifo_test();

void my_fifo_test()
{
    fifo *f = fifo_new(); 
    fifo_put(f, (void *) 0);
    fifo_put(f, (void *) 1);
    fifo_put(f, (void *) 2);
    fifo_put(f, (void *) 3);
    fifo_show(f);
    //fifo_clear(f);
    fifo_show(f);
    while (!fifo_empty(f)) {
        int l = (int) fifo_get(f);
        printf("=> %d\n", l);
    }
}

void linalg()
{
    struct vector v = {1,2,3};
    struct matrix m = {{1,2,3},{4,5,6},{7,8,9}};

    vector_show(&v);
    matrix_show(&m);

}
#endif

void ring_test()
{
    int i;
    ring_ptr r1 = ring_create(8);
    ring_ptr r2 = ring_create(16);

    for (i = 0; i < 32; i++) {
        if (!ring_full(r1)) {
            ring_push(r1, (void *) i);
        }
        if (!ring_full(r2)) {
            ring_push(r2, (void *) i);
        }
    }

    printf("full : %d\n", ring_full(r1));
    printf("empty: %d\n", ring_empty(r1));
    printf("size : %d\n", ring_size(r1));

    printf("full : %d\n", ring_full(r2));
    printf("empty: %d\n", ring_empty(r2));
    printf("size : %d\n", ring_size(r2));
    
    while (!ring_empty(r1)) {
        printf("shift1: %d\n", ring_shift(r1));
    }

    while (!ring_empty(r2)) {
        printf("shift2: %d\n", ring_shift(r2));
    }

    ring_dump(r1);
    ring_dump(r2);
}

int main()
{
    ring_test();
    //my_fifo_test();
    //linalg();
}
