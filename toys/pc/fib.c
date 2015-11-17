#include <stdio.h>
#include <math.h>

int FIB[100] = {0};

int fib(int n)
{
    int F;
    double f1, f2, m;
    f1 = (1 + sqrt(5)) / 2.0; /* dominant term */
    f2 = (1 - sqrt(5)) / 2.0; /* always between 0 and 1 */
    m = (1.0 / sqrt(5));
    F = m * (pow(f1, n) - pow(f2, n));
    return F;
}


int main()
{
    int i;
    for (i = 0; i < 16; i++)
        printf("fib(%d) = %d\n", i, fib(i));
}
