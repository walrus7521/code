#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// https://www.geeksforgeeks.org/huffman-decoding/

int g_heap[256] = {INT_MAX};
int g_size = 0;

void heap_show() {
    int i;
    for (i = 1; i <= g_size; i++) printf("a[%02d] = %02d\n", i, g_heap[i]);
}

void down_min(int k) {
    int child, last = g_heap[k]; /* grab min */
    while (k <= g_size/2) {
        child = 2 * k;
        if (child < g_size && g_heap[child+1] < g_heap[child]) child++;
        if (last <= g_heap[child]) break;
        g_heap[k] = g_heap[child];
        k = child;
    }
    g_heap[k] = last;
}

void up_min(int k) {
    int v = g_heap[k];
    while (g_heap[k/2] > v) {
        g_heap[k] = g_heap[k/2];
        k = k/2;
    }
    g_heap[k] = v;
}

int get_min()
{
    int min = g_heap[1]; // save top
    g_heap[1] = g_heap[g_size--]; // copy bottom to top
    down_min(1); // sink down
    return min;
}

void put(int k)
{
    g_heap[++g_size] = k; // insert at bottom
    up_min(g_size); // bubble up
}

int main()
{
    int a[] = { 60, 25, 10, 5 };
    int i, len=sizeof(a) / sizeof(a[0]);

    printf("min heap\n");
    g_size = 0;
    g_heap[0] = -INT_MAX;
    for (i = 0; i < len; i++) {
        put(a[i]);
    }
    heap_show();
    while (g_size >= 2) {
        int min1 = get_min();
        int min2 = get_min();
        int new = min1 + min2;
        printf("%02d %02d => %02d\n", min1, min2, new);
        put(new);
    }
    heap_show();

    printf("\n");
}

