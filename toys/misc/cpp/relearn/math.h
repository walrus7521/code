#pragma once

class complex
{
public:
    complex(double r = 0, double i = 0) : r(r), i(i) {}      // default constructor
    complex(double r)                   : complex{ r, 0 } {} // delegator
    complex()                           : complex{ 0, 0 } {} // another delegator

    complex(const complex& c) : i(c.i), r(c.r) {} // copy constructor
    friend std::ostream& operator<< (std::ostream& os, const complex& c)
    {
       os << "real: " << c.r << ", imag: " << c.i;
        return os;
    }

private:
    double r = 0.0, i = 0.0; // default member values
};

class vector
{
public:
    /*explicit*/ vector(int n) : my_size(n), data(new double[my_size]) {}
private:
    int my_size;
    double *data;
};
