#include <stdio.h>
#include <stdint.h>

void loader()
{
    printf("hello, loader\n");
}

int main()
{
    uint64_t ldr_start_addr = (uint64_t) &loader;
    typedef void (*funcptr)(void);
    funcptr jumper = (funcptr)(ldr_start_addr);
    printf("%p => %llx\n", jumper, ldr_start_addr);
    (*jumper)();
}
