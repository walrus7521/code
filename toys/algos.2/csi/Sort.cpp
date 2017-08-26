#ifndef _Sort_h_
#define _Sort_h_

#include "pch.hpp"

using namespace std;

template <typename T>
void myswap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
void Sort_show_section(T a[], int low, int high)
{
    for (int i = low; i <= high; ++i) {
        cout << a[i] << ", ";
    }
    cout << endl;
}

template <typename T>
void Sort_show(T a[], int n)
{
    for (int i = 0; i < n; ++i) {
        cout << a[i] << ", ";
    }
    cout << endl;
}

template <typename T>
void Sort_selection(T a[], int n)
{
    // start at 0 -> n-1, successively finding smallest value and swap
    T min;
    // scan through the entire list minus one
    for (int i = 0; i < n-1; ++i) {
        min = i;
        // scan sublist for smallest element
        for (int j = i+1; j < n; ++j) {
            if (a[min] > a[j]) {
                min = j;
            }
        }
        // exchange smallest with current i
        if (i != min) {
            myswap(a[i], a[min]);
        }
    }
}

template <typename T>
void Sort_bubble(T a[], int n)
{
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-1-i; ++j) {
            if (a[j+1] < a[j]) {
                myswap(a[j], a[j+1]);
            }
        }
    }
}

// decrease and conquer by constant: 1
// list is divided into 2 parts, left & right
// left is sorted, right is unsorted
// move right, adding new element from right into left
void insertion(int a[], int n)
{
    int i, j;
    // note: i=0 element is already sorted
    for (i = 1; i < n; i++) {
        int v = a[i]; // first element in right array
                      //save this because it might get shifted
        j = i-1; // last element in left sorted array
        while (j >= 0 && a[j] > v) {
            a[j+1] = a[j]; // swap left element with right
            j--; // decrease - scanning right to left through
                 // left side of array
        }
        a[j+1] = v; //
    }
}

void merge(int A[], int p, int q, int r)
{
    int m = q-p+1;
    int n = r-q;

    int B[m];
    int C[n];
    int D[n+m];

    int i,j,k;

    // debug array
    for (i = 0; i < n+m; i++) {
        D[i] = 0;
    }

    for (i = 0; i < m; i++) {
        B[i] = A[p+i];
    }
    for (j = 0; j < n; j++) {
        C[j] = A[q+j+1];
    }
    printf("\n");
    printf("merge A p:%d, q:%d, r:%d\n", p, q, r);
    Sort_show_section(A, p, r);
    printf("merge B m:%d\n", m);
    Sort_show_section(B, 0, m-1);
    printf("merge C n:%d\n", n);
    Sort_show_section(C, 0, n-1);

    i = j = 0;
    //printf("start merge m:%d n:%d\n", m, n);
    k = p;
    while (i < m && j < n) {
        if (B[i] <= C[j]) {
            A[k] = B[i];
            D[k] = B[i];
            i++;
        } else {
            A[k] = C[j];
            D[k] = C[j];
            j++;
        }
        k++;
    }
    if (i < m) {
        //cout << " need to copy rest of B to A" << endl;
        while(i < m) {
            A[k] = B[i];
            D[k] = B[i];
            k++; i++;
        }
    } else 
    if (j < n) {
        //cout << " need to copy rest of C to A" << endl;
        while(j < n) {
            A[k] = C[j];
            D[k] = C[j];
            k++; j++;
        }
    }
    printf("done merge D i:%d:m:%d, j:%d:n:%d, k:%d, p:%d, r:%d\n", i, m, j, n, k, p, r);
    Sort_show_section(D, p, r);
    // place half a in b and half in c
    // assert: r = p+q
    // assert: b and c are sorted

    // 1. i <- 0; j <- 0; k <- 0;
    // 2. while i < p and j < q do // while there are elements in b & c
    // 3.     if b[i] <= c[j]
    // 4.         a[k] <- b[i]; i <- i+1
    // 5.      else a[k] <- c[j]; j <- j+1
    // 6.      k <- k+1
    // 7. if i = p // array b is exhausted so copy remainder of c to a
    // 8.     copy c[j..q-1] to a[k..p+q-1]
    // 9. else // array c is exhausted so copy remainder of b to a
    //        copy b[i..p-1] to a[k..p+q-1]
}

void partition(int a[], int low, int high)
{
    int mid;
    // 1. if n > 1
    printf("partition: low:%d, high:%d\n", low, high);
    if (low < high) {
        mid = (low + high) / 2;
    // 2.     copy a[0..n/2-1] to b[0..n/2-1]
    // 3.     copy a[n/2..n-1] to c[0..n/2-1]
    // 4.     mergesort(b[0..n/2-1])
        partition(a, low, mid);
    // 5.     mergesort(c[0..n/2-1])
        partition(a, mid+1, high);
    // 6.     merge(b, c, a)
        merge(a, low, mid, high);
    }

}

void mergesort(int a[], int low, int high)
{
    int i,j,k,m;
    int b[256] = {0};
    if (low < high) {
        m = (high+low)/2;
        mergesort(a, low, m);
        mergesort(a, m+1, high);
        for (i = m+1; i > low; i--) b[i-1] = a[i-1];
        for (j = m; j < high; j++) b[high+m-j] = a[j+1];
        for (k = low; k <= high; k++)
            a[k] = (b[i]<b[j]) ? b[i++] : b[j--];
    }
}

void quicksort(int a[], int L, int R);

template <typename T>
void Sort_mergesort(T a[], int n)
{
    //partition(a, 0, n-1);
    //mergesort(a, 0, n-1);
    quicksort(a, 0, n-1);
}

int hoarepart(int a[], int l, int r) {
    int pivot, i, j, t;
    pivot = a[l];
    i = l; j = r+1;
    while(1) {
        do ++i; while( a[i] <= pivot && i <= r );
        do --j; while( a[j] > pivot );
        if( i >= j ) break;
        myswap(a[i], a[j]);
    }
    myswap(a[l], a[j]);
    return j;
}

void quicksort(int a[], int L, int R)
{
    if (L < R) {
        int S = hoarepart(a, L, R);
        quicksort(a, L, S-1);
        quicksort(a, S+1, R);
    }
}

#endif // _Sort_h_

#include "pch.hpp"

using namespace std;

void test_sort()
{
    //int a[] = {9, 4, 7, 3, 6, 2, 1};
    int a[] = {45,68,89,34,29};
    //int a[] = {5,4,3,2};
    int len = sizeof(a)/sizeof(a[0]);

    cout << "before merge" << endl;
    Sort_show<int>(a, len);
    //Sort_selection<int>(a, len);
    Sort_bubble<int>(a, len);
    //Sort_mergesort<int>(a, len);
    //insertion(a, len);
    cout << "after merge" << endl;
    Sort_show<int>(a, len);

}

int main()
{
    test_sort();
}


