#include <stdio.h>

void swap(int a[], int i, int j)
{
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void qsort(int v[], int left, int right)
{
    int i, last;
    if (left >= right) return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; ++i) {
        if (v[i] < v[left])
            swap(v, ++last, i);
        swap(v, left, last);
        qsort(v, left, last-1);
        qsort(v, last+1, right);
    }
}

void show(int a[], int len)
{
    int i;
    for (i = 0; i < len; ++i) {
        printf("a[%d] = %d\n", i, a[i]);
    }
}

int main()
{
    int a[] = {2,4,21,6,4,2,9};
    int len = sizeof(a) / sizeof(a[0]);
    qsort(a, 0, len-1);
    show(a, len);
}
