#include <stdio.h>

void insertion(int a[], int n)
{
    int i, j;
    for (j = 1; j < n; ++j) {
        int key = a[j];
        i = j - 1;
        while (i >= 0 && a[i] > key) {
            a[i+1] = a[i];
            i--;
        }
        a[i+1] = key; // put key in its place
    }
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++) { L[i] = arr[l+i]; }
    for (j = 0; j < n2; j++) { R[j] = arr[m+j+1]; }

    i = j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    // rest of elements
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int l, int r)
{
    if (l < r) {
        int m = (l+r)/2;
        merge_sort(arr, l, m);
        merge_sort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

#define LEFT(i)     ((i)/2)
#define RIGHT(i)    (2*(i))
#define PARENT(i)   (2*(i)+1)
void max_heapify(int arr[], int i, int size)
{
    int l = LEFT(i);
    int r = RIGHT(i);
    int largest = 0;
    if (l <= size && arr[l] >arr[i]) {
        largest = l;
    } else {
        largest = i;
    }
    if (r <= size && arr[r] > arr[largest]) {
        largest = r;
    }
    if (largest != i) {
        int tmp = arr[largest];
        arr[largest] = arr[i];
        arr[i] = tmp;
        max_heapify(arr, largest, size);
    }
}

void build_max_heap(int arr[], int len, int size)
{
    size = len;
    int i;
    for (i = len/2; i >= 1; i--) {
        max_heapify(arr, i, size);
    }
}

void show(int *a, int n)
{
    int i;
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main()
{
    int a[] = {5,2,4,6,1,3};
    int len = sizeof(a) / sizeof(a[0]);

    show(a, len);
    //insertion(a, len);
    //merge_sort(a, 0, len-1);
    build_max_heap(a, len, len);
    show(a, len);
}

