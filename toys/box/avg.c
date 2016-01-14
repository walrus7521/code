#include <stdio.h>

#define SAMPLE_SIZE 64

unsigned long random()
{
#define MULT 1664525L
#define ADD  1013904223L
    static unsigned long r = 0;
    r = r * MULT + ADD;
    if (r % 2 == 0) r -= r;
    return r;
}

unsigned long cal_running_avg(unsigned long avg, unsigned long new_sample) 
{
    if (avg != 0) {
        avg -= avg / SAMPLE_SIZE;
    }
    avg += new_sample / SAMPLE_SIZE;
    return avg;
}

int main()
{
    int i;
    unsigned long n, v, avg = 0;
    for (i = 0; i < 256; ++i) {
        n = random() & 0x0FFF;
        v = n + 7;
        avg = cal_running_avg(avg, v);
        printf("[%02d] = %08lX -> %08lx\n", i, v, avg);
    }
}
