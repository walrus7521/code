#pragma once

#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <memory>
#include <cassert>

class complex
{
public:
    complex(double r, double i)    : r(r), i(i) {}      // default constructor
    complex(double r)              : complex{ r, 0 } {} // delegator
    complex()                      : complex{ 0, 0 } {} // another delegator

    complex(const complex& c) : i(c.i), r(c.r) {
        std::cout << "copy constructor" << std::endl;
    } // copy constructor

    complex& operator=(const complex& src) // copy assignment operator
    {
        std::cout << "copy assign: " << src.r << std::endl;
        r = src.r; i = src.i;
        return *this; // return reference for multiple assignments
    }

    complex operator+(const complex& c2) const
    {
        return complex(r + c2.r, i + c2.i);
    }

    friend std::ostream& operator<< (std::ostream& os, const complex& c)
    {
       os << "real: " << c.r << ", imag: " << c.i;
        return os;
    }

    complex subtract(const complex& c1, const complex& c2)
    {
        return{ c1.r - c2.r, c1.i - c2.i };
    }

private:
    double r = 0.0, i = 0.0; // default member values
};

class vector
{
    typedef vector self;
    typedef double T; 

public:
    /*explicit*/ vector(int n) : my_size{ n }, data{ new double[my_size] } {}
    ~vector() {
        delete[] data;
    }

    vector(vector&& src) // move constructor
        : my_size(src.my_size), data(src.data)
    {
        src.data = nullptr; // vector is empty after move
        src.my_size = 0;
    }

    vector& operator=(vector&& src) // move assignment
    {
        assert(my_size == 0 || my_size == src.my_size);
        std::swap(data, src.data); // swap pointers
        return *this;
    }

    vector& operator=(const vector& src) // copy assignment operator
    {
        if (this == &src)
            return *this;
        assert(my_size == src.my_size);
        for (int i = 0; i < my_size; ++i)
            data[i] = src.data[i];
        return *this;
    }

    vector(std::initializer_list<double> values)
        : my_size(values.size()), data(new double[my_size])
    {
        std::copy(values.begin(), values.end(), data);
        std::cout << "Init constructor called.\n";
    }

    self& operator=(const std::initializer_list<double>& values)
    {
        assert(my_size == values.size());
        std::copy(values.begin(), values.end(), data);
        std::cout << "Init assignment called.\n";
        return *this;
    }

    T& operator[](int i)
    {
        std::cout << "non const[]\n";
        assert(i >= 0 && i < my_size);
        return data[i];
    }

    const T& operator[](int i) const
    {
        std::cout << "const[]\n";
        assert(i >= 0 && i < my_size);
        return data[i];
    }

    int size() const { return my_size; }

private:
    int my_size;
    double *data;
};
