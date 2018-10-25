#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

void shift_right(char *s, int n)
{
    int i;
    for (i = n-1; i >= 0; --i) {
        s[i+1] = s[i];
    }
}

void replace(char *s, int n) {
    char *p, *q, *t;
    p = q = t = s;
    while (n > 0) {
        if (*p == 'b') {
            t = p++;
            int len = n;
            while (len > 0) {
                *q++ = *p++;
                --len;
            }
        }
        else
        if (*p == 'a') {
            *p = 'd';
            p++;
            int i;
            for (i = n-1; i >= 0; --i) {
                p[i+1] = p[i];
            }
            *p = 'd';
        }
        p++;
        q = t = p;
        --n;
    }
}

int main()
{
    char s[] = "abcdefgh         ";
    printf("%s\n", s);
    replace(s, 8);
    printf("%s\n", s);
}
