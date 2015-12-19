#include <stdio.h>

/*
 * swap bits
 *
 *  x & (x-1) = x w/low bit clear
 *  x & ~(x- 1) = x lowest bit, all others clear
 *  64-bits as array, index 0 = LSB, 63 = MSB
 *  write code that takes 64-bit integer and swaps bits at index i & j
 */

unsigned long long swap1(unsigned long long x, int i, int j) {
    unsigned long long y = x;
    //printf("y        : %016llx\n", y);
    /* clear both bits */
    y &= ~(1 << i);
    y &= ~(1 << j);
    //printf("new y    : %016llx\n", y);
    /* set the swap bits */
    y |= ((x & (1 << i)) >> i) << j;
    y |= ((x & (1 << j)) >> j) << i;
    //printf("new new y: %016llx\n", y);
    return y;
}

unsigned long long swap2(unsigned long long x, int i, int j) {
    unsigned long long y = x;
    /* test if the bits are different */
    if ( (x & (1 << i)) != (x & (1 << j)) ) {
        /* just invert them, since one is 1 and the other 0 */
        y ^= (1 << i) | (1 << j);
    }
    return y;
}

int main()
{
    unsigned long long x;
    int i, j;
    x = 0x00080004; i = 19, j = 0;
    printf("swap(%016llx, %d, %d) => %016llx\n", x, i, j, swap1(x, i, j));
    x = 0x00080004; i = 19, j = 0;
    printf("swap(%016llx, %d, %d) => %016llx\n", x, i, j, swap2(x, i, j));
}
