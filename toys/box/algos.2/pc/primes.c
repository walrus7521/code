#include <stdio.h>
#include <math.h>

void prime_factorization(long x)
{
    long i, c;

    printf("prime_factorization(%ld):\n", x);
    c = x;
    while ((c % 2) == 0) {
        printf("%d\n", 2);
        c = c / 2;
    }

    i = 3;
    while (i <= (long) (sqrt(c) + 1)) {
        if ((c % i) == 0) {
            printf("%ld\n", i);
            c = c / i;
        } else {
            i = i + 2;
        }
    }

    if (c > 1) printf("%ld\n", c);
}

int main()
{
    long n;
    n = 105;
    prime_factorization(n);
      
    return 0;
}
