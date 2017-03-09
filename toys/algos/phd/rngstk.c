#include <stdio.h>
#include <stdlib.h>

typedef int e_v;

#define SIZE_RING 32
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

// previous typedef e_v applies here as well
#define SIZE_STAK 32
#include "stak.inc"

void test_stk()
{
    int i, n;
    init_stak();
    printf("space avail %d\n", stkspace());
    for (i = 0; i < 8; i++) {
        if (!stkfull()) {
            stkpush(i);
        }
    }
reload:
    printf("here 1...\n");
    while (!stkempty()) {
        printf("peek: %d\n", stkpeek());
        printf("bytes avail %d\n", stkdata());
        printf("space avail %d\n", stkspace());
        n = stkpop();
        printf("n=%d\n", n);
    }
    for (i=0; i < 32; i++) {
        if (!stkfull()) {
            stkpush(i);
        }
    }
    goto reload;
}

int main()
{
    //test_ring();
    test_stk();
    return 0;
}
