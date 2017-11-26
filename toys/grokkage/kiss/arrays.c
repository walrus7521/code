#include "types.h"

/*
    sorting
    search
    ring buffer
    strings
 */

int is_anagram(char *a, char *b)
{
    char dict[256];
    int len = strlen(a);
    if (len != strlen(b)) return 0;
    for (int i = 0; i < len; i++) dict[i] = 0;
    for (int i = 0; i < len; i++) dict[a[i]]++;
    for (int i = 0; i < len; i++) {
        if (dict[b[i]]-- == 0) return 0;
    }
    return 1;
}

int is_palindrome(char *a)
{
    int len = strlen(a);
    for (int i = 0; i < len/2; i++) {
        if (a[i] != a[len-i-1]) return 0;
    }
    return 1;
}

int main()
{
    printf("is_ana: %d\n", is_anagram("dude", "eddu"));
    printf("is_pal: %d\n", is_palindrome("duiud"));
    
}

