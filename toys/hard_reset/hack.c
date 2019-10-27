#include <stdio.h>

void test_bits()
{
    int x;

    x = 0xA7;
    printf("%x => %x\n", x, x & (x-1));
    printf("%x => %x\n", x, x | (x+1));

    printf("%x => %x\n", x, x & (x+1));
    x = 0xFFF0;
    printf("%x => %x\n", x, x & (-x));
    printf("%x => %x\n", x, ~x & (x+1));
    x = 0x58;
    printf("%x => %x\n", x, ~x & (x-1));
    printf("%x => %x\n", x, x ^ (x-1));
    printf("%x => %x\n", x, x | (x-1));
    printf("%x => %x\n", x, ((x | (x-1))+1) & x);
}



int main()
{
    test_bits();
}
