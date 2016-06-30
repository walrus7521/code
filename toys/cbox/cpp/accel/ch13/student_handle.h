#ifndef _STUDENT_HANDLE_H
#define _STUDENT_HANDLE_H

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "grad.h"
#include "core.h"

class Student_info {
public:
    Student_info(): cp(0) { /*std::cerr << "Student_info::Student_info()\n";*/ }
    Student_info(std::istream& is): cp(0) { /*std::cerr << "Student_info::Student_info(istream&)\n";*/ read(is); }
    Student_info(const Student_info&);
    Student_info& operator=(const Student_info&);
    ~Student_info() { delete cp; }

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
    Core *cp;
};

Student_info::Student_info(const Student_info& s): cp(0)
{
    /*std::cerr << "Student_info::Student_info(const Student_info&)\n";*/
    if (s.cp) cp = s.cp->clone();
}

Student_info& Student_info::operator=(const Student_info& s)
{
    if (&s != this) {
        delete cp;
        if (s.cp)
            cp = s.cp->clone();
        else
            cp = 0;
    }
    return *this;
}

std::istream& Student_info::read(std::istream& is)
{
    delete cp;

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

