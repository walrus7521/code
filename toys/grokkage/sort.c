#include <stdio.h>

// sedgewick

#define MAXN 100

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


int main()
{
    int n=0, i; //, a[MAXN+1];
    //while (scanf("%d", &a[n]) != EOF) n++;
    int a[] = {'a','s','o','r','t','i','n','g','e','x','a','m','p','l','e'};
    int p[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    n = 15;
    //selsort(a, n);
    //inssort(a, n);
    //bubsort(a, n);
    //bubsort(a, n);
    indirect_sort(a, p, n);
    for (i = 0; i < n; i++) printf("%c ", a[p[i]]);
    printf("\n");
}

