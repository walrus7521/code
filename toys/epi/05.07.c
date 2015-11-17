#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*
 * Compute x^y
 *   Write a function that takes a double x and an integer y and returns
 *   x^y.  Assume addition, multiplication, and division take constant time.
 *   You cannot use any functions, except for those you write yourself.  You
 *   can ignore overflow and underflow.
 */

long double power(long double x, int y)
{
    long double pow;
    int i;
    if (x == 0) return 0.0;
    if (y == 0) return 1.0;
    if (y < 0) {
        y = -y, x = 1.0 / x;
    }
    for (i = 0, pow = x; i < y-1; i++) {
        pow *= x;
    }
    return pow;
}

long double powerXY(long double x, int y)
{
    long double result = 1.0;
    long long power = y;
    if (x == 0) return 0.0;
    if (y == 0) return 1.0;
    if (y < 0) {
        power = -power, x = 1.0 / x;
    }
    while (power) {
        if (power & 1) {
            result *= x;
        }
        x *= x, power >>= 1;
    }
    return result;
}

int main()
{
    long double x, pow;
    int y;
    x = 7.0; y = -9;
    pow = power(x, y);
    printf("pow(%.2Lf, %02d)   = %.13Lf\n", x, y, pow);
    pow = powerXY(x, y);
    printf("powXY(%.2Lf, %02d) = %.13Lf\n", x, y, pow);
    return 0;
}
