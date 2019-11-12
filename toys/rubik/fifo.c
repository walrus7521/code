#include <stdio.h>

#define FIFO_SZ (8)
char buf[FIFO_SZ];
int head=0, tail=0;
int size=FIFO_SZ;
uint32_t fifo;
void init()
{
    // create bit mask = size of fifo
}

int data_avail()
{
    // get num leading ones
    return (tail-head);
}

int space_avail()
{
    // get num trailing zeros
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

