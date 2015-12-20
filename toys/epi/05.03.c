#include <stdio.h>
#include <inttypes.h>

/*
 * reverse bits
 *
 *  write code that takes 64-bit integer and returns the reversal of the integer bits
 */


unsigned long long reverse(uint64_t x) {
    uint64_t y = x, mi, mj, one, i, j, bi, bj, or;
    i = 0; j = 63; one = 1;
    while (i < 32) {
        mi = (one << i);
        mj = (one << j);
        bi = x & (one << i) >> i;
        bj = x & (one << j) >> j;
        printf("b(i=%02lld, mi=%016llx) = %llx, b(j=%02lld, mj=%016llx) = %llx\n", i, mi, bi, j, mj, bj);
        if (bi != bj) {
            /* swap bits (i, j) */
            or = (one << i) | (one << j);
            y ^= or;
            printf("bits %llu & %llu are different %016llx, or = %016llx, y = %016llx\n", i, j, x, or, y);
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
    uint64_t x;
    x = 0x8400000000000001;
    printf("reverse(%016llx) => %016llx\n", x, reverse(x));
}
