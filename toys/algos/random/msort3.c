 /*
 * Mergesort(list) Divide and conquer sorting
 * {
 *      if the list has length greater than 1 then {
 *          partition the list into lowlist, highlist
 *          Sort(lowlist);
 *          Sort(highlist);
 *          Combine(lowlist, highlist);
 *      }
 * }
 */
#include <stdio.h>
#include <stdlib.h>

#define LT(a,b) (a < b)
void swap(int *a, int i, int j) {
    int tmp;
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

int divide(int *A, int sz) {
    int part;
    if (sz % 2) part=(sz/2)+1;
    else part=sz/2;
    return part;
}

int *combine(int *A, int szA, int *B, int szB) {
    int i=0, j=0, k, *c;
    c = (int *) malloc(szA+szB);
    for (i = 0; i < szA; ++i) {
        c[i] = A[i];
    }
    for (j = 0; j < szB; ++j, ++i) {
        c[i] = B[j];
    }
    /* ainsert */
    for (i = 1; i < szA+szB; ++i) {
          for (k = i; k > 0; k--) {
              if (LT(c[k],c[k-1])) {
                  swap(c, k, k-1);
              }
          }
    }
    return c;
}

int *Mergesort(int *A, int sz) {
    int m, *low, *high, *comb;
    if (sz > 1) {
        m = divide(A, sz);
        low = A; high = A+m;
        Mergesort(low, m);
        Mergesort(high, sz-m);
        comb = combine(low, m, high, sz-m);
    }
    return comb;
}

int main()
{
    int a[] = {26,33,35,29,19,12,22,15,42,69,1};
    int *sorted;
    int sz = sizeof(a) / sizeof(a[0]);
    show(a, sz);
    sorted = Mergesort(a, sz);
    show(sorted, sz);
    return 0;
}
