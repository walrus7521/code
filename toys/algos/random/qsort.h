#include <stdio.h>

void swap(int v[], int i, int j)
{
    int temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort(int v[], int left, int right)
{
    int i, last;
    void swap(int v[], int i, int j);

    if (left >= right)  /* do nothing if array contains */
        return;         /* fewer than two elements      */
    swap(v, left, (left + right)/2); /* move partition elem */
    last = left;                     /* to v[0] */
    for (i = left+1; i <= right; i++) { /* partition */
        if (v[i] < v[left])
            swap(v, ++last, i);
    }
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

int qsort_test()
{
    int a[] = {2,4,7,1,3,9,4};
    int i = 6;
    for (i = 0; i < 6; i++) 
        printf("a[%d] = %d\n", i, a[i]);
    qsort(a, 0, 6);
    printf("\n");
    for (i = 0; i < 6; i++) 
        printf("a[%d] = %d\n", i, a[i]);
    return 0;
}
