#include <iostream>
#include <array>

using namespace std;

void f(int *p, int sz) {
    int i;
    for (i = 0; i < sz; i++) {
        cout << "a[" << i << "]=" << p[i] << endl;
    }
}

void test_array() {
    array<int,3> a = {1,2,3}; // stack allocated
    f(&a[0],3);
    f(a.data(), a.size());
}

int main()
{
    test_array();
}
