//#include "ring.h"
#include <stdio.h>
#include "linalg.h"
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
#endif

void linalg()
{
    struct vector v = {1,2,3};
    struct matrix m = {{1,2,3},{4,5,6},{7,8,9}};

    vector_show(&v);
    matrix_show(&m);

}

int main()
{
    //ring_test();
    //my_fifo_test();
    linalg();
}
