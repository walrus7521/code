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

uint64_t bitsort(array_t *a)
{
    uint64_t x = 0;
    for (int i = 0; i < a->size; i++) {
        x |= (1 << a->a[i]);
    }
    return x;
}

void show(array_t *a)
{
    for (int i = 0; i < a->size; i++) {
        printf("[%d] => %d\n", i, a->a[i]);
    }
}

int main()
{
    int x = 0x5a;
    printf("count:  %x => %d\n", x, count_bits(x));
    printf("parity: %x => %d\n", x, parity(x));

    array_t a = {.size=6, {4,3,1,2,7,32}};
    show(&a);
    uint64_t y = bitsort(&a);
    printf("y: %x\n", y);
    for (int i = 0; i < 64; i++) {
        if (y & 1) {
            printf("%d\n", i);
        }
        y >>= 1;
    }

}

