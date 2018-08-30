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

int main()
{
    int n, k;
    n = 6; k = 1;
    printf("%d/%d = %ld\n", n, k, binomial_coefficient(n,k));
    n = 6; k = 2;
    printf("%d/%d = %ld\n", n, k, binomial_coefficient(n,k));
    n = 6; k = 3;
    printf("%d/%d = %ld\n", n, k, binomial_coefficient(n,k));
    return 0;
}

