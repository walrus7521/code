#include "pch.hpp"
#include "Sort.hpp"

using namespace std;


void test_sort()
{
    int a[] = {9, 4, 7, 3, 6, 2, 1};
    int len = sizeof(a)/sizeof(a[0]);

    cout << "before" << endl;
    Sort_show<int>(a, len);
    Sort_selection<int>(a, len);
    cout << "after" << endl;
    Sort_show<int>(a, len);

}

int main()
{
    test_sort();
}

