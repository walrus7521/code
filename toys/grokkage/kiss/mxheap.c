#include <stdio.h>
#include <limits.h>

int heap[256]={INT_MAX}; int size = 0;

void up_max() {
    int k = size, v = heap[size]; // new item @ bottom (@youngest child)
    printf("insert(upping): %02d ", v);
    while (heap[k/2] <= v) { // has sentinal @[0], [parent] <= new item
        heap[k] = heap[k/2]; // [child] = [parent]
        k = k/2; // goto parent
    } // stop search when v is not larger than parent
    printf(" => %02d\n", k);
    heap[k] = v; // place new item @k [child]
}

void down_max() {
    int k=1, child, top = heap[k]; /* grab top=last/min */
    printf("downing %02d from %02d ", top, k);
    while (k <= size/2) {
        child = 2 * k;
        if (child < size && heap[child] < heap[child+1]) child++;
        if (top >= heap[child]) break;
        heap[k] = heap[child];
        k = child;
    }
    printf(" => %02d size: %02d : ", k, size);
    heap[k] = top;
}

int main() {
    int a[] = { 34, 5, 23, 12, 33, 98, 4, 13, 44, 37, 1, 86, 8};
    int i, len=sizeof(a) / sizeof(a[0]);
    printf("max heap - len %d\n", len);
    for (i = 0; i < len; i++) {
        heap[++size] = a[i]; // insert at bottom
        up_max(); // bubble up
    }
    for (i=1;i<=size;i++)printf("a[%02d] = %02d\n",i,heap[i]);
    while (size != 0) {
        int max = heap[1]; // save top
        heap[1] = heap[size--]; // copy bottom to top
        down_max(); // sink top down
        printf("mx => %02d\n", max);
    }
}

