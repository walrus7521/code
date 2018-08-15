#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int pstrcmp(const void *, const void *);

int
main(void)
{
    char buf[BUFSIZ];
    if (!fgets(buf, sizeof buf, stdin)) return 1;

    size_t len = strlen(buf);
    const char *array[len];

    size_t i;
    for (i = 0; i < len; i++) array[i] = &buf[i];

    qsort(array, len, sizeof *array, pstrcmp);

    for (i = 0; i < len; i++) printf("%tu\n", array[i] - buf);

    return 0;
}

int
pstrcmp(const void *p1, const void *p2)
{
    const char *const *s1 = p1;
    const char *const *s2 = p2;

    return strcmp(*s1, *s2);
}

