#include <stdio.h>
#include <string.h>

int is_palindrome(char *s) {
    char *p1, *p2;
    int is_pal = 1, len = strlen(s);
    p1 = s;
    p2 = s+len-1;
    len /= 2;
    while (len--) {
        if (*p1++ != *p2--) {
            is_pal = 0;
            break;
        }
    }
    return is_pal;
}

int main()
{
    char s[] = "aabcbaa";
    printf("'%s' %s a palindrom\n", s, (is_palindrome(s)? "is" : "is not"));
}
