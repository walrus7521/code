#include <stdio.h>
#include <limits.h>

#define NUM_CYCLES_ENTRIES      1000032 /* pad the array size */
#define MAX_INPUT_VAL           1000000
#define INVALID_CYCLE_VALUE     -1      /* sentinel */
unsigned long cycles_array[NUM_CYCLES_ENTRIES];

unsigned long gen_cycle(unsigned long k)
{
    unsigned long cycles = 1; /* minimum cycles is 1 */
    unsigned long n = k; /* loop control */
    while (n != 1) {
        /* printf("%u ", n); */
        cycles++;
        if (0 == n % 2) {
            n /= 2;
        } else {
            n *= 3;
            n++;
        }
    }
    /* printf("\n"); */
    /* save the value for future posterity */
    cycles_array[k] = cycles;
    /*printf("gen_cycle returning %ld\n", cycles); */
    return cycles;
}

unsigned long get_max_cycles(unsigned long from, unsigned long to)
{
    unsigned long k; /* loop control */
    unsigned long max_cycles = 0, cycles;
    for (k = from; k <= to; k++) {
        /* check if the value has already been calculated */
        if (cycles_array[k] == INVALID_CYCLE_VALUE) {
            /* printf("invalid entry: %d\n", k); */
            cycles = gen_cycle(k);
        } else {
            cycles = cycles_array[k];
        }
        /* printf("n = %u, max = %lu\n", n, max); */
        if (cycles > max_cycles) {
            max_cycles = cycles;
        }
    }
    return max_cycles;
}

int main()
{
    long i, j, m, n; /* input and swaps, made signed to detect negative numbers */
    unsigned long max_cycles;

    /* initialize the cycles_array 
     * this array is used to eliminate redundant
     * calculations.
     */
    for (i = 0; i < NUM_CYCLES_ENTRIES; i++) 
        cycles_array[i] = INVALID_CYCLE_VALUE;

    /* read the user input integer pair */
    while (EOF != scanf("%ld %ld", &i, &j)) {
        /* eliminate invalid input... */
        if (   i == 0      || j == 0 
            || i > MAX_INPUT_VAL || j > MAX_INPUT_VAL
            || i < 0       || j < 0       ) {
            printf("skipping\n");
            continue;
        }
        /* swap the input if i > j
         * and alias them as m and n respectively
         */
        m = i;
        n = j;
        if (i > j) {
            m = j;
            n = i;
        }
        /* get the maximum cycles for the interval */
        max_cycles = get_max_cycles(m, n);
        /* formatted output.. */
        printf("%ld %ld %ld\n", i, j, max_cycles);
    }
    return 0;
}

