#include <iostream>
#include <string>

using namespace std;

void test()
{
    string a = "125";
    string b = "456";
    int carry = 0;
    for (int i = a.length()-1; i >= 0; --i) {
        cout << a[i] << " + " << b[i] << " = " << endl;
        int m = a[i] - '0';
        int n = b[i] - '0';
        int p = m + n + carry;
        carry = (p > 9) ? 1 : 0;
        // ok now convert back to string.
        cout << m << " + " << n << " + " << carry << " = " << p << endl;
    }
}

int main()
{
    test();
}

