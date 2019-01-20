#include <stdio.h>
#define max(a,b) ((a) > (b) ? (a) : (b))

int test()
{
    int a;
    int b = 9;
    int c = 8;

    a = max(b, c/2);
    return a;
}

int main()
{
    printf("test: %d\n", test());
}
