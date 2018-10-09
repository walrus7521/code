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
    printf("rsq(%d):\n", n);
    int sum = 0;
    printf("\tft[%d] = %d\n", n, ft[n]);
    sum += ft[n];
    while (n > 0) {
        n -= (n & (-n));
        printf("\tft[%d] = %d\n", n, ft[n]);
        sum += ft[n];
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

int main()
{
    for (int i = 0; i < 11; i++) {
        adjust(scores[i], 1);
    }
    dump();
    int n = 6;
    int s = rsq1(n);
    printf("rsq(%d) = %d\n", n, s);
    int t = rsq2(3,10);
    printf("rsq2 = %d\n", t);
}

