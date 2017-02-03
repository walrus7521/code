#include <stdio.h>

#define LE(a,b) (a <= b)
#define LT(a,b) (a < b)
#define GE(a,b) (a >= b)
#define GT(a,b) (a > b)
#define EQ(a,b) (a == b)

void swap(int *a, int i, int j) {
    int tmp;
    //printf("swap(a[%d]:%d, a[%d]:%d)\n", i, a[i], j, a[j]);
    tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void show(int *a, int sz) {
    int i;
    for (i = 0; i < sz; ++i) {
        printf("a[%d] = %d, ", i, a[i]);
    }
    printf("\n");
}

void insert_linear_search(int *a, int sz) {
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
    //for (i = 1; i < sz-1; ++i) {
    for (i = 1; i < sz; ++i) {
        //printf("i = %d\n", i);
        //show(a, sz);
        //for (p = i+1; p > 0; p--) {
        for (p = i; p > 0; p--) {
            if (LT(a[p],a[p-1])) {
                swap(a, p, p-1);
            }
        }
    }
    //show(a, sz);
}

int binsearch(int *a, int i, int j, int x) {
    int m;
    m = (i+j)/2;
    while (i < j) {
        if (LT(x, a[m])) {
            j = m-1;
        } else {
            i = m;
        }
    }
    return m;
}

void insert_binsearch(int *a, int sz) {
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
    for (i = 1; i < sz-1; ++i) {
        printf("i = %d\n", i);
        show(a, sz);
        for (p = i+1; p > 0; p--) {
            if (LT(a[p],a[p-1])) {
                swap(a, p, p-1);
            }
        }
    }
    show(a, sz);
}

int main() {
    //int a[] = {3,7,4,2,9,8,1};
    int a[] = {26,33,35,29,19,12,22};
     int sz = sizeof(a) / sizeof(a[0]);
    show(a, sz);
    //insert_binsearch(a, sz);
    insert_linear_search(a, sz);
    show(a, sz);
    return 0;
}
