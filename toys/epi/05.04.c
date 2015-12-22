#include <stdio.h>
#include <inttypes.h>

/*
 * Find a closest integer with the same weight
 *   Define the weight of a nonnegative integer x to be the number of bits that are set to
 *   1 in its binary representation.  For example, since 92 in base-2 equals (1011100):base-2,
 *   the weight of 92 is 4.
 *
 *   Write a function which takes as input a nonnegative integer x and returns y != x such that
 *   y has the same weight as x, and the difference of x and y is as small as possible.
 *   You can assume x in not 0, or all 1s.
 */

uint64_t smallest_weight(uint64_t x)
{
    /* 
     * 1. get bit count
     * 2. lookup smallest?  that's a huge table
     *
     */
    return 0;
}

int main()
{
    uint64_t x = 92;
    printf("smallest weight of (%lld) 0x%llx is 0x%llx\n", x, x, smallest_weight(x));
}
