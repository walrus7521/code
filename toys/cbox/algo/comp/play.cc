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

int main()
{
    pi_decimal_places();
}

