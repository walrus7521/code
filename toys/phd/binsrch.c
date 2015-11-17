#include <stdio.h>

void show(int *a, int sz) {
    int i;
    for (i = 0; i < sz; ++i) {
        printf("[%02d], ", a[i]);
    }
    printf("\n");
}

int binsearch(int x, int *a, int n) {
/*
 * binary search of array a of size n
 * for the value x.
 */
    int low, high, mid;
    low = 0;
    high = n-1;
    while (low <= high) {
        mid = (low+high)/2;
        if (x > a[mid]) low = mid + 1;
        else if (x < a[mid]) high = mid - 1;
        else return x;
    }
    return -1;
}

int main() {
    int a[] = {1, 3, 5, 6, 8, 9, 10, 22, 45, 89, 90, 99, 101};
    int sz = sizeof(a) / sizeof(a[0]);
    int x = 45, z, i;
    show(a, sz);
    for (i = 0; i < sz; ++i) {
        x = a[i];
        z = binsearch(x, a, sz);
        printf("binsearch of %02d %s\n", 
                x, (z == x) ? "found" : "not found");
    }
    return 0;
}
