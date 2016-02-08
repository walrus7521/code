#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

/* to do: need to do negative numbers */
/* Convert Base: Write a function that performs base conversion.  Specifically, the input
 * is an integer base b1, a string s, representing an integer in base b1, and another integer
 * base b2; the output is the string representing the integer x in base b2.  Assume 2 <= b1,
 * b2 <= 16. Use "A" to represent 10, "B" for 11,..., and "F" for 15.
 */

int ishexdigit(char c) {
    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')) return 1;
    return 0;
}

int power(int x, int y)
{
    int pow, i;
    if (x == 0) return 0.0;
    if (y == 0) return 1.0;
    if (y < 0) y = -y, x = 1.0 / x;
    for (i = 0, pow = x; i < y-1; i++) pow *= x;
    return pow;
}

string *convert_base(int b1, string &s, int b2)
{
    int p, i, len = s.length(), n, count;
    count = n = 0;
    /* first convert from arbitrary base b1 to base 10 */
    for (i=len-1; ishexdigit(s[i]); --i) {
        p = power(b1, count);
        n += (s[i] - '0') * p;
        count++;
    }
    printf("%s base %d is equal to %d decimal\n", s.c_str(), b1, n);
    /* now convert from decimal to an arbitrary base b2 */
    count = 0;
    int x, v, save_n = n;
    char c;
    string *out = new string();
    while (n) {
        p = power(b2, count);
        v = (n%b2);
        if (v >= 0 && v <= 9) c = '0'+v;
        else if (v >= 10 && v <= 15) c = 'a' + (v - 10);
        out->push_back(c);
        x += v*p;
        n/=b2;
        count++;
    }
    reverse(out->begin(), out->end());
    //out->insert (0, 1, '-');
    printf("%d base 10 is equal to %s base %d\n", save_n, out->c_str(), b2);
    return out; 
}

int main()
{
    int x, b1, b2;
    std::string s = "110";
    string *s2 = convert_base(8, s, 2);
    cout << "base: " << *s2 << endl;
    return 0;
}
