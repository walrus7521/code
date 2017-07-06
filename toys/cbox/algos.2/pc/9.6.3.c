#include <stdio.h>
#include <math.h>

/*
 * Borrow from Floyd Warshall for shortest path
 *
 *
 */
#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

int dp[8][8];
#define MAX 7

void init()
{
    int i, j, k;
    for (i = 0; i <= MAX; i++)
         for (j = 0; j <= MAX; j++)
            dp[i][j] = 0;

    dp[1][2] = 30;
    dp[1][3] = 15;
    dp[1][4] = 10;
    dp[2][4] = 25;
    dp[2][5] = 60;
    dp[3][4] = 40;
    dp[3][6] = 20;
    dp[4][7] = 35;
    dp[5][7] = 20;
    dp[6][7] = 30;
}

void tour()
{
    int i, j, k, N;
    N = MAX;

    for (k = 1; k <= N; k++) {
        for (i = 1; i <= N; i++) {
            for (j = 1; j <= N; j++) {
                dp[i][j] = max(dp[i][j], min(dp[i][k], dp[k][j]));
            }
        }
    }
}

void tour2()
{
    int i, j, k, N;
    N = MAX;

    for (k = 1; k <= N; k++) {
        for (i = 1; i <= N; i++) {
            for (j = 1; j <= N; j++) {
                if (dp[i][k] + dp[k][j] < dp[i][j])
                    dp[i][j] = dp[i][k] + dp[k][j];
            }
        }
    }
}

void show()
{
    int i, j;
    for (i = 1; i <= MAX; i++) 
        for (j = 1; j <= MAX; j++)
            printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
}

int roundup(float v)
{
    float d = ceil(v);
    int i;
    i = d;
    return i;
}

int main()
{
    int s, t, p;
    float n;

    s = 1;
    t = 7;
    init();
    tour2();
    show();
    p = dp[s][t];
    printf("need to use edge (%d, %d)\n", s, t);
    n = 99.0 / (p - 1);
    printf("answer is 99 / (%d - 1) = %f\n", p, n);
    printf("trips = %d\n", roundup(n));
    return 0;
}

