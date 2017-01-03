#include "pch.hpp"
#include "String.hpp"

using namespace std;

int main()
{
    string s("ahha");
    if (is_Palindrome(s)) {
        cout << "is pal" << endl;
    } else {
        cout << "not a pal" << endl;
    }
}
