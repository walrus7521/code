#include <stdio.h>

// gcc -S hello.c
// as -o hello.o hello.s
// ld hello.o -lc /usr/lib/crt1.o
// ./a.out


int x = 0;
static double y = 3.14;

int doit()
{
    return 42;
}

static void func(int a)
{
}

int main()
{
    printf("dude, wusup\n");
    func(17);
    return 0;
}
