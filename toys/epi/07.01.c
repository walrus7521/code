#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int myatoi(char *s) {
    int len = strlen(s);
    int i = 0, n = 0, sign;
    //printf("atoi(%s)\n", s);
    //for (i = 0; i < len; i++) printf("s[%d] = %c\n", i, s[i]);
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') i++; // skip sign
    for (; isdigit(s[i]); ++i) n = 10 * n + (s[i] - '0');
    return sign * n;
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

void myitoa(int i, char s[]) {
    int x = 0, sign = 1, len, j = 0;
    if (i < 0) sign = -1;
    i *= sign;
    while (i) {
        x = i % 10;
        i /= 10;
        s[j++] = '0' + x;
    }
    if (sign < 0) {
        s[j++] = '-';
    }
    reverse(s);
}


int main()
{
    char s[] = "-231";
    char p[12];
    int i;
    i = myatoi(s);
    printf("atoi(%s) = %d\n", s, i);
    i = -1976;
    myitoa(i, p);
    printf("itoa(%d) = %s\n", i, p);
    return 0;
}
