#include <stdio.h>
#include <inttypes.h>

/*
 * reverse bits
 *
 *  write code that takes 64-bit integer and returns the reversal of the integer bits
 */


unsigned long long reverse(uint64_t x) {
    uint64_t y = x, mi, mj, one, i, j, bi, bj;
    i = 0; j = 63; one = 1;
    while (i < 32) {
        //printf("b(i=%02lld, mi=%016llx) = %lld, b(j=%02lld, mj=%016llx) = %lld\n", i, mi, bi, j, mj, bj);
        if ((x & (one << i)) != (x & (one << j))) {
            /* swap bits (i, j) */
            y ^= ((one << i) | (one << j));
            printf("bits %llu & %llu are different %016llx, y = %016llx\n", i, j, x, y);
        } else {
            printf("bits %llu & %llu are the same\n", i, j);
        }
        i++;
        j--;
    }
    return y;
}

int main()
{
    unsigned long long x;
    x = 0x8000000000000001;
    printf("reverse(%016llx) => %016llx\n", x, reverse(x));
}
