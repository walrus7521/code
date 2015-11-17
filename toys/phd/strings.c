#include <stdio.h>
#include <string.h>

int findmatch(char *pattern, char *string)
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

int main()
{
    int f;
    char data[] = "sledbobber\0";
    
    f = findmatch("bob", data);
    if (f != -1) printf("found match at %d -> %s\n", f, &data[f]);
}

