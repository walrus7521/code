#include <stdio.h>
#include <stdint.h>
#include <limits.h>

// http://graphics.stanford.edu/~seander/bithacks.html

int my_log2(uint32_t index)
{
    int targetlevel = 0;
    while (index >>= 1) ++targetlevel;
    return targetlevel;
}

int msbit(uint32_t x)
{
    int v = my_log2((double) x);
    printf("x: %x, v:%d\n", x, v);
    return 32-v;
}

void swap(uint32_t *x, uint32_t *y)
{
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;   
}

// we want to find the absolute value of v
int myabs(int v)
{
#define CHAR_BITS (8)
    unsigned int r;  // the result goes here 
    int const mask = (v >> sizeof(int)) * (CHAR_BITS - 1);

    r = (v + mask) ^ mask;
    printf("v: %x, mask: %x sum: %x, xor: %x\n", v, mask, v+mask, r);
    //Patented variation:
    //r = (v ^ mask) - mask;
    return r;
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

    n = 0x04000040;
    int y = (n - (n & (n - 1)));
    printf("n: %x => %x\n", n, y);
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
    msbit(0x0800);
    return 0;

    play();
    int v = -42;
    printf("abs(%d) = %d\n", v, myabs(v));
}

