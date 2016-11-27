#include <iostream>
#include <vector>

using namespace std;

template <typename T>
int compare(const T &v1, const T &v2)
{
    //if (v1 < v2) return -1;
    //if (v2 < v1) return 1;
    // more generic, allows use on classes
    // that may not support <
    // goal: reduce the requirements on classes using this function
    if (less<T>()(v1, v2)) return -1;
    if (less<T>()(v2, v1)) return 1;
    return 0;
}

// nontype parameters
template <unsigned N, unsigned M>
int compare2(const char (&p1)[N], const char (&p2)[M])
{
    cout << "compare nontype version" << endl;
    return strcmp(p1, p2);
}


template <typename T>
T foo(T* p)
{
    T tmp = *p;
    return tmp;
}

int main()
{
    cout << compare(1,0) << endl;
    string a = "douche", b = "bag";
    cout << compare(b,b) << endl;

    vector<int> v1{1,2,3};
    vector<int> v2{4,5,6};

    cout << compare(v1, v2) << endl;
    cout << compare(v2, v1) << endl;

    cout << compare(1, 0) << endl;
    cout << compare(0, 1) << endl;
    cout << compare(1, 1) << endl;

    int rc = 42;
    rc = foo(&rc);
    cout << rc << endl;

    const char a2[4] = "bag";
    const char b2[4] = "dog";
    cout << compare2(a2, b2) << endl;
}
