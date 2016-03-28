#include <stdio.h>
#include <math.h>

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

unsigned long datagen()
{
    static unsigned long frame_count = 0;
    static unsigned long toa = 0;
    static unsigned char  dir = 1;
    if (frame_count % 100) {
        if (dir > 0) {
            toa += 0.1;
            if (toa >= 7.0) {
                dir = -dir;
            }
        } else {
            toa -= 0.1;
            if (toa <= -7.0) {
                dir = -dir;
            }
        }
        printf("frame: %d dir %d toa %.2f\r\n", frame_count, dir, toa);
    }
    frame_count++;
    return toa;
}

double sine()
{
    static float time = 0;
    int dir = 1;
    float sineval;
    if (time > 7.0) {
        dir = -1;
    } else
    if (time < -7.0) {
        dir = 1;
    }
    time += dir * 0.1;
    sineval = sin(time);
    printf("time: %lf, %lf\n", time, sineval);
    return sineval;

}

int main()
{
    int i;
    unsigned long n, v, avg = 0;
    double nd;
    for (i = 0; i < 256; ++i) {
        n = random() & 0x0FFF;
        v = n + 7;
        nd = sine();
        n = datagen();
        v = n;
        //v = (unsigned long) 10 * nd;
        avg = cal_running_avg(avg, v);
        printf("[%02d] = %08lX -> %08lx\n", i, v, avg);
    }
}
