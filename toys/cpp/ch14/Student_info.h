#ifndef _STUDENT_INFO_H
#define _STUDENT_INFO_H

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "Handle.h"
#include "Grad.h"
#include "Core.h"

class Student_info {
public:
    Student_info() { }
    Student_info(std::istream& is) { read(is); }

    std::istream& read(std::istream&);

    std::string name() const {
        if (cp) return cp->name();
        else throw std::runtime_error("uninitialized Student");
    }

    double grade() const {
        if (cp) return cp->grade();
        else throw std::runtime_error("uninitialized Student");
    }

    static bool compare(const Student_info& s1,
                        const Student_info& s2) {
        return s1.name() < s2.name();
    }

private:
    Handle<Core> cp;
};

std::istream& Student_info::read(std::istream& is)
{
    char ch;
    is >> ch;

    std::cout << "enter Student_info::read(istream&): " << ch << std::endl;
    if (ch == 'U') {
        std::cout << "instantiating a Core..\n";
        cp = new Core(is);
    } else {
        std::cout << "instantiating a Grad..\n";
        cp = new Grad(is);
    }
    return is;
}

#endif

