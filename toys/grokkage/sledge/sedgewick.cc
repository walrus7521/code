#include <stdio.h>
#include <string.h>
#include <math.h>

// sedgewick

#define MAXN 100

void arr_show(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++) printf("%c ", a[i]);
    printf("\n");
}

void swap(int a[], int i, int j)
{
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void bubsort(int a[], int n)
{
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            if (a[i] > a[j]) {
                swap(a, i, j);
            }
        }
    }
}

void selsort(int a[], int n)
{
    int i, j, min;
    for (i = 0; i < n; i++) {
        min = i;
        for (j = i+1; j < n; j++) {
            if (a[j] < a[min]) min = j;
        }
        swap(a, i, min);
    }
}

void inssort(int a[], int n)
{
    int i, j, v;
    for (i = 0; i < n; i++) {
        v = a[i]; j = i;
        while (a[j-1] > v) {
            a[j] = a[j-1]; j--;
        }
        a[j] = v;
    }
}

void indirect_sort(int a[], int p[], int n)
{
    int i, j, v;
    for (i = 0; i < n; i++) p[i] = i;
    for (i = 1; i < n; i++) {
        v = p[i]; j = i;
        while (a[p[j-1]] > a[v]) {
            p[j] = p[j-1];
            j--;
        }
        p[j] = v;
    }
}

unsigned int bits(unsigned int x, int k, int j)
{
    return ((x >> k) & ~(~0 << j));
}

void radix_exchange_sort(int a[], int l, int r, int b)
{
    int t, i, j;
    printf("radix: l:%d r:%d b:%d\n", l, r, b);
    if (r > l && b >= 0) {
    //if (r > l && b > 0) {
        i = l; j = r;
        while (j != i) {
            while (bits(a[i], b, l) == 0 && i < j) i++;
            while (bits(a[j], b, l) != 0 && j > i) j--;
            //printf("exchg: %d %d\n", i, j);
            t = a[i]; a[i] = a[j]; a[j] = t;
        }
        if (bits(a[r], b, l) == 0) j++;
        radix_exchange_sort(a, l, j-1, b-1);
        radix_exchange_sort(a, j, r, b-1);
    }
}

int partition(int a[], int l, int r)
{
    int i, j, v, t;
    v = a[r];
    i = l-1;
    j = r;
    for (;;) {
        while (a[++i] < v) ;
        while (a[--j] > v) ;
        if (i >= j) break;
        t = a[i]; a[i] = a[j]; a[j] = t;
    }
    t = a[i]; a[i] = a[r]; a[r] = t;
    return i;
}

void select_kth_largest(int a[], int l, int r, int k)
{
    int i;
    if (r > l) {
        i = partition(a, l, r);
        if (i > l+k-i) select_kth_largest(a, l, i-1, k);
        if (i < l+k-i) select_kth_largest(a, i+1, r, k-i);
    }
}

#if 1
int main()
{
    int n=0, i; //, a[MAXN+1];
    //while (scanf("%d", &a[n]) != EOF) n++;
    int a[] = {'a','s','o','r','t','i','n','g','e','x','a','m','p','l','e'};
    int p[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    int k[] = {1,73,25,87,42,54,66,28};

    n = 15;
    //selsort(a, n);
    //inssort(a, n);
    //bubsort(a, n);
    //bubsort(a, n);
    //radix_exchange_sort(a, 1, 14, 30);
    //for (i = 0; i < n; i++) printf("%c ", a[i]);
    //indirect_sort(a, p, n); for (i = 0; i < n; i++) printf("%c ", a[p[i]]);
    //printf("\n");

    //int select = 1;
    //select_kth_largest(k, 0, 7, select);
    //printf("k[select] = %d\n", k[select]);

}
#endif
