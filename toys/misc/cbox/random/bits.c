#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

int main()
{
    uint32_t vector = 0x1;
    int n = 4;
    //printf("rotate 0x%x left  %d => 0x%08x\n", vector, n, rotate_left(vector, n));
    printf("rotate %x right %d => 0x%08x\n", vector, n, rotate_right(vector, n));
    return 0;
}
