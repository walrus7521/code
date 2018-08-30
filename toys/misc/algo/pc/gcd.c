#include <stdio.h>
#include <math.h>

long gcd(long p, long q, long *x, long *y)
{
    long x1, y1, g;

    if (q > p) return gcd(q,p,y,x);

    if (q == 0) {
        *x = 1;
        *y = 0;
        return (p);
    }

    g = gcd(q, p%q, &x1, &y1);

    *x = y1;
    *y = (x1 - floor(p/q)*y1);

    return (g);
}

int main()
{
    long p, q, x, y;
    p= 34398;
    q= 2132;
    printf("gcd(%ld, %ld) = %ld\n", p, q, gcd(p, q, &x, &y));
    return 0;
}

