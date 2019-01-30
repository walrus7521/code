#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_prime(int n)
{
    int i, bound;
    if (n % 2 == 0) return 0;
    if (n % 3 == 0) return 0;
    if (n % 5 == 0) return 0;
    bound = (int) sqrt((float) n);
    for (i = 7; i <= bound; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main()
{
    int i, n;
    n = 1000;
    for (i = 2; i <= n; i++) {
        if (prime(i)) {
            printf("%d\n", i);
        }
    }
}

