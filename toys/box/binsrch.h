#include <stdio.h>

int binarysearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n-1;
    while (low <= high) {
        mid = (low+high)/2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else /* found match */
            return mid;
    }
    return -1; /* no match */
}

int binsrch_test()
{
    int x[] = {2,3,4,5,6,7,8,9}, ret;
    int i, len = sizeof(x) / sizeof(x[0]);
    for (i = 0; i < len; i++) printf("[%d:%d]", i, x[i]); printf("\n\n");
    printf("binarysearch: x[%d] = %d\n", binarysearch(2, x, 8), x[ret]);
    printf("binarysearch: x[%d] = %d\n", binarysearch(9, x, 8), x[ret]);
    printf("binarysearch: x[%d] = %d\n", binarysearch(4, x, 8), x[ret]);
    return 0;
}

