#include <stdio.h>

/*
 * swap bits
 *
 *  x & (x-1) = x w/low bit clear
 *  x & ~(x- 1) = x lowest bit, all others clear
 *  64-bits as array, index 0 = LSB, 63 = MSB
 *  write code that takes 64-bit integer and swaps bits at index i & j
 */

unsigned long long swap(unsigned long long x, int i, int j) {
    unsigned long long y = x;
    int bi, bj;
    bi = y & (1 << i);
    bj = y & (1 << j);
    printf("bit i = %d, bit j = %d\n", bi, bj);
    printf("y        : %016llx\n", y);
    /* clear both bits */
    y &= ~bi;
    y &= ~bj;
    printf("new y    : %016llx\n", y);
    /* set the swap bits */
    y |= (bi << j);
    y |= (bj << i);
    printf("new new y: %016llx\n", y);
    return y;
}


int main()
{
    unsigned long long x = 0x00000004;
    int i = 1, j = 2;
    printf("swap(%016llx, %d, %d) => %016llx\n", x, i, j, swap(x, i, j));
}
