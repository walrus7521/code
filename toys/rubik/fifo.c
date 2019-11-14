#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define FIFO_SZ (8)

char buf[FIFO_SZ];
int head=0,tail=0,cap=FIFO_SZ,size=0;

void init()
{
    // create bit mask = size of fifo
}

int data_avail()
{
    // get num leading ones
    return (size & -size) + 1;
    //return (tail-head);
}

int space_avail()
{
    // get num trailing zeros
    int p = log2(size & -size) + 1; // this is lsb
    return (size - (tail-head));
}

int peek()
{
    // get last bit / data
    return buf[tail];
}

char get(int n)
{
    // return n trailing data
    if (tail-head) {
        return (buf[head++]);
    }
    return '0';
}

void put(char *data, int n)
{
    // set trailing zeros
    int i;
    for (i = 0; i < n; i++) {
        buf[i] = data[i];
    }
    tail += n;
}

int main()
{
    int spc, dat;
    char data[] = {'a','b','c','d','e','f','g','h'};
    char *pdata;
    int read[FIFO_SZ];
    int i;
    
    int n = 0x8020;
    //int p = (n & -n);
    int p = log2(n & -n) + 1;     
    printf("n: %x, p: %x\n", n, p);

    // left most set bit
    int x = 0x00000001;
    int xx = x;
    int pos = 32, bpos = -1;
    while (pos--) {
        if (x & 0x80000000) {bpos = pos; goto out;}
        x <<= 1;
    }
out:
    printf("left pos of %x is %d\n", xx, bpos);

    return 0;

    while (1) {
        if ((spc = space_avail())) {
            pdata = data;
            put(pdata, spc);
        }
        if ((dat = data_avail())) {
            for (i = 0; i < dat; i++) {
                data[i] = get(i);
            }
        }
    }
}

