#include <stdio.h>

typedef void (*foo1)(int);
typedef int (*foo2)(int);
typedef char *(*foo3)(int);

struct callbacks
{
    foo1 func1;
    foo2 func2;
    foo3 func3;
} callbacks;

void add1(int i)
{
    printf("add1: %d\n", i);
}

int add2(int i)
{
    printf("add2: %d\n", i);
    return 0;
}

char *add3(int i)
{
    printf("add3: %d\n", i);
    return NULL;
}

int main()
{
    struct callbacks cbs;

    cbs.func1 = add1;
    cbs.func2 = add2;
    cbs.func3 = add3;

    cbs.func1(7);
    cbs.func2(8);
    cbs.func3(9);

}
