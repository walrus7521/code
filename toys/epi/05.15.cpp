/* Compute the greatest common divisor
 *
 * The greatest common divisor (GCD) of positive integers x and y is the largest 
 * integer d such that d divides x evenly, and d divides y evenly, ie, x mod d == 0
 * and y mod d == 0.
 * 
 * Design an efficient algorithm for computing the GCD of two numbers without using
 * multiplication, division or the modulus operator.
 */

#include <iostream>

int gcd(int x, int y)
{
    for (int i = 100; i > 0; --i) {
        if ((x % i == 0) && (y % i == 0)) {
            return i;
        } 
    }
    return -1;
}

int main()
{
    int x, y;
    x = 8;
    y = 60;
    printf("gcd(%d, %d) = %d\n", x, y, gcd(x,y));
}

