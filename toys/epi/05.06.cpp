#include <stdio.h>
#include <inttypes.h>

/*
 * Compute y / x using only add, subtract and shift
 *   x and y are positive integers
 *
 * hint: relate x / y => (x - y) / y
 */


/* the brute force approach
 */
uint64_t div(uint64_t x, uint64_t y)
{
    int count = 0;
    while (x >= y) {
        x -= y;
        count++;
    }
    return count;
}

uint64_t div2(uint64_t x, uint64_t y)
{
    int res = 0, pow;
    while (x >= y) {
        pow = 1;
        while ((y << pow) >= (y << (pow - 1)) && (y << pow) <= x) {
            ++pow;
        }
        res += 1LLU << (pow - 1);
        x -= y << (pow - 1);
    }
    return res;
}

uint64_t mod(uint64_t x, uint64_t y)
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
    x = 1300449879;
    y = 345671;
    printf("div  %lld / %lld = %lld => truth=%lld\n", x, y, div(x, y), x/y);
    printf("div2 %lld / %lld = %lld => truth=%lld\n", x, y, div2(x, y), x/y);
    printf("mod  %lld / %lld = %lld => truth=%lld\n", x, y, mod(x, y), x%y);
}
