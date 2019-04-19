#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))

void swap (int *a, int *b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
}

void shuffle_array(int a[], int n)
{ 
    int i;
    srand ( time(NULL) ); 
    for (i = n-1; i > 0; i--) { 
        int j = rand() % (i+1); 
        swap(&a[i], &a[j]); 
    }
} 

void show_array(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++) {
        printf("%d, ", a[i]);
    }
    printf("\n");
}

//insertion
void insertion(int a[], int n)
{
    int i, j;
    for (i = 1; i < n; i++) {
        for (j = i; j > 0; j--) {
            if (a[j-1] > a[j]) {
                int tmp = a[j-1];
                a[j-1] = a[j];
                a[j] = tmp;
            }
        }
    }
}

// merge sort
void merge(int a[], int l, int m, int r)
{
    int i, j, k, n1, n2;
    n1 = m - l + 1;
    n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++) L[i]=a[l+i];
    for (j = 0; j < n2; j++) R[j]=a[m+1+j];
    i = j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) { a[k++] = L[i++]; } 
        else              { a[k++] = R[j++]; }
    }
    while (i < n1) { a[k++] = L[i++]; }
    while (j < n2) { a[k++] = R[j++]; }
}

void merge_sort(int a[], int l, int r)
{
    if (l < r) {
        int m = (l+r)/2;
        merge_sort(a, l, m);
        merge_sort(a, m+1, r);
        merge(a, l, m, r);
    }
}

// heapsort
int g_heap[256] = {INT_MAX};
int g_size = 0;
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

int delete_min() {
    int min = g_heap[1]; // save top
    g_heap[1] = g_heap[g_size--]; // copy bottom to top
    down_min(1); // sink down
    return min;
}

void heap_sort(int *a, int n)
{
    int i;
    g_size = 0;
    g_heap[0] = -INT_MAX;
    for (i = 0; i < n; i++) {
        g_heap[++g_size] = a[i]; // insert at bottom
        up_min(g_size); // bubble up
    }
    i = 0;
    while (g_size != 0) { a[i++] = delete_min(); }
}

// BST sort
// AVL sort
// counting, radix
// hash
// bfs
// dfs, topsort
// ssps
// dijkstra

int main()
{
    int a[] = {7,2,9,4,3,6,8};
    int n = sizeof(a)/sizeof(a[0]);
    shuffle_array(a, n);
    //insertion(a,n);
    show_array(a, n);
    //merge_sort(a, 0, n-1);
    //show_array(a, n);
    heap_sort(a, n);
    show_array(a, n);
}

