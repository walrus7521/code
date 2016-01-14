#include <stdio.h>

/* pseudo-random number generator
 * suggested by Knuth
 */

unsigned long random()
{
#define MULT 1664525L
#define ADD  1013904223L
    static unsigned long r = 0;
    r = r * MULT + ADD;
    return r;
}

int main()
{
    int i;
    for (i = 0; i < 16; ++i) {
        printf("[%02d] = %08lX\n", i, random() & 0xFFFFFFFF);
    }
}

