#ifndef _String_h_
#define _String_h_

#include "pch.hpp"

using namespace std;

bool is_Palindrome(string str)
{
    const char *p = str.c_str();
    int len = str.length();
    const char *t = p + len - 1;
    while (len/2) {
        if (*p++ != *t--) {
            return false;
        }
        --len;
    }
    return true;
}

bool is_Anagram(string s1, string s2)
{
    int ascii[256] = {0};
    const char *p1 = s1.c_str();
    const char *p2 = s2.c_str();
    int len1 = s1.length();
    int len2 = s2.length();
    if (len1 != len2) return false;
    for (int i = 0; i < len1; ++i) {
        ascii[p1[i]]++;
    }
    for (int i = 0; i < len1; ++i) {
        if (ascii[p2[i]]-- == 0) return false;
    }
    for (int i = 0; i < 256; ++i) {
        if (ascii[i] != 0) return false;
    }

    return true;

}

#endif // _String_h_"
