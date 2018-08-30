#ifndef _VEC_H_
#define _VEC_H_

#include <initializer_list>
#include "vec.h"

class Vector {
private:
    double *elem;
    int sz;


public:
    Vector(int s) :elem{new double[s]}, sz{s} {
        for (int i = 0; i != s; ++i)
            elem[i] = 0;
        std::cout << "Vector()" << std::endl;
    }

    Vector(std::initializer_list<double> lst);
    
    ~Vector() { 
        delete[] elem; 
        std::cout << "~Vector()" << std::endl;
    }
   
    void push_back(double);

    double& operator[](int i);
    int size() const;

};

#endif

