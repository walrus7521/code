#include <iostream>
#include <vector>

using std::cout; using std::endl;
using std::vector;

template <typename T>
int compare(const T &v1, const T &v2)
{
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}

int main()
{
    vector<int> v1{1,2,3};
    vector<int> v2{4,5,6};

    cout << compare(v1, v2) << endl;
    cout << compare(v2, v1) << endl;

    cout << compare(1, 0) << endl;
    cout << compare(0, 1) << endl;
    cout << compare(1, 1) << endl;
}
