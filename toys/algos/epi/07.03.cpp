#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool is_palindrome(char *s) {
    int len = strlen(s);
    char *p = s+(len-1);
    len /= 2;
    while (len) {
        if (*p-- != *s++) return false;
        len--;
    }
    return true;
}

int main()
{
    char str[] = "abcba";
    cout << "is pal: " << is_palindrome(str) << endl;
}

