#include <stdio.h>
#include <stdint.h>
#include <limits.h>

void swap(uint32_t *x, uint32_t *y)
{
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;   
}

int bits(uint32_t v, uint32_t l, uint32_t r)
{
    uint32_t mask;
    int i;
    mask = 0;
    printf("in: %08x\n", v);
    for (i = l; i >= (l-r); --i) {
        mask |= (v & (1 << i));
    }
    printf("mask: %08x\n", mask);
    int ones = 0;
    while (mask) {
        mask &= (mask-1);
        ones++;
    }
    printf("ones: %d\n", ones);
    return mask;
}

int ones(uint32_t x)
{
    int ones = 0;
    //printf("and out: %x\n", x);
    while (x) {
        ones++;
        //printf("%x\n", x);
        x &= (x-1);
    }
    //printf("ones: %d\n", ones);
    return ones;
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

void play()
{
    int x=9;
    printf("x: %x\n", x);
    x ^= ((x & ~(x))-1); // turn on all zero bits, off all one bits
    printf("x: %x\n", x);
    int n=0x80000000, d=1, r,l;
#define INT_BITS (32)
    int int_bits = ones(UINT_MAX);
    l = (n << d)|(n >> (int_bits - d)); // left rotate
    printf("n: %x, l: %x\n", n, l);
    r = (n >> d)|(n << (int_bits - d)); // right rotate
    printf("n: %x, r: %x\n", n, r);
}

int main()
{
    //ones(0b10001001);
    //not_and(0xff);
    //bits(0x11111111, 22, 12);
    //int x=4, y=2;
    //printf("x: %d, y:%d\n", x, y);
    //swap(&x, &y);
    //printf("x: %d, y:%d\n", x, y);
    play();
}

