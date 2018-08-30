#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int main()
{
    unsigned long long v64, v64_align;
    unsigned long long align = 0x1000;
    v64 = 0xdeadfeef;
    v64_align = (v64 + (align-1)) &~ (align-1);
    printf("v64+align-1 = %llx\n", v64 + (align-1));
    printf("v64 %016llx, ~mask %016llx, mask %016llx, v64_align %016llx\n", v64, ~(align), align, v64_align);
    return 0;
}


