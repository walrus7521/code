#include <stdio.h>
#include <limits.h>

int g_heap[256];
int g_size = 0;

void heap_show()
{
    for (int i = 1; i <= g_size; i++) printf("a[%02d] = %02d\n", i, g_heap[i]);
}

void down_max(int k) // k = 1
{
    int child, last = g_heap[k]; /* grab max */
    while (k <= g_size/2) {
        child = 2 * k;
        if (child < g_size && g_heap[child] < g_heap[child+1]) child++;
        if (last >= g_heap[child]) break;
        g_heap[k] = g_heap[child];
        k = child;
    }
    printf("down k: %d size: %d\n", k, g_size);
    g_heap[k] = last;
}

void up_max(int k) // k = size
{
    int v = g_heap[k];
    printf("upping: %d\n", v);
    while (g_heap[k/2] <= v) {
        g_heap[k] = g_heap[k/2];
        k = k/2;
    }
    printf("up k: %d\n", k);
    g_heap[k] = v;
}

int main()
{
    int a[] = { 34, 5, 23, 12, 33, 98, 4, 13, 44, 37, 1, 86, 8};
    int i, len=sizeof(a) / sizeof(a[0]);
    printf("max heap - len %d\n", len);
    g_size = 0;
    g_heap[0] = INT_MAX;
    for (i = 0; i < len; i++) {
        g_heap[++g_size] = a[i]; // insert at bottom
        up_max(g_size); // bubble up
    }
    heap_show();
    while (g_size != 0) {
        int max = g_heap[1]; // save top
        g_heap[1] = g_heap[g_size--]; // copy bottom to top
        down_max(1); // sink down
        printf("%d ", max);
    }
    printf("\n");
    return 0;
}

