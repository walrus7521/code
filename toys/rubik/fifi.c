#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define FIFO_SZ (32)
#define FIFO_SZ_MASK (0xFFFFFFFF)
char buf[FIFO_SZ];
uint32_t idx=0,size=0;

int data_avail();

void print_dots()
{
    int i;
    int sz = data_avail();
    //printf("sz: %d\n", sz);
    printf("                   \r");
    for (i = 0; i < sz; i++) { printf("."); }
    printf("\r");
    fflush(stdout);
}

int my_log2(uint32_t index)
{
    int targetlevel = 0;
    while (index >>= 1) ++targetlevel;
    return targetlevel;
}

void init()
{
    size = 0;
}

int space_avail()
{
    if (size == 0) return FIFO_SZ;
    int v = ((int)my_log2(size)) & FIFO_SZ_MASK;
    //printf("size: %04x, v: %x\n", size, v);
    int spc = FIFO_SZ-v-1;
    return (v ? spc : FIFO_SZ-1);
}

int data_avail()
{
    int spc = space_avail();
    int daval = FIFO_SZ - spc;
    //printf("spc: %d, daval: %x\n", spc, daval);
    return daval;
    return (spc ? daval : 0);
}


int peek()
{
    return buf[idx-1];
}

char get()
{
    size &= ~(1 << --idx);
    printf("get() idx: %02d dat: %c sz: %08x\n", idx, buf[idx], size);
    return (buf[idx]);
}

void put(char data)
{
    buf[idx] = data;
    size |= (1 << idx++);
    printf("put() idx: %02d dat: %c sz: %08x\n", idx-1, data, size);
}

void test()
{
    int i, curs=0;
    char data[] = {'a','b','c','d','e','f','g','h',
                   'i','j','k','l','m','n','o','p',
                   'q','r','s','t','u','v','w','x',
                   'y','z','0','1','2','3','4','5'};

    while (space_avail()) {
        put(data[curs++]);
    }

    while (data_avail()) {
        char c = get();
        //printf("got: %c\n", c);
    }

}

void dev()
{
    int i, spc, dat;
    size = 0x00;
    spc = space_avail();
    dat = data_avail();
    printf("sz: %02x, spc: %02d, dat: %02d\n", size, spc, dat);
    for (i = 0; i < FIFO_SZ; i++) {
        size |= (1<< i);
        spc = space_avail();
        dat = data_avail();
        printf("sz: %02x, spc: %02d, dat: %02d\n", size, spc, dat);
        //print_dots();
        sleep(1);
    }
    for (i = FIFO_SZ-1; i >= 0; i--) {
        size &= ~(1<< i);
        spc = space_avail();
        dat = data_avail();
        printf("sz: %02x, spc: %02d, dat: %02d\n", size, spc, dat);
        //print_dots();
        sleep(1);
    }

}

int main()
{
    test();
    return 0;
}

