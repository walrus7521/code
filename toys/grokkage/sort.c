#include <stdio.h>

#define MAXN 100

void swap(int a[], int i, int j)
{
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void urrsort(int a[], int n)
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

int main()
{
    int n=0, i, a[MAXN+1];
    while (scanf("%d", &a[n]) != EOF) n++;
    selsort(a, n);
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

