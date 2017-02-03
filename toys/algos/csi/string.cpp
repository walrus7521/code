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

    string txt("Have a good day!");
    string patt("day!");
    int idx = is_Match(txt, patt);
    if (idx > 0) {
        cout << "is match: " << idx << endl;
    } else {
        cout << "not a match" << endl;
    }


}
