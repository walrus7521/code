#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string>
#include <iostream>

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
char *convert_base(int b1, int s, int b2)
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

void dec2hex(int b1, int n, int b2)
{
    int x=0, count=0, p;
    printf("dec2hex=%d\n", n);
    while (n) {
        p = power(b2, count);
        x += (n%b2)*p;
        //printf("p=%d, x=%x\n", p, x);
        n/=b2;
        count++;
    }
    printf("x=%x\n", x);
}

void bin2dec(int b1, int n, int b2)
{
   int x=0, count=0, p;
   printf("bin2dec=%x\n", n);
   while (n) {
       p = power(b1, count);
       x += (n%b1)*p;
       n /= b1;
       //printf("p=%d, x=%x, n=%x\n", p, x, n);
       count++;
   }
   printf("x=%d\n", x);
}

/* yay this is working, build on this */
void scan(int b1, string &s)
{
    int p, i, len = s.length(), n = 0, count = 0;
    for (i=len-1; ishexdigit(s[i]); --i) {
        //cout << s[i] << endl;
        p = power(b1, count);
        n += (s[i] - '0') * p;
        count++;
    }
    printf("n = %s, len=%d, n=%d\n", s.c_str(), len, n);

}

int main()
{
    int x, b1, b2;
    char num[] = "194";
    std::string s = "194";
    scan(16, s);
    return 0;
    int n = 0x5a;
    b1 = 16, b2 = 10;
    //x = myatoi_base(b1, num, b2);
    //printf("%s - base %d = %d - base %d\n", num, b1, x, b2);
    //convert_base(b1, n, b2);
    n = 1101;
    dec2hex(10, 1101, 16);
    n = 0b1101010;
    bin2dec(2, n, 16);
    return 0;
}
