#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int heap[256];
int size = 0;

void down(int k)
{
    int child, last;
    last = heap[k]; /* grab max */
    while (k <= size/2) {
        child = 2 * k;
        if (child < size && heap[child] < heap[child+1]) child++;
        if (last >= heap[child]) break;
        heap[k] = heap[child];
        k = child;
    }
    heap[k] = last;
}

void up(int k)
{
    int v;
    v = heap[k];
    while (heap[k/2] <= v) {
        heap[k] = heap[k/2];
        k = k/2;
    }
    heap[k] = v;
}

int delete()
{
    int max, last;
    max = heap[1];
    last = heap[size--];
    heap[1] = last;
    down(1);
    return max;
}

void insert(int v)
{
    heap[++size] = v;
    up(size);
}

void show()
{
    int i;
    for (i = 0; i <= size; i++) {
        printf("a[%02d] = %02d\n", i, heap[i]);
    }
}

void heapify(int *a, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        insert(a[i]);
    }
    printf("\n");
}

int main()
{
    int a[] = { 34, 5, 23, 12, 33, 98, 4, 13, 44, 37, 1, 86, 8};
    size = 0;
    heap[0] = INT_MAX;
    heapify(a, 13);
    show();
    while (size != 0) {
        printf("%d ", delete());
    }
    printf("\n");
    return 0;
}

