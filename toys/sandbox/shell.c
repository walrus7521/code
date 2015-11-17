#include <stdio.h>

#define LE(a,b) (a <= b)
#define LT(a,b) (a < b)
#define GE(a,b) (a >= b)
#define GT(a,b) (a > b)
#define EQ(a,b) (a == b)

void show(int a[], int sz) {
    int i;
    printf("show: a, sz=%d\n", sz);
    for (i = 0; i < sz; ++i) {
        printf("a[%d] = %d\n", i, a[i]);
    }
    printf("\n");
}

void swap(int *a, int i, int j) {
    int tmp;
    //printf("swap(a[%d]:%d, a[%d]:%d)\n", i, a[i], j, a[j]);
    tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void sort_interval(int a[], int sz, int start, int inc) {
/*
 * insertion into ordered list
 * p is the partition between the ordered
 * upper portion and the unordered lower
 * portion of the list. as new items are 
 * encountered, a reverse scan is performed 
 * from the point of the new item to the 
 * beginning of the list to maintain the 
 * invariant of an ordered upper portion.
 */
    int p, i;
    //printf("sort_interval: start %d, increment %d\n", start, inc);
    //show(a, sz);
    for (i = start; i < sz; i+=inc) {
        for (p = i; p-inc >= 0; p-=inc) {
            if (LT(a[p],a[p-inc])) {
                swap(a, p, p-inc);
            }
        }
    }
    //show(a, sz);
}

void shell(int A[], int sz) {
    int increment, start, i;
    increment = sz;
    do {
        increment = increment/3 + 1;
        for (start = 0; start < increment; ++start) {
            sort_interval(A, sz, start, increment);
        }   
    } while (increment > 1);
}

int main() {
    int a[] = {3,7,2,9,6,5,1};
    int sz = sizeof(a)/sizeof(a[0]);
    show(a, sz);
    shell(a, sz);
    show(a, sz);
    return 0;
}
