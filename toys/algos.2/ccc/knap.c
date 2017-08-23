#include <stdio.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define WEIGHT (0)
#define VALUE  (1)

int sack[3][3];
int items[3][3] = {{1,1500},{4,3000},{3,2000}};
int sizes[3] = {1,2,3};

void show()
{
    int r, c;
    for (r = 0; r < 3; r++) {
        printf("(%d,%d)\n", items[r][WEIGHT], items[r][VALUE]);
    }
    for (r = 0; r < 3; r++) {
        for (c = 0; c < 3; c++) {
            printf("%d ", sack[r][c]);
        }
        printf("\n");
    }
}

// for a given row, find max for a given column
int get_max(int row, int col)
{
    static int max = 0;
    int r, c;
    printf("find max for row %d, col %d\n", row, col);
    for (r = 0; r <= row; r++) {
        int wt_of_row = items[r][WEIGHT];
        int val = items[r][VALUE];
        for (c = 0; c <= col; c++) {
            int wt_cap_of_col = sizes[c];
            if (wt_of_row <= wt_cap_of_col && val > max) {
                max = val;
                printf("setting max = %d\n", max);
            }
        }
    }
    printf("max[%d,%d] = %d\n", row, col, max);
    return max;
}

// Returns the maximum value that can be put in a knapsack of capacity W
int knapSack(int W, int wt[], int val[], int n)
{
   // Base Case
   if (n == 0 || W == 0)
       return 0;
 
   // If weight of the nth item is more than Knapsack capacity W, then
   // this item cannot be included in the optimal solution
   if (wt[n-1] > W) {
       return knapSack(W, wt, val, n-1);
   }
 
   // Return the maximum of two cases: 
   // (1) nth item included 
   // (2) not included
   else return MAX( val[n-1] + knapSack(W-wt[n-1], wt, val, n-1),
                    knapSack(W, wt, val, n-1)
                  );
}

void knap()
{
    int mx = get_max(0,0);
        //mx = get_max(0,1);
        //mx = get_max(0,2);
}

void knap2()
{
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int W = 50;
    int n = sizeof(val)/sizeof(val[0]);
    printf("%d\n", knapSack(W, wt, val, n));
}

int main()
{
    //knap();
    knap2();
    //show();
}
