#include <stdio.h>

/* simple 1st order lowpass:
 *      y(n) = x(n) + x(n-1)
 */
double lowpf (double *x, double *y, 
               int M, double xm1)
{
    int n;
    y[0] = x[0] + xm1;
    for (n=1; n < M ; n++) {
        y[n] =  x[n]  + x[n-1];
    }
    return x[M-1];
}

int main() { 
    //double x[10] = {1,2,3,4,5,6,7,8,9,10}; // ins
    //double x[10]   = {0,0,0,0,0,1,0,0,0,0}; // ins pulse
    double x[10]   = {0,0,0,0,0,1,1,1,1,1}; // ins step
    double y[10]; // outs

    int i;
    int N=10;
    int M=N/2; /* block size */
    double xm1 = 0;

    xm1 = lowpf(x, y, M, xm1);
    xm1 = lowpf(&x[M], &y[M], M, xm1);

    for (i=0;i<N;i++) {
        printf("x[%d]=%f\ty[%d]=%f\n",i,x[i],i,y[i]);
    }

}
/* Output: 
 *    x[0]=1.000000     y[0]=1.000000
 *    x[1]=2.000000     y[1]=3.000000
 *    x[2]=3.000000     y[2]=5.000000
 *    x[3]=4.000000     y[3]=7.000000
 *    x[4]=5.000000     y[4]=9.000000
 *    x[5]=6.000000     y[5]=11.000000
 *    x[6]=7.000000     y[6]=13.000000
 *    x[7]=8.000000     y[7]=15.000000
 *    x[8]=9.000000     y[8]=17.000000
 *    x[9]=10.000000    y[9]=19.000000
 */

