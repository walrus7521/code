#include <stdio.h>
#include <stdarg.h>

#define MAX 1004
#define SCALE_TO_PENNIES 100
long expenses[MAX];

unsigned short PRIO_HIGH    = 0x0001;
unsigned short PRIO_NORMAL  = 0x0002;
unsigned short PRIO_LOW     = 0x0004;
int PRIO_LOG = 0; /* 0xffff; */
int dbg_log(int priority, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    if (priority & PRIO_LOG)
        vprintf(format, args);
    va_end(args);
    return 0;
}

void init(int nstudents)
{
    int ns;
    for (ns = 0; ns < MAX; ns++) {
        expenses[ns] = 0;
    }
}

void process_expenses(int nstudents)
{
    int ns;
    long minx = 0, average, pennies, num_over = nstudents;
    long sum = 0, residual;
    for (ns = 0; ns < nstudents; ns++) {
        sum += expenses[ns];
    }
    average = sum / nstudents;
    pennies = sum % nstudents;
    for (ns = 0; ns < nstudents; ns++) {
        if (expenses[ns] <= average) {
            dbg_log(1, "add to minx exchange[%d] = %ld\n", ns, expenses[ns]);
            minx += average - expenses[ns];
            num_over--;
        }
    }
    if (pennies > num_over) {
        residual = (pennies - num_over);
        minx += residual;
        dbg_log(1, "minx += residual %ld\n", residual);
    }

    dbg_log(1, "sum: %ld, avg %ld, pennies %ld, num over %ld\n", sum, average, pennies, num_over);
    dbg_log(1, "minx = %ld\n", minx);
    printf("minx = %.2f\n", ((float) minx / SCALE_TO_PENNIES));
}

void get_expenses(int nstudents)
{
    int ns;
    float xp;
    long expense;
    for (ns = 0; ns < nstudents; ns++) {
        scanf("%f\n", &xp);
        expenses[ns] = (long) (xp * SCALE_TO_PENNIES + 0.5);
        dbg_log(1, "expense[%d] = %ld\n", ns, expenses[ns]);
    }
}

int main()
{
    int nstudents;
    while (EOF != scanf("%d\n", &nstudents)) {
        if (nstudents == 0) break;
        dbg_log(1, "*************************************************\n");
        dbg_log(1, "num students: %d\n", nstudents);
        init(nstudents);
        get_expenses(nstudents);
        process_expenses(nstudents);
    }
    return 0;
}
