#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * Convert Base: Write a function that performs base conversion.  Specifically, the input
 * is an integer base b1, a string s, representing an integer in base b1, and another integer
 * base b2; the output is the string representing the integer x in base b2.  Assume 2 <= b1,
 * b2 <= 16. Use "A" to represent 10, "B" for 11,..., and "F" for 15.
 *
 */

int power(int x, int y);
char *convert_base(int b1, char *s, int b2)
/* b1 : base of integer s (string)
 * s  : integer string
 * b2 : base to conver s to.
 */
{
    char *conversion = NULL;
    int counter, y, val, rem;
    counter = y = 0;
    val = 123;
    while (val) {
        rem = val % b1;
        y += power(b1, counter) * rem;
        counter++;
        val /= b1;
    }
    printf("123 => %d\n", y);
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
            //printf("no %c is not alpha => %d\n", s[i], n);
        }
    }
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

int main()
{
    int x, b1, b2;
    char num[32];
    b1 = 8, b2 = 16;
    //convert_base(b1, "123", b2);
    //x = myatoi_base(b1, "123", b2);
    //printf("%s - base %d = %d - base %d\n", "123", b1, x, b2);
    //memset(num, '\0', 32);
    //x = 0xdead;
    x = 23;
    myitoa(x, num, 8);
    printf("itoa(%x) = %s\n", x, num);
    return 0;
}
