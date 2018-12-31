#include <stdio.h>
#include <stdint.h>

void ones(uint32_t x)
{
    int ones = 0;
    printf("and out: %x\n", x);
    while (x) {
        ones++;
        printf("%x\n", x);
        x &= (x-1);
    }
    printf("ones: %d\n", ones);
}

void not_and(uint32_t x)
{
    int i;
    uint32_t y=x;
    printf("not and out: %x\n", x);
    while (x) {
        y = x & ~(x-1);
        printf("%x\n", y);
    }
}

int main()
{
    ones(0b10001001);
    //not_and(0xff);
}
