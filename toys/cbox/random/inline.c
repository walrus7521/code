#include <stdio.h>
#include <time.h>

static inline int mymax(int a, int b) {
  return a > b ? a : b;
}

/* here, do your time-consuming job */

#define ITERATIONS 1024000000
int main()
{
    clock_t begin, end;
    double time_spent;
    int i, time;
    printf("start...\n");
    begin = clock();
    for (i = 0; i < ITERATIONS; ++i) {
        mymax(1,1);
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("end...time=%.2lf\n", time_spent);
}

