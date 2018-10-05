// source: pearls: bentley, pg 165 LCS
#include "utils.h"

int pstrcmp(const void *p1, const void *p2)
{ // needs to handle one level of indirection
    const char *const *s1 = p1;
    const char *const *s2 = p2;
    return strcmp(*s1, *s2);
}

static int comlen(const char *p, const char *q)
{
    int i = 0;
    while (*p && (*p++ == *q++)) i++;
    return i;
}

int main(void)
{
    char buf[BUFSIZ], dude[BUFSIZ];
    int i, maxi, maxlen, len, nlen;

    if (!fgets(buf, sizeof buf, stdin)) return 1;
    len = strlen(buf);
    const char *a[len];
    
    for (i = 0; i < len; i++) a[i] = &buf[i]; // setup suffix array
    qsort(a, len, sizeof(char *), pstrcmp); // sort the strings

    for (i = maxi = 0, maxlen = -1; i < len-1; i++) {
        nlen = comlen(a[i],a[i+1]);
        if (nlen > maxlen) {
            maxlen = nlen;
            maxi = i;
        }
    }
    strncpy(dude, a[maxi], maxlen);
    dude[maxlen] = '\0';
    printf("dude: '%s'\n", dude);
    return 0;
}

