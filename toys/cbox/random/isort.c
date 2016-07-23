#include <stdio.h>

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

void isort(int *a, int sz) {
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
    int i, j;
    for (i = 1; i < sz; ++i) {
        j = i;
        while (j > 0 && (a[j] < a[j-1])) {
            swap(a, j, j-1);
            --j;
        }
    }
}

int main() {
    int a[] = {26,33,35,29,19,12,22,15,42,69,1};
    int sz = sizeof(a) / sizeof(a[0]);
    show(a, sz);
    isort(a, sz);
    show(a, sz);
    return 0;
}
