#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::reverse;

int atoi(string& s) {
    int len = s.size();
    int i = 0, n = 0, sign;
    cout << "atoi(" << s << ")\n";
    for (i = 0; i < len; i++) cout << "s[" << i << "] = " << s[i] << endl;
    i = 0;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') i++; // skip sign
    for (; isdigit(s[i]); ++i) n = 10 * n + (s[i] - '0');
    return sign * n;
}

string itoa(int i) {
    string s, r;
    int x = 0, sign = 1;
    if (i < 0) sign = -1;
    i *= sign;
    while (i) {
        x = i % 10;
        i /= 10;
        s.push_back('0' + x);
    }
    copy(s.rbegin(), s.rend(), back_inserter(r));
    if (sign < 0) r.insert(0, '-');
    return r;
}


int main()
{
    string s = "-231";
    int i;
    i = atoi(s);
    cout << "atoi(" << s << ") = " << i << endl;
    i = -1976;
    s = itoa(i);
    cout << "itoa(" << i << ") = " << s << endl;
    return 0;
}
