#include <stdio.h>

int main()
{
    int X, Y, Z;
    X = 0x42;
    Y = 0x37;
    printf("x: %xh, y: %xh\n", X, Y);
    X = X ^ Y;
    printf("x: %xh, y: %xh\n", X, Y);
    Y = Y ^ X;
    printf("x: %xh, y: %xh\n", X, Y);
    X = X ^ Y;
    printf("x: %xh, y: %xh\n", X, Y);

}
