#include <stdio.h>

void swap(int *a, int i, int j)
{
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

void DutchFlagPartition(int pivot_index, int *A, int len) {
    int pivot = A[pivot_index];

    printf("pivot = %d\n", pivot);
    /**
      * keep the following invariants during partitioning:
      * bottom group: A_ref[0 : smaller - 1].
      * middle group: A_ref[smaller : equal - 1].
      * unclassified group: A_ref[equal : larger].
      * top group: A_ref[larger + 1 : A-ref.size() - 1].
      */

    int smaller = 0, equal = 0, larger = len - 1;
    // when there is any unclassified element.
    while (equal <= larger) {
        // A_ref[equal] is the incoming unclassified element.
        if (A[equal] < pivot) {
            swap(A, smaller++, equal++);
        } else
        if (A[equal] == pivot) {
            ++equal;
        } else { // A_ref[equal] > pivot.
            swap(A, equal, larger--);
        }
    }
}

/* still need to implement variants
 */

void dump(int *vi, int len)
{
    for (int i = 0; i < len; i++) {
        printf("%d\n", vi[i]);
    }
    printf("\n");
}

int main()
{
    int vi[] = {3, 1, 0, 8, 6, 7, 5, 3, 0, 9};
    dump(vi, 10);
    DutchFlagPartition(7, vi, 10);
    dump(vi, 10);
    return 0;
}
