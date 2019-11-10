#include "types.h"

int heap[256] = {INT_MAX};
int size = 0;

void show() {
    int i;
    for (i = 1; i <= size; i++) printf("a[%02d] = %02d\n", i, heap[i]);
}

void up_min(int k) {
    int v = heap[k];
    while (heap[k/2] > v) {
        heap[k] = heap[k/2];
        k = k/2;
    }
    heap[k] = v;
}

void down_min(int k)
{
    int child, last = heap[k]; /* grab min */
    while (k <= size/2) {
        child = 2 * k;
        if (child < size && heap[child+1] < heap[child]) child++;
        if (last <= heap[child]) break;
        heap[k] = heap[child];
        k = child;
    }
    heap[k] = last;
}

int main()
{
    int a[] = {3,7,2,5,9};
    int i, len=sizeof(a) / sizeof(a[0]);

    printf("min heap\n");
    size = 0;
    heap[0] = -INT_MAX;
    for (i = 0; i < len; i++) {
        heap[++size] = a[i]; // insert at bottom
        up_min(size); // bubble up
    }
    show();
    while (size != 0) {
        int min = heap[1]; // save top
        heap[1] = heap[size--]; // copy bottom to top
        down_min(1); // sink down
        printf("%d ", min);
    }
}

