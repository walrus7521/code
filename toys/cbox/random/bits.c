#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t rotate_right(uint32_t vector, int n)
{
    printf("rot[%d]: %x\n", n, vector);
    for (int i = 0; i < n; i++) {
        int x = vector >>= 1;
        printf("vec[%d]: %x\n", i, x);
        if (x) {
            vector |= 1;
        } else {
            vector &= ~1;
        }
    }
    return vector;
}

uint32_t rotate_left(uint32_t vector, int n)
{
    printf("rot[%d]: %x\n", n, vector);
    for (int i = 0; i < n; i++) {
        int x = vector <<= 1;
        printf("vec[%d]: %x\n", i, x);
        if (x) {
            vector |= 1;
        } else {
            vector &= ~1;
        }
    }
    return vector;
}

int main()
{
    uint32_t vector = 0x1;
    int n = 4;
    printf("rotate %x left  %d => %x\n", vector, n, rotate_left(vector, n));
    printf("rotate %x right %d => %x\n", vector, n, rotate_right(vector, n));
    return 0;
}
