#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstring>

using std::cout;
using std::endl;
using std::string;
using std::reverse;

int atoi_cpp(string& s) {
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

string itoa_cpp(int i) {
    string s, r, minus = "-";
    int x = 0, sign = 1;
    if (i < 0) sign = -1;
    i *= sign;
    while (i) {
        x = i % 10;
        i /= 10;
        s.push_back('0' + x);
    }
    copy(s.rbegin(), s.rend(), back_inserter(r));
    if (sign < 0) r.insert(0, minus);
    return r;
}

int myatoi_c(char *s) {
    int len = strlen(s);
    int i = 0, n = 0, sign;
    //printf("atoi(%s)\n", s);
    //for (i = 0; i < len; i++) printf("s[%d] = %c\n", i, s[i]);
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') i++; // skip sign
    for (; isdigit(s[i]); ++i) n = 10 * n + (s[i] - '0');
    return sign * n;
}

void reverse_c(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void myitoa_c(int i, char s[]) {
    int x = 0, sign = 1, len, j = 0;
    if (i < 0) sign = -1;
    i *= sign;
    while (i) {
        x = i % 10;
        i /= 10;
        s[j++] = '0' + x;
    }
    if (sign < 0) {
        s[j++] = '-';
    }
    reverse_c(s);
}

void test_cpp()
{
    string s = "-231";
    int i;
    i = atoi_cpp(s);
    cout << "atoi(" << s << ") = " << i << endl;
    i = -1976;
    s = itoa_cpp(i);
    cout << "itoa(" << i << ") = " << s << endl;
}

void test_c()
{
    char s[] = "-231";
    char p[12];
    int i;
    i = myatoi_c(s);
    printf("atoi(%s) = %d\n", s, i);
    i = -1976;
    myitoa_c(i, p);
    printf("itoa(%d) = %s\n", i, p);
}

int main()
{
    test_cpp();
    test_c();
    return 0;
}
