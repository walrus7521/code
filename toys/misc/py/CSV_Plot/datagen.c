#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define T_MAX 100
void delay(int milli_seconds) 
{  
    clock_t start_time = clock();   
    while (clock() < start_time + milli_seconds) ; 
}

int main(int argc, char **argv) 
{
#if 0
    if( argc != 3) {
      printf("Mandatory arguments: <rows> <cols>\n");
         return 1;
    }
#endif
    int frame=0, col=0;
    float phi, theta, psi;
   
    phi     = 0.0f;
    theta   = 0.0f;
    psi     = 0.0f;

    float t = 0.0f;
    float dt = 0.01f;
    while(1) {
        printf("%d,%f,%f,%f\n",
                frame, phi, theta, psi);
        fflush(stdout);
        phi    += 0.0001f;
        phi     = sin(10.0f * t);
        theta   = sin(2*phi);
        psi     = cos(3*theta);
        frame++;
        t += dt;
        if (dt > 0 && t > T_MAX) {
            dt = -dt;
        } else
        if (dt < 0 && t < T_MAX) {
            dt = -dt;
        }

        delay(20);
        
#if 0
        for(col = 0; col < COLS; col++) {
            if(col > 0) {
                printf(", ");
            }
            /* Default values are "row x col" */
            printf("\"%dx%d\"", row, col);
        }
        printf("\r\n");
#endif
    }
    return 0;
}

