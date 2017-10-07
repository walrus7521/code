#include <iostream>
#include <stdexcept> // out_of_range

namespace troll {

    // abstract type - pure interface
    class Container {
    public:
        virtual double& operator[] (int i) = 0;
        virtual int size() const = 0;
        virtual ~Container() {}
    private:
    };

    class Complex {
    public:
        Complex(double r, double i) : re{r}, im{i} {}
        Complex(double r)           : re{r}, im{0} {}
        Complex()                   : re{0}, im{0} {}

        double real() const { return re; }
        void   real(double r) { re = r; }
        double imag() const { return im; }
        void   imag(double i) { im = i; }

        Complex& operator+=(Complex z) { re += z.re, im += z.im; return *this; }
        Complex& operator-=(Complex z) { re -= z.re, im -= z.im; return *this; }
        Complex& operator*=(Complex z) { re *= z.re, im *= z.im; return *this; }
        Complex& operator/=(Complex z) { re /= z.re, im /= z.im; return *this; }

    private:
        double re;
        double im;
    };


    class Vector : public Container {
    public:
        Vector() :elem{ nullptr }, sz{ 0 } {}
        Vector(int s) :elem{ new double[s] }, sz{ s } 
        {
            for (int i = 0; i < size(); ++i)  elem[i] = 0;
        }
        Vector(std::initializer_list<double> lst)
            : elem{ new double[lst.size()] }, sz{ static_cast<int>(lst.size()) }
        {
            std::copy(lst.begin(), lst.end(), elem);
        }
        ~Vector() { delete[] elem; }
        void resize(int n) 
        {
            delete[] elem;
            elem = new double[n];
            sz = n;
            for (int i = 0; i < size(); ++i)  elem[i] = 0;
        }
        double& operator[] (int i) 
        { 
            if (i < 0 || size() <= i)
                throw std::out_of_range("Vector::operator[]");
            return elem[i]; 
        }
        int size() const noexcept { return sz; }
        void show() 
        {
            for (int i = 0; i < size(); ++i) {
                std::cout << elem[i] << std::endl;
            }
        }
    private:
        double *elem;
        int sz;
    };

}

double read_and_sum(int s)
{
    troll::Vector v(s);
    double sum;

    try {

        for (int i = 0; i != v.size(); ++i) 
            std::cin >> v[i];
    
        sum = 0;
        for (int i = 0; i != v.size(); ++i)
            sum += v[i];

        std::cout << v[9];

    } catch (std::out_of_range) {
        std::cout << "out of range dude\n";
        // we can rethrow
        // throw;
        // or terminate();
    }

    return sum;
}

void use(troll::Container& c)
{
    const int sz = c.size();
    for (int i = 0; i < sz; ++i) {
        std::cout << c[i] << std::endl;
    }
}

int main()
{
    //std::cout << read_and_sum(6) << std::endl;
    static_assert(sizeof(int) <= 4, "ints are too small");

    troll::Complex a, b;

    troll::Vector v = {1,2,3,4};
    use(v); // polymorphic function
    v.show();
    v.resize(4);
    v.show();

}

