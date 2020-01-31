#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>

using namespace std;

void test_template_error()
{
    vector<complex<float>> v;
    //sort(v.begin(), v.end()); // errors because complex has no operator>
}

#if 0
void gradient_descent(double *x,
    double *y, double s, double eps,
    double (*f)(double, double),
    double (*gx)(double, double),
    double (*gy)(double, double))
{
    double val = f(*x, *y), delta;
    do {
        *x -= s * gx(*x,*y);
        *y -= s * gy(*x,*y);
        double new_val = f(*x,*y);
        delta = abs(new_val - val);
        val = new_val;
    } while (delta > eps);
}
#endif

template <typename Value, typename P1,
          typename P2, typename F,
          typename G>
Value gradient_descent(Value x, P1 s,
        P2 eps, F f, G g)
{
    auto val = f(x), delta = val;
    do {
        x -= s * g(x);
        auto new_val = f(x);
        delta = abs(new_val - val);
        val = new_val;
    } while (delta > eps);
    return x;
}

struct ft {
    double operator() (double &v) { return 42.0; }
};

double func(double x) { return x; }

int main()
{
    double x = gradient_descent(3.0, .1, .2, func, func);
    cout << "grad: " << x << endl;
}

