#ifndef _String_h_
#define _String_h_

#include "pch.hpp"

bool is_Palindrome(std::string str)
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

#endif // _String_h_"
