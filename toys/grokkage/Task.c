#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define PUBLIC_API
#define PRIVATE static

typedef struct _record {
    int key, bus, id;
} record;

PRIVATE record g_heap[256] = {INT_MAX};
PRIVATE int g_size = 0;
PRIVATE void Task_Down(int k);
PRIVATE void Task_Up(int k);
PRIVATE void Task_Decrement_Keys(int amt);

PUBLIC_API void Task_Queue_Show() {
    int i;
    for (i = 1; i <= g_size; i++) printf("%02d, ", g_heap[i].key);
    printf("\n");
}

PUBLIC_API void Task_Insert(int key, int bus, int id)
{
    ++g_size;
    g_heap[g_size].key = key; // insert at bottom
    g_heap[g_size].bus = bus; // insert at bottom
    g_heap[g_size].id  = id; // insert at bottom
    Task_Up(g_size); // bubble up
}

PUBLIC_API int Task_Get_Min(int *key, int *bus, int *id)
{
    int min = g_heap[1].key;
    *key = g_heap[1].key;
    *bus = g_heap[1].bus;
    *id  = g_heap[1].id;
    g_heap[1].key = g_heap[g_size--].key; // copy bottom to top
    Task_Down(1); // sink down
    return min;
}

PRIVATE void Task_Down(int k) {
    int child, last = g_heap[k].key; /* grab min */
    while (k <= g_size/2) {
        child = 2 * k;
        if (child < g_size && g_heap[child+1].key < g_heap[child].key) child++;
        if (last <= g_heap[child].key) break;
        g_heap[k].key = g_heap[child].key;
        k = child;
    }
    g_heap[k].key = last;
}

PRIVATE void Task_Up(int k) {
    int v = g_heap[k].key;
    while (g_heap[k/2].key > v) {
        g_heap[k].key = g_heap[k/2].key;
        k = k/2;
    }
    g_heap[k].key = v;
}

PRIVATE void Task_Decrement_Keys(int amt)
{
    int i;
    for (i = 1; i <= g_size; i++) g_heap[i].key -= amt;
}


int main()
{
    int keys[] = { 34, 5, 23, 12, 33, 98, 4, 13, 44, 37, 1, 86, 8};
    int i, len=sizeof(keys) / sizeof(keys[0]);
    int key, bus, id;

    printf("min heap\n");
    g_size = 0;
    g_heap[0].key = -INT_MAX;
    for (i = 0; i < len; i++) {
        key = keys[i];
        bus = i;
        id = 42+i;
        Task_Insert(key, bus, id);
    }
    Task_Queue_Show();
    while (g_size != 0) {
        int min = Task_Get_Min(&key, &bus, &id);
        printf("%02d ", key);
        Task_Queue_Show();
        Task_Decrement_Keys(key);
    }
}

