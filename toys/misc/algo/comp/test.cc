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

void uva11565()
{
    int A = 6, B = 6, C = 14;
    bool sol = false;
    int x,y,z;
    for (x = -22; x <= 22; x++)
        for (y = -100; y <= 100; y++)
            for (z = -100; z <= 100; z++)
                if (x != y && x != z && y != z &&
                        x + y + z == A && 
                        x * y * z == B &&
                        x*x + y*y + z*z == C) {
                    if (!sol) printf("%d %d %d\n", x, y, z);
                    sol = true;
                }
}


void uva11742()
{
    int p[8] = {0,1,2,3,4,5,6,7}, N = 8;
    for (int i = 0; i < N; i++) p[i] = i;
    do {
        for (int i = 0; i < N; i++) printf("%d ", p[i]);
        printf("\n");
    } while (next_permutation(p, p + N));
}

void ex123t8()
{
    int p[8], N = 4;
    bool in_subset = false;
    for (int i = 0; i < N; i++) p[i] = i;
    int mask = (1 << N);
    printf("mask: %d\n", mask);
    for (int i = 0; i < mask; i++) {
        printf("%d> ", i);
        for (int j = 0; j < N; j++) {
            in_subset = false;
            if (i & (1 << j)) {in_subset = true;}
            //else              printf("not");
            //printf("(%04x,%d) jmask: %04x, and: %04x, p:%d", i, j, (1 << j), i & (1 << j), p[j]);
            if (in_subset == true) printf("%d ", p[j]);
        }
        printf("\n");
    }
}

void uva12455()
{// subset of N list sum = X? see Ex. 1.2.3 task 8
    int l[] = {1,2,3,4,5,6,7,8}, N = 8, X = 3;
    int mask = (1 << N);
    int j;
    for (int i = 0; i < mask; i++) {
        int sum = 0;
        for (j = 0; j < N; j++) {
            if (i  & (1 << j)) sum += l[j];
            printf("%04x,%d> %04x and: %04x, sum: %d\n", i, j, (1 << j), i & (1 << j), sum);
        }
        if (sum == X) { printf("found sum(%d,%d): %d\n", i, j, sum); break; }
    }
}

int main()
{
    //printf("%x\n", (1<<10)-1);
    //uva725();
    //uva11565();
    ex123t8();
    //uva12455();
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

