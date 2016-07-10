#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

/*
 * Convert Base: Write a function that performs base conversion.  Specifically, the input
 * is an integer base b1, a string s, representing an integer in base b1, and another integer
 * base b2; the output is the string representing the integer x in base b2.  Assume 2 <= b1,
 * b2 <= 16. Use "A" to represent 10, "B" for 11,..., and "F" for 15.
 *
 *
 */

char tohex(int n)
{
    if (n <10) return '0'+n;
    else return 'a'+(n-10);

}

#define MAX_STR_LEN 16
void reverse(char s[]);
int power(int x, int y);
char *convert_base_2(int b1, int s, int b2)
/* b1 : base of integer s (string)
 * s  : integer string
 * b2 : base to conver s to.
 */
{
    char *conversion = (char *) malloc(MAX_STR_LEN);
    int counter, val, rem, save_val, pow, n = 0;
    counter = 0;
    save_val = val = s;
    memset(conversion, 0, MAX_STR_LEN);
    while (val) {
        rem = val % b2;
        pow = power(b1, counter);
        // convert y = base in string
        conversion[counter] = tohex(rem);
        val /= b2;
        n += b2 * n + val;
        printf("[%d] val %d, rem %d, pow %d, n %d\n", counter, val, rem, pow, n);
        counter++;
    }
    reverse(conversion);
    printf("%x => %s\n", save_val, conversion);
    return conversion;
}

int ishexdigit(char c) {
    //printf("ishexdigit : %c => ", c);
    if ((c >= '0' && c <= '9') ||
        (c >= 'A' && c <= 'F') ||
        (c >= 'a' && c <= 'f')) {
        //printf("yes\n");
        return 1;
    }
    //printf("no\n");
    return 0;
}

void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void myitoa(int i, char s[], int base) {
    int x = 0, sign = 1, j = 0;
    if (i < 0) sign = -1;
    i *= sign;
    x = i % base;
    while (i) {
        x = i % base;
        i /= base;
        if (x >= 0 && x <= 9) {
            s[j] = '0' + x;
        } else {
            s[j] = 'a' + x - 10;
        }
        j++;
    }
    if (sign < 0) {
        s[j++] = '-';
    }
    reverse(s);
}

int myatoi_base(int b1, char *s, int b2) {
    int len = strlen(s);
    int i = 0, n = 0, sign;
    //printf("atoi(%s)\n", s);
    //for (i = 0; i < len; i++) printf("s[%d] = %c\n", i, s[i]);
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') i++; // skip sign
    for (; ishexdigit(s[i]); ++i) {
        if (isalpha(s[i])) {
            if (s[i] >= 'A' && s[i] <= 'F') {
                //n = b1 * n + (s[i] - 'A' + 10);
                n = b1 * n + (s[i] - 'A' + b2);
            } else {
                //n = b1 * n + (s[i] - 'a' + 10);
                n = b1 * n + (s[i] - 'a' + b2);
            }
            //printf("yes %c is alpha => %d\n", s[i], n);
        } else {
            n = b1 * n + (s[i] - '0');
            printf("no %c is not alpha => %d\n", s[i], n);
        }
    }
    printf("return: %d\n", n);
    return sign * n;
}

int power(int x, int y)
{
    int pow;
    int i;
    if (x == 0) return 0.0;
    if (y == 0) return 1.0;
    if (y < 0) {
        y = -y, x = 1.0 / x;
    }
    for (i = 0, pow = x; i < y-1; i++) {
        pow *= x;
    }
    return pow;
}

/* Ok, convert_base converts from any base to base 10, we now need a function
 * that converts from base 10 to any other base.
 */

/* yay this is working, build on this
 * this basically converts string s to decimal
 * from base b1
 */
string *convert_base(int b1, string &s, int b2)
{
    int p, i, len = s.length(), n, count;
    count = n = 0;
    for (i=len-1; ishexdigit(s[i]); --i) {
        //cout << s[i] << endl;
        p = power(b1, count);
        n += (s[i] - '0') * p;
        count++;
    }
    printf("%s base %d is equal to %d decimal\n", s.c_str(), b1, n);
    count = 0;
    int x, v, save_n = n;
    char c;
    string *out = new string();
    while (n) {
        p = power(b2, count);
        v = (n%b2);
        if (v >= 0 && v <= 9) c = '0'+v;
        else if (v >= 10 && v <= 15) c = 'a' + (v - 10);
        out->push_back(c);
        x += v*p;
        //printf("p=%d, v=%x\n", p, v);
        n/=b2;
        count++;
    }
    reverse(out->begin(), out->end());
    //out->insert (0, 1, '-');
    printf("%d base 10 is equal to %s base %d\n", save_n, out->c_str(), b2);
    //string *out = dec2B2(n, b2);
    return out; 
}

int main()
{
    int x, b1, b2;
    std::string s = "110";
    string *s2 = convert_base(8, s, 2);
    cout << "base: " << *s2 << endl;
    return 0;
}
