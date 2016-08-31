#include <iostream>
#include <cstdio>
#include <string>

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
    string s = "hello";
    return s;
}

int main()
{
    cout << atoi("-123") << endl;
}
