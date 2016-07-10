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
    int col, overflow, carry;
    ostringstream convert;
    cout << a << " * " << b << endl;
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    // initialize string with a.length() + b.length() zeros.
    string c (a.length() + b.length(), '0');
    overflow = 0;
    for (int i = 0; i < a.length(); ++i) {
        for (int j = 0; j < b.length(); ++j) {
            col = i + j;
            cout << i << " * " << j << " col " << col << endl;
            int m = a[i] - '0';
            int n = b[j] - '0';
            int p = m * n;
            cout << a[i] << " * " << b[j] << " = " << p << endl;
            // need to do a RMW of result string 
            // note: inside these if's need to check for overflow of
            // each individual digit...oh crap
            overflow = (p > 9) ? 1 : 0;
            if (overflow) {
                // grab 2 digits
                int q = c[col] - '0';
                q += p % 10;
                carry = (q > 9) ? 1 : 0;
                if (carry) {
                } else {
                    c[col] = q + '0';
                }
                int r = c[col+1] - '0';
                r += p / 10;
                carry = (r > 9) ? 1 : 0;
                if (carry) {
                } else {
                    c[col+1] = r + '0';
                }
                cout << "ov: " << q << " : " << r << " : " << c << endl;
            } else {
                // grab 1 digit
                int q = c[col] - '0';
                q += p % 10;
                carry = (q > 9) ? 1 : 0;
                if (carry) {
                } else {
                    c[col] = q + '0';
                }
                cout << "nr: " << q << " : " << " : " << c << endl;
            }
            overflow = 0;
        }
    }
    std::reverse(c.begin(), c.end());
    //cout << a << " + " << b << " = " << result << endl;
    return c;
}

int main()
{

    string a = "111";
    string b = "221";
    string c;

    //c  = add(a, b);
    //cout << a << " + " << b << " = " << c << endl;

    c  = mult(a, b);
    string answer = "24531";
    cout << a << " * " << b << " = " << c << endl;
    cout << "answer = " << answer << endl;

}

