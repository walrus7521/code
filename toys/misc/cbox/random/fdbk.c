#include <stdio.h>
#include <math.h>

#define SAMPLE_SIZE 16


/* C function implementing the simpe lowpass:
 *   difference equation:
 *      y(n) = x(n) + x(n-1)
 * https://ccrma.stanford.edu/~jos/fp/Definition_Simplest_Low_Pass.html
 * https://www.mathworks.com/help/dsp/ug/lowpass-filter-design.html?requestedDomain=www.mathworks.com
 */
double simplp (double *x, double *y, 
               int M, double xm1)
{
  int n;
  y[0] = x[0] + xm1;
  for (n=1; n < M ; n++) {
    y[n] =  x[n]  + x[n-1];
  }
  return x[M-1];
}

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

void test_lp()
{
    double x[10] = {1,2,3,4,5,6,7,8,9,10}; 
    double y[10];

    int i;
    int N=10;
    int M=N/2; /* block size */
    double xm1 = 0;

    xm1 = simplp(x, y, M, xm1);
    xm1 = simplp(&x[M], &y[M], M, xm1);

    printf("low pass\n");
    for (i=0;i<N;i++) {
        printf("x[%d]=%f\ty[%d]=%f\n",i,x[i],i,y[i]);
    }
}

int main()
{
    test_avg();
    test_integ();
    test_lp();
}
