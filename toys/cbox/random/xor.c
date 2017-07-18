#include <stdio.h>

int main()
{
    int X, Y, Z;
    X = 42;
    Y = 37;
    printf("x: %d, y: %d\n", X, Y);
    X = X ^ Y;
    Y = Y ^ X;
    X = X ^ Y;
    printf("x: %d, y: %d\n", X, Y);

}
