#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include "student.h"

using std::istream;
using std::cin;

//void read_hw(istream& in, vector<double> hw)
//{
//}

istream& Student_info::read(istream& in)
{
    in >> n >> midterm >> final;
    //read_hw(in, homework);
    return in;
}

double Student_info::grade() const
{
    return 42.0;
}

bool compare(const Student_info& x, const Student_info& y)
{
    return x.name() < y.name();
}


