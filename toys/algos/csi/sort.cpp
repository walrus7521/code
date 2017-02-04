#include "pch.hpp"
#include "Sort.hpp"

using namespace std;


void test_sort()
{
    //int a[] = {9, 4, 7, 3, 6, 2, 1};
    int a[] = {45,68,89,34,29};
    int len = sizeof(a)/sizeof(a[0]);

    cout << "before merge" << endl;
    Sort_show<int>(a, len);
    //Sort_selection<int>(a, len);
    //Sort_bubble<int>(a, len);
    Sort_mergesort<int>(a, len);
    cout << "after merge" << endl;
    Sort_show<int>(a, len);

}

int main()
{
    test_sort();
}

