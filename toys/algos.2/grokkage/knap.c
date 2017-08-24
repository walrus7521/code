#include <stdio.h>

// add collection of items chosen as output

#define MAX(a,b) ((a) > (b) ? (a) : (b))

// Returns the maximum value that can be put in a knapsack of capacity W
int knapper(int W, int wt[], int val[], int n)
{
   // Base Case
   if (n == 0 || W == 0)
       return 0;
 
   // If weight of the nth item is more than Knapsack capacity W, then
   // this item cannot be included in the optimal solution
   if (wt[n-1] > W) {
       return knapper(W, wt, val, n-1);
   }
 
   else {
   // Return the maximum of two cases: 
   // (1) nth item included 
   // (2) not included
       int val1 = val[n-1] + knapper(W-wt[n-1], wt, val, n-1);
       int val2 = knapper(W, wt, val, n-1);
       return MAX(val1, val2);
   }
}


 // Returns the maximum value that can be put in a knapsack of capacity W
int knappy(int W, int wt[], int val[], int n)
{
   int i, w;
   int K[n+1][W+1];
   // Build table K[][] in bottom up manner
   for (i = 0; i <= n; i++) {
       for (w = 0; w <= W; w++) {   
           // Base case
           if (i == 0 || w == 0) {
               K[i][w] = 0;
           }

           // if weight of ith item if more than knapsack capacity, then
           // this item can't be included in optimal solution
           else if (wt[i-1] > w) {
               K[i][w] = K[i-1][w];
           } 
           
           else {
           // pick max of
           // (1) ith item included
           // (2) not included
               int val1 = val[i-1] + K[i-1][w-wt[i-1]];
               int val2 = K[i-1][w];
               K[i][w] = MAX(val1, val2);
           }
       }
   }
   // looks like its always the last entry
   return K[n][W];
}
 
int val[] = {60, 100, 120, 150, 200};
int wt[]  = {10,  20,  30,   4,  32};
int n = sizeof(val)/sizeof(val[0]);

void knap2()
{
    int W = 50; // capacity of knapsack
    printf("knapper = %d\n", knapper(W, wt, val, n));
}

void knap3()
{
    int  W = 50; // capacity of knapsack
    printf("knappy  = %d\n", knappy(W, wt, val, n));
}

int main()
{
    knap2();
    knap3();
}

