#include <stdio.h>
#include <string.h>

int match(char *string, char *pattern)
/*
 * return position of the 1st occurence of pattern p
 * in the string, and -1 if not found.
 */
{
    int i, j;
    int plen, tlen;

    plen = strlen(pattern);
    tlen = strlen(string);

    for (i = 0; i <= (tlen-plen); ++i) {
        j = 0;
        while ((j < plen) && (string[i+j] == pattern[j]))
            ++j;
        if (j == plen) return (i);
    }
    return (-1);
}

int sequential_search(char *str, int len, char k)
{
    int i = 0;
    while (i < len && str[i] != k) i++;
    if (i < len) return i;
    return -1;
}

int palindrome(char *s)
{
    int len = strlen(s);
    int n = len-1;
    int i;
    for (i = 0; i < len/2; i++, n--) {
        if (s[i] != s[n]) {
            return 0;
        }
    }
    return 1;
}

int anagram(char *s1, int len1, char *s2, int len2)
{
    int ascii[256];
    int i;
    if (len1 != len2) {
        return 0;
    }
    for (i = 0; i < 256; i++) ascii[i] = 0;
    for (i = 0; i < len1; i++) ascii[s1[i]]++;
    for (i = 0; i < len1; i++) {
        if (ascii[s2[i]]-- == 0) {
            return 0;
        }
    }
    for (i = 0; i < 256; i++) {
        if (ascii[i] != 0) {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int f;
    char data[]  = "sledbobber\0";
    char data2[] = "sleddels";
    char data3[] = "abbaz";
    char data4[] = "yaabb";
    
    //f = match("bob", data);
    //if (f != -1) printf("found match at %d -> %s\n", f, &data[f]);

    printf("is match %d\n", match(data, "bob"));
    printf("is pal   %d\n", palindrome(data2));
    printf("is ana   %d\n", anagram(data3, strlen(data3), data4, strlen(data4)));
    printf("search   %d\n", sequential_search(data, 10, 'z'));
}

