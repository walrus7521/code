#include "pch.hpp"
#include "Search.hpp"

using namespace std;


void test_sort()
{
    int a[] = {9, 4, 7, 3, 6, 2, 1};
    int len = sizeof(a)/sizeof(a[0]);
    int find = 7;

    Search_show(a, len);
    cout << "found (" << find << ") at: " << Search_sequential<int>(a, 0, len, find) << endl;

}

int main()
{
    test_sort();
}

