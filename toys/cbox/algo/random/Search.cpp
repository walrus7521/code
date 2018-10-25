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

int binsearch(int a[], int n, int k)
{
    int l = 0, r = n-1;
    while (l <= r) {
        int m = (l+r)/2;
        if (k == a[m]) return m;
        else if (k < a[m]) r = m-1;
        else l = m+1;
    }
    return -1;
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

#include "pch.hpp"

using namespace std;


void test_sort()
{
    //int a[] = {9, 4, 7, 3, 6, 2, 1};
    int a[] = {1,2,3,4,5,6,7,8,9}; // sorted
    int len = sizeof(a)/sizeof(a[0]);
    int find = 7;

    Search_show(a, len);
    //cout << "found (" << find << ") at: " << Search_sequential<int>(a, 1, len, find) << endl;
    cout << "found (" << find << ") at: " << binsearch(a, len, find) << endl;

}

int main()
{
    test_sort();
}


