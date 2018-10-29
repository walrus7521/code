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
  
float travel(float W, float rate[], float time[], int n) 
{ 
   int i, w; 
   float K[n+1][(int)W+1]; 
  
   // Build K[][] table bottom-up
   for (i = 1; i <= n; i++) 
   { 
       for (w = 1; w <= W; w++) 
       { 
           if (i==0 || w==0) 
               K[i][w] = 0; 
           else if (rate[i-1] <= w) 
                 K[i][w] = max(time[i-1] + K[i-1][w-(int)rate[i-1]],  K[i-1][w]); 
           else
                 K[i][w] = K[i-1][w]; 
       } 
   } 
  
   return K[n][(int) W];
} 

void test_knap()
{
    int val[] = {1500, 2000, 3000, 2000, 1000}; // value of each item
    int wt[] = {1, 3, 4, 1, 1}; // wt of each item
    int  W = 4; // capacity of knapsack
    int n = sizeof(val)/sizeof(val[0]); 
    printf("%d\n", knapSack(W, wt, val, n)); 
}

void test_travel()
{
    float time[] = {0.0f, 0.0f, 0.5, 1.0, 2.0, 0.5}; // time in days each location
    float rate[] = {0, 7, 6, 9, 9, 8}; // rating of each location
    float  W = 2.0; // number of days total for trip
    int n = sizeof(time)/sizeof(time[0]); 
    printf("%f\n", travel(W, rate, time, n)); 
}

int main() 
{ 
    //test_knap();
    test_travel();
    return 0; 
}

