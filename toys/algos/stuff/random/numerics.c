#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// rotate a string
// fix primes 235

uint32_t rotate_right(uint32_t vector, int n)
{
    printf("rot[%d]: %x\n", n, vector);
    for (int i = 0; i < n; i++) {
        int set = vector & 1;
        int x = vector >>= 1;
        vector |= (set << 31);
        printf("vec[%d]: %x\n", i, x);
    }
    return vector;
}

uint32_t rotate_left(uint32_t vector, int n)
{
    printf("rot[%d]: %x\n", n, vector);
    for (int i = 0; i < n; i++) {
        int set = vector & 0x80000000;
        int x = vector <<= 1;
        vector |= set;
        printf("vec[%d]: %x\n", i, x);
    }
    return vector;
}

int test_bit_rot()
{
    uint32_t vector = 0x1;
    int n = 4;
    //printf("rotate 0x%x left  %d => 0x%08x\n", vector, n, rotate_left(vector, n));
    printf("rotate %x right %d => 0x%08x\n", vector, n, rotate_right(vector, n));
    return 0;
}

int min(int a, int b, int c) {
    if (a <= b && a <= c) return a;
    if (b <= a && b <= c) return b;
    return c;
}

void test_primes_235()
{
    int p0[3] = {1,1,1};
    int p1[3] = {2,3,5};
    for (int i = min(p0[0], p0[1], p0[2]); i <= 1024; i = min(p1[0], p1[1], p1[2])) {
        printf("i:%04d> %04d %04d %04d\n", i, p0[0], p0[1], p0[2]);
        p0[0] = p1[0];
        p0[1] = p1[1];
        p0[2] = p1[2];
        p1[0] = 2 * i;
        p1[1] = 3 * i;
        p1[2] = 5 * i;
    }
    
}

int main()
{
    test_primes_235();
    test_bit_rot();
}
