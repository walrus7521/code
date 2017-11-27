#include "types.h"

int count_bits(uint32_t x)
{
    int count = 0;
    while (x) {
        count++;
        x &= (x-1);
    }
    return count;
}

int parity(uint32_t x)
{
    int count = count_bits(x);
    //return (count % 2) ? 0 : 1; // even parity
    return (count & 0x01); // odd parity
}


int main()
{
    int x = 0x5a;
    printf("count:  %x => %d\n", x, count_bits(x));
    printf("parity: %x => %d\n", x, parity(x));
}

