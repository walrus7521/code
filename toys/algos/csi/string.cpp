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

    string s1("ahha");
    string s2("hahh");
    if (is_Anagram(s1, s2)) {
        cout << "is ana" << endl;
    } else {
        cout << "not an ana" << endl;
    }
}
