#include <stdio.h>
#include "../box/binsrch.h"

int find_first_k2(int x, int v[], int n)
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
        else {/* found match */
            int first_k = mid;
            while (v[first_k] == x) first_k--;
            return first_k+1;
        }
    }
    return -1; /* no match */
}

int main()
{
    int x[] = {2,3,5,5,5,7,8,9}, ret;
    int i, len = sizeof(x) / sizeof(x[0]);
    for (i = 0; i < len; i++) {
        printf("[%d] = %d", i, x[i]); 
        printf("\n");
    }
    ret = binarysearch(5, x, len);
    printf("binsearch:    x[%d] = %d\n", ret, x[ret]);
    ret = find_first_k2(5, x, len);
    printf("find_first_k: x[%d] = %d\n", ret, x[ret]);
    return 0;
}

