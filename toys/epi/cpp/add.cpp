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

int power(int x, int power)
{
    int i;
    if (power == 0) return 1;
    for (i = 0; i < power-1; ++i) {
        x *= 10;
    }
    return x;
}

int column(int x)
{
    int col = 0;
    while (x) {
        x /= 10;
        col++;
    }
    return col-1;
}

string mult(string a, string b)
{
    int icol, jcol, col;
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    string c = "boom";
    int carry = 0;
    for (int i = 0; i < a.length(); ++i) {
        for (int j = 0; j < b.length(); ++j) {
            icol = power(10, i);
            jcol = power(10, j);
            col = icol * jcol;
            int cc = column(col);
            cout << i << " * " << j << " col " << col << " cc " << cc << endl;
            //cout << a[i] << " * " << b[j] << " = " << endl;
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
            //cout << m << " * " << n  << " = " << p << endl;
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
    string c;

    //c  = add(a, b);
    //cout << a << " + " << b << " = " << c << endl;

    c  = mult(a, b);
    cout << a << " * " << b << " = " << c << endl;

}

