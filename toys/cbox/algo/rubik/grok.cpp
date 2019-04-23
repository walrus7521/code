#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define exchg(A, B) { int t = A; A = B; B = t; } 

void shuffle_array(int a[], int n)
{ 
    int i;
    srand ( time(NULL) ); 
    for (i = n-1; i > 0; i--) { 
        int j = rand() % (i+1); 
        exchg(a[i], a[j]); 
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
void Heapify(int A[], int i, int n)
{
    int left = 2*i;
    int right = 2*i + 1;
    int max;
    if ((left <= n) && (A[left] > A[i])) {
        max = left;
    } else {
        max = i;
    }
    if ((right <= n && (A[right] > A[max]))) {
        max = right;
    }
    if (max != i) {
        exchg(A[i], A[max]);
        Heapify(A, max, n);
    }
}

void BuildHeap(int A[], int n)
{
    int i = 0;
    for (i = n/2; i >= 1; i--) {
        Heapify(A, i, n);
    }
}

void Heapsort(int A[], int n)
{
    BuildHeap(A, n);
    int i;
    for (i = n; i >= 1; i--) {
        exchg(A[1], A[i]);
        n--;
        Heapify(A, 1, n);
    }
}

// BST sort
typedef struct tree {
    struct tree *left, *right;
    int x;
} tree;
static int BST_sort_idx = 0;
tree *BST_insert(tree *root, int val)
{
    tree *t = root;
    if (t == NULL) {
        t = (tree *) malloc(sizeof(tree));
        t->left = t->right = NULL;
        t->x = val;
        return t;
    } else if (val < t->x) {
        t->left = BST_insert(t->left, val);
    } else if (val > t->x) {
        t->right = BST_insert(t->right, val);
    }
    return t;
}
void BST_inorder(tree *root, int a[])
{
    static int idx = 0;
    if (root) {
        BST_inorder(root->left, a);
        a[BST_sort_idx++] = root->x;
        BST_inorder(root->right, a);
    }
}
void BST_sort(int a[], int n)
{
    int i;
    tree *root = NULL;
    for (i = 0; i < n; i++) {
        root = BST_insert(root, a[i]);
    }
    BST_sort_idx = 0;
    BST_inorder(root, a);
}

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
    //show_array(a, n);
    //merge_sort(a, 0, n-1);
    //show_array(a, n);
    //heap_sort(a, n);
    show_array(&a[1], n-1);
    Heapsort(a, n-1);
    show_array(&a[1], n-1);
    //BST_sort(a, n);

}

