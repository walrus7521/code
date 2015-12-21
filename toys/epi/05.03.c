#include <stdio.h>
#include <inttypes.h>

/*
 * reverse bits
 *
 *  write code that takes 64-bit integer and returns the reversal of the integer bits
 */
unsigned long long reverse(uint64_t x) {
    uint64_t y = x, bi, bj, mi, mj;
    int i, j;
    i = 0; j = 63;
    while (i < 32) {
        mi = 1ULL << i;
        mj = 1ULL << j;
        bi = x & mi;
        bj = x & mj;
        if ((bi>>i) != (bj>>j)) {
            /* swap bits (i, j) */
            y ^= ((mi) | (mj));
        }
        i++;
        j--;
    }
    return y;
}

int main()
{
    uint64_t x, y;
    x = 0x8080808010101010;
    printf("reverse(%016llx) => %016llx\n", x, reverse(x));
}
