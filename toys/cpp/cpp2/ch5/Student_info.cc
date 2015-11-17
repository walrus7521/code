#include <iostream>
#include "Student_info.h"
#include "grade.h"

using std::istream; using std::list; using std::vector;

bool compare(const Student_info& x, const Student_info& y)
{
    return x.name < y.name;
}

istream& read_hw(istream& in, vector<double>& hw)
{
    if (in) {
        hw.clear();

        double x;
        while (in >> x)
            hw.push_back(x);
        
        in.clear();
    }
    return in;
}

istream& read(istream& is, Student_info& s)
{
    is >> s.name >> s.midterm >> s.final;
    read_hw(is, s.homework);
    return is;
}

list<Student_info> extract_fails(list<Student_info>& students)
{
    list<Student_info> pass, fail;

    for (list<Student_info>::const_iterator iter = students.begin();
            iter != students.end(); ++iter) {
        if (fgrade(*iter))
            fail.push_back(*iter);
        else
            pass.push_back(*iter);
    }
    students = pass;
    return fail;
}

#if 0
list<Student_info> extract_fails2(list<Student_info>& students)
{
    list<Student_info> fail;
    list<Student_info>::size_type i = 0;

    while (i != students.size()) {
        if (fgrade(students[i])) {
            fail.push_back(students[i]);
            students.erase(students.begin() + i);
        } else
            ++i;
    }
    return fail;
}
#endif

list<Student_info> extract_fails3(list<Student_info>& students)
{
    list<Student_info> fail;

    list<Student_info>::iterator si = students.begin(); 
    while (si != students.end()) {
        if (fgrade(*si)) {
            fail.push_back(*si);
            si = students.erase(si);
        } else
            ++si;
    }
    return fail;
}

