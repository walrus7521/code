#include "utils.h"

#define LSOne(s) (s & (-s))

int size = 11;
int ft[11] = {0};
int scores[] = {2,4,5,5,6,6,6,7,7,8,9};

void dump()
{
    for (int i = 0; i < size; i++) {
        printf("ft[%02d] = %d\n", i, ft[i]);
    }
}

int rsq1(int n)
{
    printf("rsq1(%02x)\n", n);
    int sum = 0;
    printf("\tft[%02x] = %d\n", n, ft[n]);
    sum += ft[n];
    n -= LSOne(n);
    while (n > 0) {
        printf("\tft[%02x] = %d\n", n, ft[n]);
        sum += ft[n];
        n -= LSOne(n);
    }
    return sum;
}

int rsq2(int a, int b)
{
    return rsq1(b) - rsq1(a-1);
}

void adjust(int k, int v)
{
    for (; k < size; k += LSOne(k)) {
        ft[k] += v;
    }
}

void test_lsone()
{
    int n=90, s;
    s = LSOne(90);
    printf("%d + LSOne(%d) = %d\n", n, s, n+s);
    printf("%d - LSOne(%d) = %d\n", n, s, n-s);
    return;

    while (n) {
        s = n & (-n);
        printf("%02X => %02X\n", n, s);
        n-=s;
    }
}

void uva725()
{
    int N = 2;
    for (int fghij = 1234; fghij <= 98765/N; fghij++) {
        int abcde = fghij * N;
        int tmp, used = (fghij < 10000); // if digit f=0, then flag
        tmp = abcde; while (tmp) { used |= 1 << (tmp % 10); tmp /= 10; }
        tmp = fghij; while (tmp) { used |= 1 << (tmp % 10); tmp /= 10; }
        if (used == (1<<10) - 1)
            printf("%0.5d / %0.5d = %d\n", abcde, fghij, N);
    }
}

int main()
{
    uva725();
    //test_lsone();
/*
    for (int i = 0; i < 11; i++) {
        adjust(scores[i], 1);
    }
    //dump();
    int n = 6;
    //int s = rsq1(n);
    //printf("rsq(%02x) = %d\n", n, s);
    int t = rsq2(3,10);
    printf("rsq2 = %d\n", t);
*/
}

