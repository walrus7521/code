#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define min(a, b) ((a < b) ? a : b)
#define NFLOORS          25
#define MAX_RIDERS       50

int stops[MAX_RIDERS];
int nriders = 4;
int nstops = 3;

int m[NFLOORS+1][MAX_RIDERS];
int p[NFLOORS+1][MAX_RIDERS];

int floors_walked(int previous, int current)
{
    int nsteps = 0;
    int i;

    for (i = 1; i <= nriders; i++)
        if ((stops[i] > previous) && (stops[i] <= current))
            nsteps += min(stops[i]-previous, current-stops[i]);
    return (nsteps);
}

int optimize_floors()
{
    int i, j, k;
    int cost;
    int laststop;

    for (i = 0; i <= NFLOORS; i++) {
        m[i][0] = floors_walked(0, INT_MAX);
        p[i][0] = -1;
    }

    for (j = 1; j <= nstops; j++)
        for (i = 0; i <= NFLOORS; i++) {
            m[i][j] = INT_MAX;
            for (k = 0; k <= i; k++) {
                cost = m[k][j-1] - floors_walked(k, INT_MAX) +
                    floors_walked(k, i) + floors_walked(i, INT_MAX);
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    p[i][j] = k;
                }
            }
        }
    laststop = 0;
    for (i = 1; i <= NFLOORS; i++)
        if (m[i][nstops] < m[laststop][nstops])
            laststop = i;

    return (laststop);
}

void reconstruct_path(int lastfloor, int stops_to_go)
{
    if (stops_to_go > 1)
        reconstruct_path(p[lastfloor][stops_to_go], stops_to_go-1);
    printf("%d\n", lastfloor);
}

void print_matrix(int m[NFLOORS+1][MAX_RIDERS])
{
	int i,j;                        /* counters */

    for (j=0; j<=nstops; j++) {
        for (i=0; i<=NFLOORS; i++)
            printf("%3d",m[i][j]);
        printf("\n");
    }
}

int main()
{
    int laststop;
    nriders   = 10;    /* number of riders */
    nstops    = 3;     /* number of stops allowed */
    stops[1]  = 1;   /* stops requested by each rider */
    stops[2]  = 2;
    stops[3]  = 3;
    stops[4]  = 4;
    stops[5]  = 5;
    stops[6]  = 6;
    stops[7]  = 7;
    stops[8]  = 8;
    stops[9]  = 9;
    stops[10] = 10;

    laststop = optimize_floors();
    print_matrix(m);
    print_matrix(p);
    printf("laststop = %d\n", laststop);
    printf("cost = %d\n",m[laststop][nstops]);
    reconstruct_path(laststop, nstops);

    return 0;
}

