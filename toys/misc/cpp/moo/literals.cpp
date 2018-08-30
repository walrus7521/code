#include <iostream>
 
// used as conversion
constexpr long double operator"" _deg ( long double deg )
{
    return deg*3.141592/180;
}

constexpr long double operator"" _rad ( long double rad )
{
    return rad*180.0/3.141592;
}

// used with custom type
struct mytype
{
    mytype ( unsigned long long m):m(m){}
    unsigned long long m;
};
mytype operator"" _mytype ( unsigned long long n )
{
    return mytype(n);
}
 
// used for side-effects
void operator"" _print ( const char* str )
{
    std::cout << str;
}
 
int main(){
    double x_rads = 90.0_deg;
    double y_degs  = 1.57_rad;
    std::cout << std::fixed << x_rads << '\n';
    std::cout << std::fixed << y_degs << '\n';
    mytype y = 123_mytype;
    std::cout << y.m << '\n';
    0x123ABC_print;
}
