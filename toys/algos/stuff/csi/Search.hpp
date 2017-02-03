#ifndef _Search_h_
#define _Search_h_

#include "pch.hpp"

using namespace std;

template <typename T>
void Search_show(T a[], int n)
{
    for (int i = 0; i < n; ++i) {
        cout << a[i] << ", ";
    }
    cout << endl;
}

template <typename T>
T Search_sequential(T a[], int first, int last, T k)
{
    int i = first;
    int n = last - first;
    while (a[i] != k) {
        ++i;
    }
    if (i < n) return i;
    else return -1;
}


#endif // _Search_h_
