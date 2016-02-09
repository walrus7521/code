#include <iostream>
#include <cmath>

using namespace std;

/* The problem is concerned with computing the reverse of the decimal represantation
 * of a binary-encoded integer.  For example, the reverse of 42 is 24, and the reverse
 * of -314 is -413.
 *
 * Write a function which takes an inteter K and returns the integer corresponding
 * to the digits of K written in reverse order.
 */

int reverse(int k)
{
    int x = 0;
    while (k) {
        cout << "k mod 10 " << k % 10 << endl;
        x = x * 10 + k % 10; // at each pass the modulo is shifted up by 10
        k /= 10; // while k is diminished by a factor of 10
    }
    return x;
}

int main()
{
    int x = 142, y;
    y = reverse(x);
    cout << "the reverse of " << x << " is " << y << endl;
}
