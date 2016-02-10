#include <iostream>

using namespace std;

/* 5.11 Check if a decimal integer is a palindrome
 *
 * A palindromic string is one which reads the same forwards and backwards, e.g.,
 * "redivider".  In this problem, you are to write a function which determines
 * if the decimal representation of an integer is a palindromic string.  For example,
 * your function should return true on the inputs 0, 1, 7, 11,121,333, and 2147447412, and
 * false on inputs -1,12,100, and 2147483647.
 *
 * Write a function that takes an integer and determines if that integer's 
 * representation as a decimal string is a palindrome.
 *
 */

int is_palindromic(unsigned int n)
{
    unsigned int x = 0, save_n = n;
    while (n) {
        x = 10*x + n%10;
        n/=10;
    }
    return (x == save_n) ? 1 : 0;
}

int main()
{
    unsigned int n = 217;
    int x = is_palindromic(n);
    cout << n << " is_pal ?= " << x << endl;
}

