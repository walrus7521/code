#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

/*
 * Find the median: minimum of sum
 */

#define MAX_LOCATIONS 256
int location[MAX_LOCATIONS];
int nr_locations;

void isort(int n)
{
    int c, d, t;
    for (c = 1 ; c <= n - 1; c++) {
        d = c;
        while ( d > 0 && location[d] < location[d-1]) {
            t = location[d];
            location[d] = location[d-1];
            location[d-1] = t;
            d--;
        }
    }    
}

void init()
{
    int i;
    for (i = 0; i < MAX_LOCATIONS; i++) location[i] = 0;
}

void sim()
{
    int i;
    srand (time(NULL));
    for (i = 0; i < MAX_LOCATIONS; i++) location[i] = 2 * (rand()*i+1);
    nr_locations = rand() % 253;
}

void show(int n)
{
    int i;
    for (i = 0; i < n; i++) printf("location[%2d] = %2d\n", i, location[i]);
}

void brute_force(int nlocs)
{
    int i, j, minloc, sum, minsum, minsumloc;
    minsum = INT_MAX;
    for (i = 0; i < nlocs; i++) {
        minloc = i;
        sum = 0;
        for (j = 0; j < nlocs; j++) {
            if (j != minloc) sum += abs(location[j] - location[i]);
        }
        if (sum < minsum) {
            minsumloc = minloc;
            minsum = sum;
        }
    }
    /* printf("brute_force: minsum %3d - minloc[%2d] = %3d\n", minsum, minsumloc, location[minsumloc]); */
}

int main()
{
    int ncases, nlocs, i, j, minloc, sum, minsum, minsumloc, predict;

    scanf("%d\n", &ncases);
    for (i = 0; i < ncases; i++) {
        init();
        /* sim(); */
        scanf("%d ", &nlocs);
        for (j = 0; j < nlocs; j++) {
            scanf("%d ", &location[j]);
        }
        isort(nlocs);
        /* show(nlocs); */
        if (nlocs % 2)  predict = (nlocs/2);
        else predict = (nlocs/2) - 1;
        printf("%d\n", location[predict]);
        brute_force(nlocs);
    }
    return 0;
}
