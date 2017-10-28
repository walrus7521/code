#include <iostream>
#include <cmath>

using namespace std;

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

double f(double x, double y)
{
    return x*y;
}

double g(double x)
{
    if (x > 0) return 1/x;
    return x;
}

int main()
{
    double x = gradient_descent<double, double, double, double (*f)(double,double), double(*g)(double)>(3, .1, .2, f, g);
}

