#include <stdio.h>
#include <stdlib.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))

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
// BST sort
// AVL sort
// counting, radix
// hash
// bfs
// dfs, topsort
// ssps
// dijkstra
// bell-ford
// dp
// complexity

int main()
{
    int a[] = {7,2,9,4,3,6,8};
    int n = sizeof(a)/sizeof(a[0]);
    //insertion(a,n);
    show_array(a, n);
    merge_sort(a, 0, n-1);
    show_array(a, n);
}

