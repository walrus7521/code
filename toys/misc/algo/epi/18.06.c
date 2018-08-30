#include <stdio.h>
#include <stdlib.h>

/**

Let A be an array of n numbers.  Let t be a number, and k be an integer in [1,n].
Define A to k-create t if and onl if there exists k indices i0, i1, i2, ... , ik-1 
(not necessarily distinct) such that SUM[j-0, k-1]A[ij] = t;

Design an algorithm that takes as input an array A and a number t, 
and determines if A 3-creates t.

1. Sort A
2. For each A[i], search for indices j and k, such that A[j] + A[k] = t - A[i];

 */

int HasTwoSum(int *A, int len, int t) {
    int j = 0, k = len - 1;
    
    while (j <= k) {
        if (A[j] + A[k] == t) {
            return 1;
        } else
        if (A[j] + A[k] < t) {
            ++j;
        } else { // A[j] + A[k] > t
            --k;
        }
    }
    //cout << " no" << endl;
    return 0;
}

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int HasThreeSum(int *A, int len, int t) {
    qsort((void *) A, (size_t) len, (size_t) sizeof(int), cmpfunc);
    int a;
    for (a = 0; a < len; a++) {
        // finds if the sum of 2 numbers in A equals to t - a.
        if (HasTwoSum(A, len, t-a)) {
            return 1;
        }
    }
    return 0;
}

int main()
{
    int vi[] = {1, 2, 3, 4, 5, 7};
    int has3, sum, len;
    len = sizeof(vi)/sizeof(vi[0]);
    for (sum = 0; sum < 12; ++sum) {
        has3 = HasThreeSum(vi, len, sum);
        printf(" %d has 3 sum? %d\n", sum, has3);
    }
    return 0;
}
