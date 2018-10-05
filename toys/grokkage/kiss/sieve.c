// sieve of eratosthenes
#include "utils.h"

int main()
{
    int p, i, n = 120;
    char prime[n];
    memset(prime, 1, n);

    for (p = 2; p*p <= n; p++) {
        if (prime[p] == 1) {
            // update all multiples of p
            for (i = 2*p; i <=n; i+=p) prime[i] = 0;
        }
    }

    for (p = 2; p <= n; p++) {
        if (prime[p]) printf("%d\n", p);
    }
}
