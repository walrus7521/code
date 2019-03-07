#include <cstdio>
#include <cmath>

void pi_decimal_places(int n)
{
    bool first = true;
    double integral, fractional;
    double pi = 2 * acos(0.0);

    for (int i = 0; i <= n; i++) {
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

void pi_n_decimal_places(int n)
{
    double pi = 2 * acos(0.0);
    printf("%.*lf\n", n, pi); // ****
}

int main()
{
    pi_decimal_places(9);
    pi_n_decimal_places(11);
}

