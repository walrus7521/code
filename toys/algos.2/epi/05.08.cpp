#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
string ConvertBase(const string& s, int b1, int b2);
/* Convert Base: Write a function that performs base conversion.  Specifically, the input
 * is an integer base b1, a string s, representing an integer in base b1, and another integer
 * base b2; the output is the string representing the integer x in base b2.  Assume 2 <= b1,
 * b2 <= 16. Use "A" to represent 10, "B" for 11,..., and "F" for 15.
 */
int power(int x, int y);
int ishexdigit(char c);
string convert_base(const string& s, int b1, int b2)
{
    int v, save_n, i, len = s.length(), n=0, x=1;
    bool is_negative = s.front() == '-';
    /* first convert from arbitrary base b1 to base 10 */
    for (i=len-1; ishexdigit(s[i]); --i) {
        n += (s[i] - '0') * x;
        x *= b1;
    }
    /* now convert from decimal to an arbitrary base b2 */
    string result;
    while (n) {
        char c;
        v = (n%b2);
        if (v >= 0 && v <= 9) c = '0'+v;
        else if (v >= 10 && v <= 15) c = 'a' + (v - 10);
        result.push_back(c);
        n/=b2;
    }
    if (is_negative) result.push_back('-');
    reverse(result.begin(), result.end());
    return result;
}

int ishexdigit(char c) {
    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')) return 1;
    return 0;
}

int main()
{
    int b1, b2;
    std::string s1 = "615";
    b1 = 7; b2 = 13;
    string s2 = convert_base(s1, b1, b2);
    //string s2 = ConvertBase(s1, b1, b2);
    cout << s1 << " base " << b1 << " equals " << s2 << " base " << b2 << endl;
    return 0;
}

// solution in the book
string ConvertBase(const string& s, int b1, int b2)
{
    bool is_negative = s.front() == '-';
    int x = 0;
    for (size_t i = (is_negative == true ? 1 : 0); i < s.size(); ++i) {
        x *= b1;
        x+= isdigit(s[i]) ? s[i] - '0' : s[i] - 'A' + 10;
    }
    string result;
    do {
        int remainder = x % b2;
        result.push_back(remainder >= 10 ? 'A' + remainder - 10 : '0' + remainder);
        x /= b2;
    } while (x);
    if (is_negative) {
        result.push_back('-');
    }
    reverse(result.begin(), result.end());
    return result;
}

