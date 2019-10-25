#include <iostream>
#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <valarray>
#include <cmath>
#include <typeinfo>
#include <type_traits>
#include <memory>
#include <vector>
#include <complex>
#include <algorithm>
//#include "math.h"

using namespace std;

namespace my_stuff {

template <typename T, typename U>
inline auto max(T a, U b)
{
    std::cout << a << " is type " << typeid(a).name() << std::endl;
    return (a > b ? a : b);
}

template <typename TPara>
void f1(TPara p)
{
    std::cout << "f1 has type " << typeid(p).name() << std::endl;
}

template <typename TPara>
void f2(const TPara& p)
{
    std::cout << "f2 has type " << typeid(p).name() << std::endl;
}

template <typename TPara>
void f3(TPara& p)
{
    std::cout << "f3 has type " << typeid(p).name() << std::endl;
}

template <typename TPara>
void f4(TPara&& p)
{
    std::cout << "f4 has type " << typeid(p).name() << std::endl;
}

template <typename TPara>
void f5(TPara&& p)
{
    f4(std::forward<TPara>(p));
}

} // namespace my_stuff

namespace algegra {
    template <typename T>
    class vector
    {
        public:
            explicit vector(int size)
                : my_size(size), data( new T[my_size] ) {}
            vector(const vector& that)
                : my_size(that.my_size), data(new T[my_size])
            {
                std::copy(&that.data[0], &that.data[that.my_size], &data[0]);
            }
            int size() const { return my_size; }
            const T& operator[](int i) const
            {
                check_index(i);
                return data[i];
            }
        private:
            void check_index(int i) { assert(i <= my_size); }
            int my_size;
            std::unique_ptr<T[]> data;
    };
}

using namespace my_stuff;

int main()
{
    std::cout << "max(3,4) is " << my_stuff::max(3,4) << std::endl;
    std::cout << "max(3.14,4.2) is " << my_stuff::max(3.14,4.2) << std::endl;

    int i = 0;
    int& j = i;

    std::unique_ptr<int> up;
    const std::unique_ptr<int> cup;
    ::f1(move(up));
    f2(move(up));
    my_stuff::f2(up);
    my_stuff::f2(j);
    my_stuff::f3(up);
    my_stuff::f3(cup);
    my_stuff::f4(move(up));

    //std::complex<float> z(3,2), c(4,8);
    //std::cout << "max of c and z is " << ::max(c,z) << std::endl;

    //vector<complex<float>> v;
    //sort(v.begin(), v.end());

}

