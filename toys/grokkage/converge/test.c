#include <stdio.h>
#include <string.h>

#if 1
#include "fifo.h"
int main()
{
    fifo_ptr f = fifo_new(); 
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

#if 0
#include "ring.h"
int main()
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
#endif

#if 0
#include "ring2.h"
int main()
{
    uint8_t buffer[256];
    ring_t ring;
    ring_init(&ring, 256, buffer);
    int i;
    for (i = 0; i < 8; i++) {
        char data = i+'a';
        printf("put: %c\n", data);
        ring_put(&ring, 'a'+i);
    }
    printf("\n");
    while (ring_data_avail(&ring)) {
        uint8_t data;
        if (SUCCESS == ring_get(&ring, &data)) {
            printf("get: %c\n", data);
        }
    }
}
#endif


#if 0
#define SIZE_RING 32
typedef char e_v;
#include "ring.inc"
int main()
{
    char n = 0;
    init_ring();
    while (!rngfull()) {
        rngput(n+'a');
        n++;
    }
    int counter = 0;
    while (!rngempty()) {
        n = rngget();
        printf("ring[%02d]: %c\n", counter++, n);
    }
}

#endif
