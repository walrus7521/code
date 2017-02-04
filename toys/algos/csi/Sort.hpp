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

template <typename T>
void merge(T b[], int p, T c[], int q, T a[], int r)
{
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

template <typename T>
void copy(T *a, int sp, int plen, T *b, int sq, int qlen)
{
    if (plen == qlen) {
        for (int i = sp, j = sq; i < plen; ++i, ++j) {
            a[i] = b[j];
        }
    }
}

template <typename T>
void Sort_mergesort(T a[], int n)
{
    T *b = new T[n];
    T *c = new T[n];
    // 1. if n > 1
    if (n > 1) {
    // 2.     copy a[0..n/2-1] to b[0..n/2-1]
        copy(b, 0, n/2-1, a, 0, n/2-1);
    // 3.     copy a[n/2..n-1] to c[0..n/2-1]
    // 4.     mergesort(b[0..n/2-1])
    // 5.     mergesort(c[0..n/2-1])
    // 6.     merge(b, c, a)
    }
}

#endif // _Sort_h_
