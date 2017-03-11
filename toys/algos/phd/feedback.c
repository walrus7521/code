#include <stdio.h>
#include <math.h>

#define SAMPLE_SIZE 16

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
    unsigned long avg = 0;
    unsigned long v = 256;
    avg = cal_running_avg(avg, v);
    v = 128;
    avg = cal_running_avg(avg, v);
    v = 64;
    avg = cal_running_avg(avg, v);
    v = 32;
    avg = cal_running_avg(avg, v);
    printf("%ld -> %ld\n", v, avg);
}
