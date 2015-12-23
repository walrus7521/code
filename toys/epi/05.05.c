#include <stdio.h>
#include <inttypes.h>

/*
 * Compute x * y without multiply or add
 *
 * Write a function that multiplies 2 nonnegative integers.  The
 * only operators you are allowed to use are assignment and bitwise
 * operators, ie, >>, <<, |, &, ~, ^.  (You cannot use increment
 * or decrement).  You may use loops, conditionals and functions
 * you write yourself.
 *
 */

uint64_t multiply(uint64_t x, uint64_t y)
{
    return 0;
}

int main()
{
    uint64_t x, y;

    x = 0x76;
    y = 0x92;
    printf("multiply %llxh X %llxh = %llxh\n", x, y, multiply(x, y));
}
