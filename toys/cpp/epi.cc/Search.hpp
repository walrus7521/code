#ifndef _Search_h_
#define _Search_h_

#include "pch.hpp"

using namespace std;

template <typename T>
void Search_show(T a[], int size)
{
    for (int i = 0; i < size; ++i) {
        cout << a[i] << endl;
    }

}

template <typename T>
T Search_sequential(T a[], int first, int last, T val)
{
    int match = -1;
    for (int i = first; i < last; ++i) {
        if (a[i] == val) {
            match = i;
        }
    }
    return match;
}


#endif // _Search_h_
