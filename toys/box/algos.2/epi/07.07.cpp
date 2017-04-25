#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int convert(char r)
{
    int num;
    switch (r) {
        case 'I': num = 1; break;
        case 'V': num = 5; break;
        case 'X': num = 10; break;
        case 'L': num = 50; break;
        case 'C': num = 100; break;
        case 'D': num = 500; break;
        case 'M': num = 1000; break;
    }
    return num;
}

int roman(string r)
{
    int first = 1;
    int accum = 0;
    int num;
    for (int i = r.size()-1; i >= 0; --i) {
        char c = r.c_str()[i];
        num = convert(c);
        if (first) {
            first = 0;
            accum += num;
        } else {
            char d = r.c_str()[i+1];
            int num_prev = convert(d);
            if (num_prev > num) {
                accum -= num;
            } else {
                accum += num;
            }
        }
        printf("r[%d]: %c\n", i, r.c_str()[i]);
    }
    return accum;
}

int RomanToInteger(string s) {
    unordered_map<char, int> T = { { 'I', 1    },
                                   { 'V', 5    },
                                   { 'X', 10   },
                                   { 'L', 50   },
                                   { 'C', 100  },
                                   { 'D', 500  },
                                   { 'M', 1000 } };
    int sum = T[s.back()];
    for (int i = s.length() - 2; i >=0; --i) {
        if (T[s[i]] < T[s[i+1]]) {
            sum -= T[s[i]];
        } else {
            sum += T[s[i]];
        }
    }
    return sum;
}

int main()
{
    string r = "IC"; // "XLVII";
    cout << "roman1: " << r << " = " << roman(r) << endl;
    cout << "roman2: " << r << " = " << RomanToInteger(r) << endl;
}

