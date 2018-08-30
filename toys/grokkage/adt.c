#include <stdlib.h>
#include <stdio.h>

typedef struct _foo foo_t;

// foo.c
struct _foo {
    int x;
    int y;
};

foo_t *create()
{
    foo_t *f = malloc(sizeof(foo_t));
    f->x = 42;
    f->y = 17;
    return f;
}

void show(foo_t *f)
{
    printf("%d - %d\n", f->x, f->y);
}
