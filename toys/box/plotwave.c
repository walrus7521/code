#include <stdio.h>
#include <math.h>

#define TWO_PI  2*3.14159
#define ROWS    40
#define COLS    120
#define SCALE   10
#define OFFSET  ROWS/2
#define MAX     99999.0

int grid[ROWS][COLS];

void plot(float *data, int len, float min, float max)
{
    int i, amp;
    printf("num points: %d : min %f, max %f\n", len, min, max);
    for (i = 0; i < len; i++) {
        amp = (int) (data[i] * SCALE) + OFFSET;
        if (amp > 0 && amp > ROWS) amp = ROWS;
        else if (amp < 0)          amp = 0;
        //printf("grid[%d][%d] = %f\n", i, amp, data[i]);
        grid[amp][i] = 1;
    }
}

void clear()
{
    int r, c;
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLS; c++) {
            grid[r][c] = 0;
        }
    }
}

void display()
{
    int r, c;
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLS; c++)
            if (grid[r][c] == 0) printf(" ");
            else printf(".");
        printf("\n");
    }
}

int capture(float *data, int nsegs, float *min, float *max, double (*xfrm)(double))
{
    int i;
    float phasor[nsegs];
    for (i = 0; i < nsegs; i++) {
        phasor[i] = (i+1) * TWO_PI / 16.0;
        data[i] = xfrm(phasor[i]);
        if (data[i] > *max) *max = data[i];
        if (data[i] < *min) *min = data[i];
    }
}

int main()
{
    int nsegs = COLS, i;
    float phasor[nsegs], data[nsegs], max, min;
    max = -MAX; min =  MAX;
    clear();
    capture(data, nsegs, &min, &max, sin);
    plot(data, nsegs, min, max);
    capture(data, nsegs, &min, &max, cos);
    plot(data, nsegs, min, max);
    display();
    return 0;
}

