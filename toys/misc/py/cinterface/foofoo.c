#include <stdio.h>
#include <stdlib.h>

struct point {
    int x;
    int y;
};

void foofoo() 
{
    printf("fooey bar bat\n"); 
}

int foobar(char *name)
{
    printf("bar: %s\n", name);
    return 42;
}

void bar(struct point *pt)
{
    printf("yo bar x: %d, y: %d\n", pt->x, pt->y);
}

struct point *foo(int x, int y)
{
    struct point *pt = malloc(sizeof(struct point));
    pt->x = x; pt->y = y;
    printf("ah foo x: %d, y: %d\n", pt->x, pt->y);
    return pt;
}

