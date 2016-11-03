#include <stdio.h>

#define WIDTH         16
#define DECIMAL       6
#define FRAC          (1 << DECIMAL)
#define WHOLE_MASK    0x03FF
#define DECIMAL_MASK  0x003F

int mult(int x, int y)
{
    int z = x * y;
    return z;
}

int divide(int x, int div)
{
    int z = x >> (div-1);
    return z;
}

int add(int x, int y)
{
    int z = x + y;
    return z;
}
int make_fixed(int x)
{
    int y = (x << DECIMAL);
    return y;
}

void show(int x)
{
    int whole, decimal;
    float frac;
    whole = (x >> DECIMAL) & WHOLE_MASK;
    decimal = x & DECIMAL_MASK;
    frac = (float) decimal / (1.0 * FRAC);
    printf("fixed: %08X\n", x);
    printf("whole: %04X, decimal: %04X\n", whole, decimal);
    printf("frac: %0.2f\n", frac);
}

int main()
{
    int x, y, z;
    printf("frac %d\n", FRAC);
    x = 5;
    x = make_fixed(x);
    y = 3;
    //y = make_fixed(y);
    show(x);
    //show(y);
    //z = add(x, y);
    //z = mult(x, y);
    z = divide(x, 3);
    show(z);
}

