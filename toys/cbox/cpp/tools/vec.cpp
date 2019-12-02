#include <iostream>
#include <memory>
#include <algorithm>
#include <initializer_list>
#include "vec.h"


Vector::Vector(std::initializer_list<double> lst) : elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())} {
        std::copy(lst.begin(), lst.end(), elem);
}

double& Vector::operator[](int i) {
    return (elem[i]);
}

int Vector::size() const {
    return sz;
}

void Vector::push_back(double x) {
}

Vector read(std::istream& is) {
    Vector v(7);
    for (double d; is >> d; )
       v.push_back(d);
    return v;
}


#if 1
int main()
{
    std::unique_ptr<Vector> v {new Vector(55)};
    Vector vt (54);
    std::cout<< "size " << vt.size() << std::endl;
    std::cout<< "size " << v->size() << std::endl;

    Vector v2 = read(std::cin);

    //for (int i = 0; i < 16; ++i)
    //    v[i] = i;

    //for (int i = 0; i < 16; ++i)
    //    std::cout<< v[i] << std::endl;

}
#endif

