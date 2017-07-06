#include <stdio.h>

#define MAXN 100

/*
 *  How many ways to choose k things out of n possibilities
 *  | n | 
 *  | k |
 */
long binomial_coefficient(int n, int k)
{
    int i, j;
    long bc[MAXN][MAXN];

    for (i = 0; i <= n; i++) bc[i][0] = 1;
    for (j = 0; j <= n; j++) bc[j][j] = 1;
    for (i = 1; i <= n; i++)
        for (j = 1; j < i; j++)
            bc[i][j] = bc[i-1][j-1] + bc[i-1][j];

    return (bc[n][k]);
}

long catalan(int n)
{
    long binco = binomial_coefficient(2*n, n);
    double cat = (1.0 / (n + 1.0)) * binco;
    return (long) cat;
}

int main()
{
    int n, k;
    n = 64; k = 8;
    printf("binco[%d/%d] = %ld\n", n, k, binomial_coefficient(64, 8));
#if 0
    int i;
    for (i = 0; i < 12; i++)
        printf("cat(%2d) = %ld\n", i, catalan(i));
#endif
    return 0;
}

