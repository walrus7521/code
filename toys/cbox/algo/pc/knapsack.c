// A Dynamic Programming based solution for 0-1 Knapsack problem 
#include<stdio.h> 
  
int max(int a, int b) { return (a > b)? a : b; }
  
// return max value that can be put in knapsack w/capacity W 
int knapSack(int W, int wt[], int val[], int n) 
{ 
   int i, w; 
   int K[n+1][W+1]; 
  
   // Build K[][] table bottom-up
   for (i = 0; i <= n; i++) 
   { 
       for (w = 0; w <= W; w++) 
       { 
           if (i==0 || w==0) 
               K[i][w] = 0; 
           else if (wt[i-1] <= w) 
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]); 
           else
                 K[i][w] = K[i-1][w]; 
       } 
   } 
  
   return K[n][W]; 
} 
  
int main() 
{ 
    int val[] = {1500, 2000, 3000}; 
    int wt[] = {1, 2, 3, 4}; 
    int  W = 4; 
    int n = sizeof(val)/sizeof(val[0]); 
    printf("%d\n", knapSack(W, wt, val, n)); 
    return 0; 
}

