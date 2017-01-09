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
void Sort_show(T a[], int size)
{
    for (int i = 0; i < size; ++i) {
        cout << a[i] << endl;
    }

}

template <typename T>
void Sort_selection(T a[], int size)
{
    // start at 0 -> n-1, successively finding smallest value and swap
    T min;
    // scan through the entire list minus one
    for (int i = 0; i < size-1; ++i) {
        min = i;
        // scan sublist for smallest element
        for (int j = i+1; j < size; ++j) {
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


#endif // _Sort_h_
