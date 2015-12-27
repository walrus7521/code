#include <stdio.h>
#include <inttypes.h>

/*
 * Compute y / x using only add, subtract and shift
 *   x and y are positive integers
 *
 * hint: relate x / y => (x - y) / y
 */


uint64_t div(int64_t x, int64_t y)
{
    int count = 0;
    while (x >= y) {
        x -= y;
        count++;
    }
    return count;
}

uint64_t mod(int64_t x, int64_t y)
{
    int count = 0;
    while (x >= y) {
        x -= y;
        count++;
    }
    return x;
}

int main()
{
    uint64_t x, y;
    x = 13;
    y = 3;
    printf("div %lld / %lld = %lld => truth=%lld\n", x, y, div(x, y), x/y);
    printf("mod %lld / %lld = %lld => truth=%lld\n", x, y, mod(x, y), x%y);
}
