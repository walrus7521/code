#include <stdio.h>

//-- given a list of ints, return the sum of the even numbers in the list
//-- e.g.: [1,2,3,4,5] => 2 + 4 => 6

int evenSum(int a[], int len) {
  int result = 0;
  int i;
  for (i = 0; i < len; i++) {
    if (a[i] % 2 == 0) {
        result += a[i];
   }
 }
  return result;
}

//-- make this recursive
int evenSumR(int a[], int len)
{
  int sum = 0, i;  
  if (len == 0) return 0;
  if (len == 1) return a[0];
  if (a[0] % 2 == 0) return a[0] + evenSumR(&a[0], len-1);
  else return 0;
}


int sum(int a[], int p, int n)
{
    //if (n == 0) return 0; // skip the zero case
    if (n == 1) return a[p];
    int x = a[p];
    if (x % 2 == 0) return x + sum(a,p+1,n-1);
    else return sum(a,p+1,n-1);
    //return a[p] + sum(a,p+1,n-1);
}

int main()
{
    int a[] = {1,2,3,4,5,6,7,8,9,10};
    int n = sizeof(a)/sizeof(a[0]);
    printf("sum: %d\n", sum(a,0,n));
    printf("even: %d\n", evenSum(a,n));
}

