#include <stdio.h>
#include <math.h>

#define SAMPLE_SIZE 16

// do interp

float integ(float gain, float input, float ic, float sat, int hold)
{
    static float state = 0.0f;
    if (hold == 0) {
        state += input * gain;
        if (state > sat) {
            state = sat;
        }
    } else {
        state = ic;
    }
    return state;
}

float kal(float input, float gain)
{
    static float state = 0.0f;
    state += (input - state) * gain;
    return state;
}

unsigned long cal_running_avg(unsigned long avg, unsigned long new_sample) 
{
    if (avg != 0) {
        avg -= avg / SAMPLE_SIZE;
    }
    avg += new_sample / SAMPLE_SIZE;
    return avg;
}

void test_avg()
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

void test_integ()
{
    float gain, input, ic, output, sat;
    int hold;
    hold = 0;
    ic = 1.0f;
    gain = 1.0f;
    input = 0.01f;
    sat = 42.0f;
    int i;
    for (i = 0; i < 16; i++) {
        output = integ(gain, input, ic, sat, hold);
        printf("integ: %f\n", output);
        input = output;
    }

}

int main()
{
    test_avg();
    test_integ();
}
