#include <stdio.h>
#include <limits.h>

int g_heap[256]={INT_MAX}; int g_size = 0;

void down_max() {
    int k=1, child, last = g_heap[k]; /* grab max */
    printf("downing %02d from %02d ", last, k);
    while (k <= g_size/2) {
        child = 2 * k;
        if (child < g_size && g_heap[child] < g_heap[child+1]) child++;
        if (last >= g_heap[child]) break;
        g_heap[k] = g_heap[child];
        k = child;
    }
    printf(" => %02d size: %02d : ", k, g_size);
    g_heap[k] = last;
}

void up_max() {
    int k = g_size, v = g_heap[k]; // new item @ bottom
    printf("insert(upping): %02d ", v);
    while (g_heap[k/2] <= v) { // has sentinal @[0]
        g_heap[k] = g_heap[k/2];
        k = k/2;
    } // stop search when v is not larger than parent
    printf(" => %02d\n", k);
    g_heap[k] = v; // place new item @k
}

int main() {
    int a[] = { 34, 5, 23, 12, 33, 98, 4, 13, 44, 37, 1, 86, 8};
    int i, len=sizeof(a) / sizeof(a[0]);
    printf("max heap - len %d\n", len);
    for (i = 0; i < len; i++) {
        g_heap[++g_size] = a[i]; // insert at bottom
        up_max(); // bubble up
    }
    for (i=1;i<=g_size;i++)printf("a[%02d] = %02d\n",i,g_heap[i]);
    while (g_size != 0) {
        int max = g_heap[1]; // save top
        g_heap[1] = g_heap[g_size--]; // copy bottom to top
        down_max(); // sink down
        printf("mx => %02d\n", max);
    }
}

