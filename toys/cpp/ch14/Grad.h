#ifndef _GRAD_H_
#define _GRAD_H_

#include <iostream>
#include <algorithm>
#include "Core.h"

class Grad: public Core {
public:
    Grad(): thesis(0) { /*std::cerr << "Grad::Grad()\n";*/ }
    Grad(std::istream& is) { /*std::cerr << "Grad::Grad(istream&)\n";*/  read(is); }
    double grade() const;
    std::istream& read(std::istream&);
protected:
    Grad* clone() const { return new Grad(*this); }
private:
    double thesis;
};

double Grad::grade() const
{
    return std::min(Core::grade(), thesis);
}

std::istream& Grad::read(std::istream& in)
{
    read_common(in);
    in >> thesis;
    read_hw(in, homework);
    return in;
}

#endif
