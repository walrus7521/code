#include <cstdio>
#include <cmath>

#define M_PI 3.14159265358979323846
void pi_decimal_places()
{
    int N=15, caseNo = 1;
    bool first = true;
    double integral, fractional, pi = M_PI;

    for (int i = 0; i < N; i++) {
        fractional = modf(pi, &integral);
        pi -= integral;
        pi *= 10.0f;
        if (first == true) {
            printf("%d.", (int) integral);
            first = false;
        } else {
            printf("%d", (int) integral);
        }
    }
    printf("\n");
}

// wrong!!
float newPrecision(float n, float i) 
{ 
    return floor(pow(10,i)*n)/pow(10,i); 
}

void pi_decimal_places2(int n)
{
   float num = 3.14159265358979323846;
  
   // 4 digits after the decimal point 
   num = floor(10000*num)/10000; 
  
   printf("%f", num); 
}

int main()
{
    //pi_decimal_places2(7);
    printf("%f\n", newPrecision(M_PI, 9.0));
}

