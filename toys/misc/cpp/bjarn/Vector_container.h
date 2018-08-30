#ifndef _VECTOR_CONTAINER_H_
#define _VECTOR_CONTAINER_H_


#include <iostream>
#include "Container.h"
#include "vec.h"

class Vector_container : public Container {
private:
    Vector v;
public:
    Vector_container(int s) : v(s){}
    ~Vector_container(){}

    double& operator[](int i) {return v[i]; }
    int size() const { return v.size(); }

};


#endif
