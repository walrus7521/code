#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

void test()
{
    string a = "125";
    string b = "456";
    string c;
    int carry = 0;
    for (int i = a.length()-1; i >= 0; --i) {
        //cout << a[i] << " + " << b[i] << " = " << endl;
        int m = a[i] - '0';
        int n = b[i] - '0';
        int s = m + n + carry;
        carry = (s > 9) ? 1 : 0;
        s %= 10;
        // ok now convert back to string.
        ostringstream convert;
        convert << s;
        c += convert.str();
        //cout << m << " + " << n << " + " << carry << " = " << s << endl;
    }
    std::reverse(c.begin(), c.end());
    cout << a << " + " << b << " = " << c << endl;
}

int main()
{
    test();
}

