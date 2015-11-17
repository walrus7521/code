// Suppose the given number is X, then  
// X*(10^Y) < 2^N < X*(10^Y) + (10^Y) => Y*log10 + logX < N < Y*log10 + log(X+1)  
// Another limitation is: Y > int(lgX) + 1  
  
#include <math.h>  
#include <iostream>  
  
using namespace std;  
  
static int SmallestIntLargerThan(long double x)  
{  
    return static_cast<int>(floor(x + 1.0));  
}  
  
static int GetPower(int y, long double log_2_10, long double log_2_x, long double log_2_x_plus_1)  
{  
    long double n = static_cast<long double>(SmallestIntLargerThan(y * log_2_10 + log_2_x));  
    if (n < y * log_2_10 + log_2_x_plus_1)  
        return static_cast<int>(n);  
  
    return -1;  
}  
  
static void HandleNumber(long double x, long double log_2_10, long double ln_2, long double ln_10)  
{  
    long double ln_x = log(x);  
    long double log_2_x = log(x) / ln_2;  
    long double log_2_x_plus_1 = log(x + 1.0) / ln_2;  
  
    int y = SmallestIntLargerThan(ln_x/ln_10) + 1;  
    int n;  
    while((n = GetPower(y, log_2_10, log_2_x, log_2_x_plus_1)) <= 0)  
        ++y;  
    cout << n << endl;  
}  
  
static void Test()  
{  
    long double ln_2 = log(2);  
    long double ln_10 = log(10);  
    long double log_2_10 = ln_10 / ln_2;  
  
    long double x;  
    while(cin >> x)  
        HandleNumber(x, log_2_10, ln_2, ln_10);  
}  
  
int main(int argc, char* argv[])  
{  
    Test();  
    return 0;  
}  

