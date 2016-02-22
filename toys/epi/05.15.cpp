/* Compute the greatest common divisor
 *
 * The greatest common divisor (GCD) of positive integers x and y is the largest 
 * integer d such that d divides x evenly, and d divides y evenly, ie, x mod d == 0
 * and y mod d == 0.
 * 
 * Design an efficient algorithm for computing the GCD of two numbers without using
 * multiplication, division or the modulus operator.

 * Hint: use case analysis: both even; both odd; one even and one odd.
 */

#include <iostream>

#define MAX(a,b) (((a)>(b))?(a):(b))

unsigned int modulo(unsigned int dividend, unsigned int divisor);

int gcd(int x, int y)
{
    int loop = MAX(x,y);
    for (int i = loop; i > 0; --i) {
        //if ((x % i == 0) && (y % i == 0)) {
        if ((modulo(x, i) == 0) && (modulo(y, i) == 0)) {
            return i;
        } 
    }
    return -1;
}

int main()
{
    int x, y;
    x = 8;
    y = 64;
    printf("gcd(%d, %d) = %d\n", x, y, gcd(x,y));
}

/* divident: left hand side of division, ie, what is being divided
   divisor: right hand side of division
 */
unsigned int modulo(unsigned int dividend, unsigned int divisor)
{
    unsigned int remain=dividend, part1=divisor, result=0, mask=1;
    printf("modulo(%d, %d)\n", dividend, divisor);
    if (part1 == 0) { // this is preventing divide by zero, ie, divisor == 0
        return -1;
    }
    while (part1 < remain) {
        part1 = part1 << 1;
        mask = mask << 1;
    }
    printf("part1 = %d\n", part1);
    /* at this point, part1 is the greatest power of divisor that dividend is
       evenly divided by, leaving a remainder of course.
     */
    do {
        if (remain >= part1) {
            remain = remain - part1;
            result = result + mask;
        }
        part1 = part1 >> 1;
        mask = mask >> 1;
    } while (mask != 0);
    return remain;
}
