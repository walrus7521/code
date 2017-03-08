#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fifo.inc"

int test()
{
    char buffer[256];
    int i;
    fifo_init(0x42, buffer, 256);
    for (i = 0; i < 26; i++) {
        fifo_enqueue(0x42, 'a'+i);
    }
    char c;
    fifo_peek_relative(0x42, 2, &c);
    printf("peek: %c\n", c);
    char tmp[8] = "";
    memset(tmp, 8, 0);
    fifo_peek_data(0x42, (void *) tmp, 8);
    printf("peek data: %s\n", tmp);
    fifo_enqueue_data(0x42, tmp, 8);
    while (fifo_get_num_data_avail(0x42)) {
        fifo_dequeue_data(0x42, tmp, 1);
        printf("dequeued: %c\n", tmp[0]);
    }
}


int main()
{
    printf("testing fifo\n");
    test();
}
