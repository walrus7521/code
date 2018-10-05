#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * source: pearls: bentley, pg 165
 */
int pstrcmp(const void *p1, const void *p2)
{
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
    char buf[BUFSIZ];
    char dude[BUFSIZ];
    if (!fgets(buf, sizeof buf, stdin)) return 1;

    size_t len = strlen(buf);
    const char *a[len];

    size_t i;
    int maxi, maxlen;
    for (i = 0; i < len; i++) a[i] = &buf[i];

    qsort(a, len, sizeof(char *), pstrcmp);

    int nlen;
    maxlen = -1;
    maxi = 0;
    for (i = 0; i < len-1; i++) {
        nlen = comlen(a[i],a[i+1]);
        //printf("len: %d\n", nlen);
        if (nlen > maxlen) {
            maxlen = nlen;
            maxi = i;
            //printf("max: %d\n", maxlen);
        }
        //printf("%x\n", a[i] - buf);
        //printf("%x => %x\n", &buf[i], a[i]);
    }
    //printf("max[%d] = %d\n", maxi, maxlen);

    strncpy(dude, a[maxi], maxlen);
    dude[maxlen] = '\0';
    printf("dude: '%s'\n", dude);

    return 0;
}


