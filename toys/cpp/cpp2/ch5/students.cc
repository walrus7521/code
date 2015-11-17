#include <iomanip>
#include <stdexcept>
#include <ios>
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include "Student_info.h"
#include "median.h"
#include "grade.h"

using std::cin;         using std::setprecision;
using std::cout;        using std::string;
using std::endl;        using std::streamsize;
using std::vector;      using std::sort;
using std::domain_error;
using std::istream;     using std::list;
using std::max;


int main()
{
    list<Student_info> students;
    Student_info record;
    string::size_type maxlen = 0;
    
    while (read(cin, record)) {
        maxlen = max(maxlen, record.name.size());
        students.push_back(record);
    }

    list<Student_info> fails = extract_fails3(students);

    students.sort(compare);

    for (list<Student_info>::const_iterator iter = students.begin();
            iter != students.end(); ++iter) {
        cout << iter->name
             << string(maxlen + 1 - iter->name.size(), ' ');
       try {
            double final_grade = grade(*iter);
            streamsize prec = cout.precision();
            cout << setprecision(3)
              << final_grade << setprecision(prec) << endl;
       } catch (domain_error e) {
           cout << e.what();
       }
    }

    cout << "failed students: " << endl;
    for (list<Student_info>::const_iterator iter = fails.begin();
            iter != fails.end(); ++iter) {
        cout << iter->name << endl;
    }

    return 0;
}
