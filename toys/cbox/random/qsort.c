/*  
 * Divide and conquer sorting
 * quicksort(list) 
 * {
 *      if the list has length greater than 1 then
 *      {
 *          partition the list into lowlist, highlist
 *          sort(lowlist);
 *          sort(highlist);
 *          combine(lowlist, highlist);
 *      }
 * }
 */
#include <stdio.h>

void swap(int *a, int i, int j, char tag) {
    int tmp;
    //printf("swap[%c](a[%d]:%d, a[%d]:%d)\n", tag, i, a[i], j, a[j]);
    tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void show(int *A, int sz) {
    int i;
    for (i = 0; i < sz; ++i) {
        printf("S[%d] = %d, ", i, A[i]);
    }
    printf("\n");
}

int partition(int *A, int lo, int hi) {
    int i, p, firsthigh;
    p = hi; /* pick a partition (=hi) */
    firsthigh = lo; /* firsthigh is the partition boundary */
    for (i = lo; i < hi; ++i) {
        if (A[i] < A[p]) {
            swap(A, i, firsthigh, 'b');
            firsthigh++;
        }
    }
    swap(A, p, firsthigh, 'c'); /* finally put pivot where it belongs */
    return firsthigh;
}

void quicksort(int *A, int lo, int hi) {
    int p;
    if (lo < hi) {
        p = partition(A, lo, hi);
        quicksort(A, lo, p-1);
        quicksort(A, p+1, hi);
    }
}


int main()
{
    int a[] = {26,33,35,29,19,12,22,15,42,69,1};
    int sz = sizeof(a) / sizeof(a[0]);
    show(a, sz);
    quicksort(a, 0, sz-1);
    show(a, sz);
    return 0;
}
