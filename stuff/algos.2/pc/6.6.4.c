#include <stdio.h>

/*
 *  Let n denotes the length of the expression, d denotes the depth at most, 
 *  and the count is f (n, d). Obviously, f (n, d) = 0 when n is odd. For other 
 *  conditions, let us consider where we can find the corresponding parenthesis 
 *  of the leftmost one. It can be only found at the even places. For place 2, 
 *  this yields f (2, d-1) * f (n-2, d) ways of correctly built expressions. 
 *  And for place 4, the number will be f (4, d-1) * f (n-4, d). So we can 
 *  draw this recurrence from the above observation 
 *
 *  f (n, d) = E {i: 2 -> n-2, i + = 2: f (i, d-1) * f (ni, d)} 
 *      and and base cases are 
 *  f (0, d) = 1 where d >= 0 

 *  f(6, 2) = 3
 *  f(300, 150) = 1
 *
 * Hint: Formulate a recurrence w/2 parameter version of Catalan.
 *
 */

#define nsize 301
#define dsize 151
#define MAXN  nsize

unsigned long long numbers[nsize][dsize], results[nsize][dsize];

void gen_numbers()
{ 
    int d, n, i;
    for (d = 0; d < dsize; ++d) numbers[0][d] = 1; 
    for (n = 2; n < nsize; n += 2) {
        for (d = 1; d < dsize; ++d) {
            for (i = 2; i <= n; i += 2) {
                numbers[n][d] += numbers[i-2][d-1] * numbers[i][d]; 
            }
        }
    }
    for (n = 1; n <nsize; ++n) {
        for (d = 1; d <dsize; ++d) {
            results[n][d] = numbers[n][d] - numbers[n][d-1]; 
        }
    }
#if 0
    for (n = 0; n < nsize; n++)
        for (d = 0; d < dsize; d++)
            printf("r[%d][%d] = %lld\n", n, d, numbers[n][d]);
#endif
} 

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

<<<<<<< HEAD
long catalan2(int n, int d)
{
    long binco1 = binomial_coefficient(n, d-1);
    long binco2 = binomial_coefficient(d, n-2);
    double cat = binco1 * binco2;
    printf("%d/%d = %ld %ld ==> %ld\n", n, d, binco1, binco2, (long) cat);
    return (long) cat;
}

void show()
{
    int n, k;
    for (n = 0; n < nsize; n++)
        for (k = 0; k < dsize; k++)
            printf("r[%d][%d] = %lld\n", n, k, results[n][k]);
}
=======
int val(int n)
{
    long dual_cat = 0;
    int i;
    for (i = 0; i < n; i++) 
        dual_cat += catalan(i-1) * catalan(0);
}

>>>>>>> d2ec914ccae06e84735ad9c6efbae2b33b43b016
int main()
{
    int n, k;
    gen_numbers();
#if 0
    n = 6; k = 1;
    printf("%d/%d = %lld\n", n, k, results[n][k]);
    n = 6; k = 2;
    printf("%d/%d = %lld\n", n, k, results[n][k]);
    n = 6; k = 3;
    printf("%d/%d = %lld\n", n, k, results[n][k]);
    show();
    for (n = 0; n < 8; n++)
        printf("cat %d = %ld\n", n, catalan(n));
#endif
    n = 6; k = 2;
    catalan2(n, k);
    n = 300; k = 150;
    catalan2(n, k);
    return 0;
}
