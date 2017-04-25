#ifndef _VECTOR_H_
#define _VECTOR_H_

// TODO:

#include <initializer_list>

// pure interface, polymorphic type
class Container {
public: // no constructor, because no data
    virtual double& operator[](int) = 0; //pure virtual function
    virtual int size() const = 0;
    virtual ~Container(){} // force destructor in subclass because of pointer access,
                           // destructor is accessed via vtbl, insuring that the correct
                           // destructor is invoked.
};

// polymorphic functions must be implemented using pointers or references
// uses vtbl to resolve correct subclass.
// we can use polymorphism to define all kinds of general operations for
// Container's, not caring about the subclass implementation.
void use(Container& c) {
    const int sz = c.size();
    for (int i = 0; i != sz; ++i)
        std::cout << c[i] << std::endl;
}

class Vector {
friend Vector operator+(const Vector& lhs, const Vector& rhs);
friend void show(const Vector &v); 

public:
    Vector() :elem{new double[4]}, sz{4} {
        std::cout << "default constructor vector(" << sz << ")" << std::endl;
    }
    
    Vector(int s) :elem{new double[s]}, sz{s} {
        for (int i = 0; i < sz; ++i) elem[i] = 0;
        std::cout << "created vector(" << sz << ")" << std::endl;
    }

    // initialize vector from a list of doubles, like Vector v = {1,2,3,4};
    Vector(std::initializer_list<double> lst) :elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())} {
        std::copy(lst.begin(), lst.end(), elem);
        std::cout << "created initializer_list vector(" << sz << ")" << std::endl;
    }

    ~Vector() { 
        std::cout << "destroyed vector(" << sz << ")" << std::endl;
        delete[] elem; 
    }

    // copy constructors are memberwise copy by default, not good enough for complex containers
    // Vector v2{v1}; // copy initializer, needs copy constructor
    Vector(const Vector& a) :elem{new double[a.sz]}, sz{a.sz} {
        for (int i = 0; i != sz; ++i) elem[i] = a.elem[i];
        std::cout << "copy constructor vector(" << sz << ")" << std::endl;
    }

    // Vector v3 = v2; // requires copy assignment operator
    Vector& operator=(const Vector& a) {
        double *p = new double[a.sz];
        for (int i = 0; i != a.sz; ++i)
            p[i] = a.elem[i];
        delete[] elem; // delete old elements
        elem = p;
        sz = a.sz;
        std::cout << "copy assignment vector(" << sz << ")" << std::endl;
        return *this;
    }

    // Move operations involve rvalues, which are values that can't be assigned to
    // so we can steal them for our use.
    Vector(Vector&& rhs) :elem{rhs.elem}, sz{rhs.sz} {
        rhs.elem = nullptr;
        rhs.sz = 0;
        std::cout << "move constructor vector(" << sz << ")" << std::endl;
    }

    Vector& operator=(Vector&& rhs) {
        if (this != &rhs) { // check for self-assignment
            delete[] elem;
            elem = rhs.elem;
            sz = rhs.sz;
            rhs.elem = nullptr; // leave rhs in a destructable state
        }
        std::cout << "move assignment vector(" << sz << ")" << std::endl;
        return *this;
    }

    double& operator[](int i) { return (elem[i]); }
    int size() const { return sz; }

private:
    double* elem;
    int sz;
};

    // v3 + v2; 
Vector operator+(const Vector& lhs, const Vector& rhs) {
    Vector sum(rhs.sz + lhs.sz);
    int i = 0;
    for (i = 0; i != rhs.sz; ++i)
        sum.elem[i] = rhs.elem[i];
    for (int j = 0; j != rhs.sz; ++i, ++j)
        sum.elem[i] = lhs.elem[i];
    return sum;
}

// v3 + v2; 
void show(const Vector& v) {
    for (int i = 0; i != v.sz; ++i)
        std::cout << "[" << i << "]=" << v.elem[i] << std::endl;
}


class Vector_container : public Container {
public:
    Vector_container(int s) : v(s) {}
    ~Vector_container() {}
    double& operator[](int i) { return v[i]; }
    int size() const { return v.size(); }
private:
    Vector v;
};


#endif
