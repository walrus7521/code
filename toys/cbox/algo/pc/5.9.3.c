// Suppose the given number is X, then  
// X*(10^Y) < 2^N < X*(10^Y) + (10^Y) => Y*log10 + logX < N < Y*log10 + log(X+1)  
// Another limitation is: Y > int(lgX) + 1
//

#include <stdio.h>
#include <math.h>  
  
static int smallest_int_larger_than(long double x)  
{  
    return (int) (floor(x + 1.0));  
}  
  
static int get_power(int y, long double log_2_10, long double log_2_x, long double log_2_x_plus_1)  
{  
    long double n = (long double) (smallest_int_larger_than(y * log_2_10 + log_2_x));  
    if (n < y * log_2_10 + log_2_x_plus_1)  return (int) (n);  
    return -1;  
}  
  
static void crunch(long double x, long double log_2_10, long double ln_2, long double ln_10)  
{  
    int n;  
    long double ln_x = log(x);  
    long double log_2_x = log(x) / ln_2;  
    long double log_2_x_plus_1 = log(x + 1.0) / ln_2;  
    int y = smallest_int_larger_than(ln_x/ln_10) + 1;  
    while ((n = get_power(y, log_2_10, log_2_x, log_2_x_plus_1)) <= 0) ++y;  
    printf("%d\n", n);
}  
  
int main()  
{  
    long double ln_2 = log(2);  
    long double ln_10 = log(10);  
    long double log_2_10 = ln_10 / ln_2;  
    long double x;  
    while (scanf("%lg\n", &x) != EOF) {
        //printf("got a %lg\n", x);
        crunch(x, log_2_10, ln_2, ln_10);  
    }
    return 0;  
}  

