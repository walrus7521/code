#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

int atoi(string a)
{
    int sign = 1, result = 0, end = 0, mult = 1;
    if (a[0] == '-') {
        sign = -1;
        end++;
    }
    for (int i = a.size()-1; i >= end; --i) {
        result += (a[i]-'0') * mult;
        mult *= 10;
    }
    result *= sign;
    return result;
}

string itoa(int i)
{
    string result;
    int sign = 1;
    if (i < 0) sign = -1;
    i *= sign;
    while (i) {
        result += ('0'+(i%10));
        i /= 10;
    }
    if (sign == -1) result += "-";
    reverse(result.begin(), result.end());
    return result;
}

int main()
{
    cout << atoi("-123") << endl;
    cout << itoa(-456) << endl;
}
