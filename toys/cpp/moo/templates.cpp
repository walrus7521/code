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

#include "Blob.h"

void test_blob()
{
    Blob<string> b1;
    {
        Blob<string> b2 = {"a", "an", "the"};
        b1 = b2;
        b2.push_back("about");
        cout << b2.front() << endl;
        b2++;
        cout << b2 << endl;
    }

    StrBlob sb1 = {"bass", "guitar", "fiddle", "piano"};
    for (auto &s : sb1) {
        cout << s << endl;
    }

    IntBlob ib1 = {2,5,3,2,2,5,9,6,3,0};
    for (auto &i : ib1) {
        cout << i << endl;
    }

    clump<int> ib2 = {2,1,3,4,5,6,8,5,1,9};
    for (auto &i : ib2) {
        cout << i << endl;
    }

    twin<int> win;
    partNo<string> books;

}
// static members of template classes
template <typename T> 
class Foo {
public:
    static size_t count() { return ctr; }
private:
    static size_t ctr;
};

template <typename T> 
size_t Foo<T>::ctr = 0;

template <typename elemType> class ListItem;
template <typename elemType> class List {
public:
private:
    ListItem<elemType> *front, *end;
};

int main()
{
#if 0
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
#endif

    test_blob();

    Foo<int> fi;
    auto ct = Foo<int>::count();
    cout << "ct: " << ct << endl;
    ct = fi.count();
    cout << "ct: " << ct << endl;
}
