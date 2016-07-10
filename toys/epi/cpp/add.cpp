#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

string add(string a, string b)
{
    //string a = "125";
    //string b = "456";
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
    //cout << a << " + " << b << " = " << c << endl;
    return c;
}

string mult(string a, string b)
{
    //string a = "125";
    //string b = "456";
    string c = "boom";
    int carry = 0;
    for (int i = a.length()-1; i >= 0; --i) {
        for (int j = b.length()-1; j >= 0; --j) {
           cout << a[i] << " * " << b[j] << " = " << endl;
            int m = a[i] - '0';
            int n = b[j] - '0';
            int p = m * n;
            //int s = m + n + carry;
            //carry = (s > 9) ? 1 : 0;
            //s %= 10;
            // ok now convert back to string.
            //ostringstream convert;
            //convert << s;
            //c += convert.str();
            cout << m << " * " << n  << " = " << p << endl;
        }
    }
    //std::reverse(c.begin(), c.end());
    //cout << a << " + " << b << " = " << c << endl;
    return c;
}

int main()
{
    string a = "123";
    string b = "456";
    string c  = add(a, b);
    cout << a << " + " << b << " = " << c << endl;
    //mult();

    c  = mult(a, b);
    cout << a << " * " << b << " = " << c << endl;

}

