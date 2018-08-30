#include <iostream>
#include "Vector.h"

// g++ -std=c++11 main.cc

void testV() {
#if 0
    Vector v;
    Vector v1(1);
    Vector v2 = {1,2,3,4};
    Vector v3{v2};
    Vector v4(4);
    v4 = v3;
#endif
    Vector x(10);
    Vector y(10);
    Vector z(10);
    //z=x;
    //y=std::move(z);
    z = x+y;
    show(z);
}

void testvc() {
    Vector_container vc(4);
    vc[0] = 4;
    vc[1] = 5;
    vc[2] = 6;
    vc[3] = 7;
    use(vc);
    Vector_container x(10);
    Vector_container y(10);
    Vector_container z(10);
    z=x;
    y=std::move(z);
 }

int main() {
    //testvc();
    testV();
    return 0;
}
