#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * http://www.mathcs.emory.edu/~cheung/Courses/171/Syllabus/8-List/array-queue2.html
 */

#define RING_SIZE 10
int ring_buffer[RING_SIZE];
int ring_read, ring_write, ring_size;

int ring_full()
{
    if (ring_read == (ring_write+2)%ring_size) {
        return 1;
    }
    return 0;
}

int ring_empty()
{
    if (ring_read == ring_write) return 1;
    return 0;
}

void ring_put(int elem)
{
    ring_buffer[ring_write] = elem;
    printf("write[%d] = %d\n", ring_write, elem);
    ++ring_write;
    ring_write %= ring_size;
}

int ring_get()
{
    int item = ring_buffer[ring_read];
    printf("read[%d] = %d\n", ring_read, item);
    ++ring_read;
    ring_read %= ring_size;
    return item;
}

int main()
{
    int i, j;
    ring_size = RING_SIZE;
    ring_read = ring_write = 0;
    i = 0;
    while (!ring_full()) {
        ring_put(i);
        i++;
    }
    j = ring_get();
    j = ring_get();
    j = ring_get();
    ring_put(j);
    ring_put(j);
    ring_put(j);
    ring_put(j);
    while (!ring_empty()) {
        j = ring_get();
    }

    return 0;
}
