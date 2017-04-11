#include <stdio.h>

#define exchg(A, B) { int t = A; A = B; B = t; }

// binary search
// selection sort
// divide and conquer: gcd

int gcd(int m, int n)
{
    if (n > m) exchg(m,n);
    printf("m:%d, n:%d => %d\n", m, n, m % n);
    if (m % n == 0) return n;
    return gcd(n,m-n);
}

void show(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++) {
        printf("%d, ", a[i]);
    }
    printf("\n");
}

int main()
{
    int g = gcd(1680, 640);
    printf("gcd: %d\n", g);
}
