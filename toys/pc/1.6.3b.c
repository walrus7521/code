#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#define MAX 1004

int main()
{
    int ns, nstudents;
    double xp, over, under, average, sum, expenses[MAX];
    while (EOF != scanf("%d\n", &nstudents)) {
        if (nstudents == 0) break;
        sum = over = under = 0;
        for (ns = 0; ns < nstudents; ns++) { // get expenses
            scanf("%lf\n", &expenses[ns]);// = (xp * SCALE_TO_PENNIES);
            sum += expenses[ns];
        }
        average = sum / nstudents;
        for (ns = 0; ns < nstudents; ns++) {
            if (expenses[ns] < average) {
                under += (floor((average - expenses[ns])*100))/100;
            } else
            if (expenses[ns] > average) {
                over += (floor((expenses[ns] - average)*100))/100;
            }
        }
        if (under < over) under = over;
        printf("$%.2f\n", ((double) under));
    }
    return 0;
}
