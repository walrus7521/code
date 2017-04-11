#include <stdio.h>

#define exchg(A, B) { int t = A; A = B; B = t; }

// binary search
// selection sort
// divide and conquer: gcd

void selection(int a[], int n)
{
    int i, j, min;
    for (i = 0; i < n; i++) {
        min = i;
        for (j = i+1; j < n; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }
        exchg(a[i], a[min]);
    }
}

int gcd(int m, int n)
{
    if (m < n) exchg(m,n); //assert(m > n);
    printf("m:%4d, n:%4d, mod:%4d\n", m,n,m%n);
    return (m%n == 0) ? n : gcd(n, m%n);
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

    int a[] = {4,1,8,3,42,2};
    int n = sizeof(a)/sizeof(a[0]);
    show(a,n);
    selection(a,n);
    show(a,n);
}
