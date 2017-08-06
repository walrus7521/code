#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"

int heap[256];
int size = 0;


void heap_show()
{
    int i;
    for (i = 0; i <= size; i++) {
        printf("a[%02d] = %02d\n", i, heap[i]);
    }
}

void down_max(int k)
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

int delete_max()
{
    int max, last;
    max = heap[1];
    last = heap[size--];
    heap[1] = last;
    down_max(1);
    return max;
}

void up_max(int k)
{
    int v;
    v = heap[k];
    while (heap[k/2] <= v) {
        heap[k] = heap[k/2];
        k = k/2;
    }
    heap[k] = v;
}

void insert_max(int v)
{
    heap[++size] = v;
    up_max(size);
}

void heapify_max(int *a, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        insert_max(a[i]);
    }
    printf("\n");
}

void down_min(int k)
{
    int child, last;
    last = heap[k]; /* grab min */
    while (k <= size/2) {
        child = 2 * k;
        if (child < size && heap[child+1] < heap[child]) child++;
        if (last <= heap[child]) break;
        heap[k] = heap[child];
        k = child;
    }
    heap[k] = last;
}

int delete_min()
{
    int min, last;
    min = heap[1];
    last = heap[size--];
    heap[1] = last;
    down_min(1);
    return min;
}

void up_min(int k)
{
    int v;
    v = heap[k];
    while (heap[k/2] > v) {
        heap[k] = heap[k/2];
        k = k/2;
    }
    heap[k] = v;
}

void insert_min(int v)
{
    heap[++size] = v;
    up_min(size);
}

void heapify_min(int *a, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        insert_min(a[i]);
    }
}

void test_min_heap()
{
    int a[] = { 34, 5, 23, 12, 33, 98, 4, 13, 44, 37, 1, 86, 8};
    size = 0;
    heap[0] = -INT_MAX;
    heapify_min(a, 13);
    heap_show();
    while (size != 0) {
        printf("%d ", delete_min());
    }
    printf("\n");
}

void test_max_heap()
{
    int a[] = { 34, 5, 23, 12, 33, 98, 4, 13, 44, 37, 1, 86, 8};
    size = 0;
    heap[0] = INT_MAX;
    heapify_max(a, 13);
    heap_show();
    while (size != 0) {
        printf("%d ", delete_max());
    }
    printf("\n");
}

int heap_test()
{
    test_min_heap();
    test_max_heap();
    return 0;
}

