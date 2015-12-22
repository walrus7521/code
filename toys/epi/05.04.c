#include <stdio.h>
#include <inttypes.h>

/*
 * Find a closest integer with the same weight
 *   Define the weight of a nonnegative integer x to be the number of bits that are set to
 *   1 in its binary representation.  For example, since 92 in base-2 equals (1011100):base-2,
 *   the weight of 92 is 4.
 *
 *   Write a function which takes as input a nonnegative integer x and returns y != x such that
 *   y has the same weight as x, and the difference of x and y is as small as possible.
 *   You can assume x in not 0, or all 1s.
 */

unsigned short bitcount(uint64_t x)
{
    short count = 0;
    while (x) {
        count++;
        x &= (x - 1); // drops lowest set bit
    }
    return count;
}

uint64_t precompute_smallest_weight[] = {
/*  0 */   0x00,
/*  1 */   0x01,
/*  2 */   0x03,
/*  3 */   0x07,
/*  4 */   0x0F,
/*  5 */   0x1F,
/*  6 */   0x3F,
/*  7 */   0x7F,
/*  8 */   0xFF,
/*  9 */   0x1FF,
/* 10 */   0x3FF,
/* 11 */   0x7FF,
/* 12 */   0xFFF,
/* 13 */   0x1FFF,
/* 14 */   0x3FFF,
/* 15 */   0x7FFF,
/* 16 */   0xFFFF,
/* 17 */   0x1FFFF,
/* 18 */   0x3FFFF,
/* 19 */   0x7FFFF,
/* 20 */   0xFFFFF,
/* 21 */   0x1FFFFF,
/* 22 */   0x3FFFFF,
/* 23 */   0x7FFFFF,
/* 24 */   0xFFFFFF,
/* 25 */   0x1FFFFFF,
/* 26 */   0x3FFFFFF,
/* 27 */   0x7FFFFFF,
/* 28 */   0xFFFFFFF,
/* 29 */   0x1FFFFFFF,
/* 30 */   0x3FFFFFFF,
/* 31 */   0x7FFFFFFF,
/* 32 */   0xFFFFFFFF,
/* 33 */   0x1FFFFFFFF,
/* 34 */   0x3FFFFFFFF,
/* 35 */   0x7FFFFFFFF,
/* 36 */   0xFFFFFFFFF,
/* 37 */   0x1FFFFFFFFF,
/* 38 */   0x3FFFFFFFFF,
/* 39 */   0x7FFFFFFFFF,
/* 40 */   0xFFFFFFFFFF,
/* 41 */   0x1FFFFFFFFFF,
/* 42 */   0x3FFFFFFFFFF,
/* 43 */   0x7FFFFFFFFFF,
/* 44 */   0xFFFFFFFFFFF,
/* 45 */   0x1FFFFFFFFFFF,
/* 46 */   0x3FFFFFFFFFFF,
/* 47 */   0x7FFFFFFFFFFF,
/* 48 */   0xFFFFFFFFFFFF,
/* 49 */   0x1FFFFFFFFFFFF,
/* 50 */   0x3FFFFFFFFFFFF,
/* 51 */   0x7FFFFFFFFFFFF,
/* 52 */   0xFFFFFFFFFFFFF,
/* 53 */   0x1FFFFFFFFFFFFF,
/* 54 */   0x3FFFFFFFFFFFFF,
/* 55 */   0x7FFFFFFFFFFFFF,
/* 56 */   0xFFFFFFFFFFFFFF,
/* 57 */   0x1FFFFFFFFFFFFFF,
/* 58 */   0x3FFFFFFFFFFFFFF,
/* 59 */   0x7FFFFFFFFFFFFFF,
/* 60 */   0xFFFFFFFFFFFFFFF,
/* 61 */   0x1FFFFFFFFFFFFFFF,
/* 62 */   0x3FFFFFFFFFFFFFFF,
/* 63 */   0x7FFFFFFFFFFFFFFF
};

uint64_t smallest_weight(uint64_t x)
{
    int c = bitcount(x);
    uint64_t wt = precompute_smallest_weight[c];
    printf("%016llx has %d bits, resulting in %016llx\n", x, c, wt);
    return wt;
}

unsigned short lowest_zero_bit(uint64_t x)
{
    x=~x;
    return bitcount((x&(-x))-1);
}

unsigned short lowest_one_bit(uint64_t x)
{
    unsigned short n = 0;
    while (x) {
        if (x&1) break;
        x >>= 1;
        n++;
    }
    return n;
}

uint64_t smallest_weight_difference(uint64_t x) 
/* this is broken :
 * see instead swap_first_2_consecutive_bits_that_differ
 */
{
    unsigned short set, clr;
    set = lowest_one_bit(x);
    clr = lowest_zero_bit(x);
    x ^= ((1 << set) | (1 << clr));
    return x;
}

uint64_t swap_first_2_consecutive_bits_that_differ(uint64_t x) 
{
    int i;
    uint64_t y, save_x = x;
    unsigned short bit = 0, set, clr;
    bit = 0;
    for (i = 0; i < 64; i++) {
        y = x ^ 3;
        if (y == 1 || y == 2) break;
        bit++;
        x >>= 1;
    }
    set = bit;
    clr = bit+1;
    save_x ^= ((1 << set) | (1 << clr));
    return save_x;
}

int main()
{
    uint64_t x = 7;
    //printf("smallest weight of (%lld) 0x%llx is 0x%llx\n", x, x, smallest_weight(x));
    //printf("smallest weight diff of (%lld) 0x%llx is 0x%llx\n", x, x, smallest_weight_difference(x));
    printf("smallest weight diff of (%lld) 0x%llx is 0x%llx\n", x, x, swap_first_2_consecutive_bits_that_differ(x));
}
