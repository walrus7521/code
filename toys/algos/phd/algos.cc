#include <stdio.h>
#include <stdlib.h>

#define exchg(A, B) { int t = A; A = B; B = t; }

// todo - recursive:
// [x] 4.1 write sum(a,n) recursively
// [x] 4.2 count items in list -> count(a,n)
// [x] 4.3 find max in list -> max(a,n)
// [ ] 4.4 binsearch recursively

// binary search
// selection sort
// divide and conquer: gcd


void show(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++) {
        printf("%d, ", a[i]);
    }
    printf("\n");
}

int sum(int a[], int p, int n)
{
    show(&a[p],n);
    //if (n == 0) return 0; // skip the zero case
    if (n == 1) return a[p];
    return a[p] + sum(a,p+1,n-1);
    
// iterative
//    int i, s = 0;
//    for (i = 0; i < n; i++) {
//        show(&a[i],n-i);
//        s += a[i];
//    }
//    return s;
}

typedef struct _list {
    struct _list *next;
    int v;
} list;

list *alloc(int v)
{
    list *l = (list *) malloc(sizeof(list));
    l->v = v;
    l->next = NULL;
    return l;
}

void insert(list *head, int v)
{
    list *n = alloc(v);
    list *tmp = head->next;
    head->next = n;
    n->next = tmp;
}

void showl(list *head)
{
    printf("show list\n");
    list *p = head->next;
    while (p) {
        printf("v:%d\n", p->v);
        p = p->next;
    }
}

int count(list *head)
{
    if (head->next == NULL) return 0;
    return 1 + count(head->next);
}

void max(list *head, int *m)
{
    if (head->next == NULL) return;
    if (*m < head->next->v) {
        *m = head->next->v;
    }
    max(head->next, m);
}

#if 0
    Algorithm: Quicksort(A[l..r])
    Input: Sub array A[0..n-1] defined by left (l) and right (r)
    Ouput: Sorted sub array A[l..r]
    1. if l < r // so long as here are elements in the array
    2.     s <- Partition(A[l..r]) // place pivot at right place
    3.     Quicksort(A[l..s-1])    // left part
    4.     Quicksort(A[s+1,..r])   // right part

    Algorithm: Hoare Partition(A[l..r])
    Input: sub array of A[0..n-1] defined by l and r indices
    Output: Partition of A[L..R] with the split position
    1.  p <- A[L] // pivot is first element
    2.  i <- L; j <- R+1
    3.  repeat
    4.      repeat i <- i + 1 until A[i] >= p // left to right
    5.      repeat j <- j - 1 until A[j] <= p // right to left
    6.      swap(A[i], A[j])
    7.  until i >= j
    8.  swap(A[i], A[j]) // undo last iteration
    9.  swap(A[L], A[j]) // A[L] refers to pivot value
    10. return j // returns the split position (L <-- j --> R) sorted

def quicksort(arr):
    if (len(arr) < 2):
        return arr
    else:
        pivot = arr[0]
        less = [i for i in arr[1:] if i <= pivot]
        grtr = [i for i in arr[1:] if i > pivot]
        return quicksort(less) + [pivot] + quicksort(grtr)
    return arr
#endif

int partition(int a[], int p, int r)
{
    int x=a[p],i=p-1,j=r+1;
    while (1) {
        do  j--; while (a[j] > x);
        do  i++; while (a[i] < x);
        if  (i < j) {
            exchg(a[i],a[j]);
        } else {
            return j;
        }
    }
}

void quicksort(int a[], int l, int r)
{
    int s;
    if (r <= l) return;
    s = partition(a,l,r);
    quicksort(a,l,s);
    quicksort(a,s+1,r);
}

void selection(int a[], int n)
{
    int i, j, min;
    for (i = 0; i < n; i++) {
        min = i;
        for (j = i+1; j < n; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }
        exchg(a[i], a[min]);
    }
}

int gcd(int m, int n)
{
    if (m < n) exchg(m,n); //assert(m > n);
    printf("m:%4d, n:%4d, mod:%4d\n", m,n,m%n);
    return (m%n == 0) ? n : gcd(n, m%n);
}

int main()
{
    int g = gcd(1680, 640);
    printf("gcd: %d\n", g);

    int a[] = {4,1,8,3,42,2};
    int n = sizeof(a)/sizeof(a[0]);
    show(a,n);
    //selection(a,n);
    quicksort(a,0, n-1);
    show(a,n);

    return 0;

    printf("sum: %d\n", sum(a,0,n));

    list head;
    insert(&head, 4);
    insert(&head, 42);
    insert(&head, 3);
    insert(&head, 5);
    insert(&head, 6);
    showl(&head);
    int c = count(&head);
    printf("list count: %d\n", c);

    int m = 0;
    max(&head, &m);
    printf("list max: %d\n", m);

}
