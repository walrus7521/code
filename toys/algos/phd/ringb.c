#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

#define SIZE_RING 32
typedef int e_v;
#include "ring.inc"

void test_ring()
{
    int i, n;
    init_ring();
    printf("space avail %d\n", rngspace());
    for (i = 0; i < 8; i++) {
        if (!rngfull()) {
            rngput(i);
        }
    }
reload:
    while (!rngempty()) {
        printf("peek: %d\n", rngpeek());
        printf("bytes avail %d\n", rngdata());
        printf("space avail %d\n", rngspace());
        n = rngget();
        printf("n=%d\n", n);
    }
    for (; i < n+8; i++) {
        if (!rngfull()) {
            rngput(i);
        }
    }
    goto reload;
}

#include <string.h>
#include "ring2.inc"

void test_ring2()
{
    char buffer[256];
    int i, id = 7;
    fifo_init(id, buffer, 256);
    for (i = 0; i < 26; i++) {
        fifo_enqueue(id, 'a'+i);
    }
    char c;
    fifo_peek_relative(id, 2, &c);
    printf("peek: %c\n", c);
    char tmp[8] = "";
    memset(tmp, 8, 0);
    fifo_peek_data(id, (void *) tmp, 8);
    printf("peek data: %s\n", tmp);
    fifo_enqueue_data(id, tmp, 8);
    while (fifo_get_num_data_avail(id)) {
        fifo_dequeue_data(id, tmp, 1);
        printf("dequeued: %c\n", tmp[0]);
    }
}

int main()
{
    test_ring();
    //test_ring2();    
    return 0;
}
