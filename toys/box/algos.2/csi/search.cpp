#include "pch.hpp"
#include "Search.hpp"

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

