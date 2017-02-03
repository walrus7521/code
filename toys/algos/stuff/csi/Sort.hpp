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

#endif // _Sort_h_
