#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

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


#define ALL(x) x.begin(), x.end()
#define UNIQUE(x) (x).resize(unique(ALL(x)) - (x).begin())
void n_rand_ints_sorted(int n)
{
    int arr[] = {1,2,2,2,3,3,2,2,1};
    n = sizeof(arr)/sizeof(arr[0]);
    vector<int> v(arr, arr+n);
    sort(ALL(v));
    UNIQUE(v);
    for (auto x : v) {
        cout << x << endl;
    }
}

int main()
{
    //pi_decimal_places(9);
    //pi_n_decimal_places(11);
    n_rand_ints_sorted(32);
}

