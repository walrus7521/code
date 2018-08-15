#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int pstrcmp(const void *, const void *);
static int comlen(const char *p, const char *q);

int
main(void)
{
    char buf[BUFSIZ];
    if (!fgets(buf, sizeof buf, stdin)) return 1;

    size_t len = strlen(buf);
    const char *a[len];

    size_t i, maxi, maxlen;
    for (i = 0; i < len; i++) a[i] = &buf[i];

    //qsort(a, len, sizeof *a, pstrcmp);
    qsort(a, len, sizeof(char *), pstrcmp);

    maxlen = -1;
    maxi = 0;
    for (i = 0; i < len; i++) {
        //if (comlen(a[i],a[i+1]) > maxlen) {
        //    maxlen = comlen(a[i],a[i+1]);
        //    maxi = i;
        //}
        printf("%d\n", a[i] - buf);
    }
    printf("%d\n", maxi);

    return 0;
}

int
pstrcmp(const void *p1, const void *p2)
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

