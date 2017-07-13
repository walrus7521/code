#include <iostream>
#include <string>
#include "Sales_data.h"

using std::istream_iterator;
using std::ostream_iterator;
using std::cin;
using std::cout;

int main()
{

    Sales_data total(cin);
    double price = 0;
    if (cin) {
        while (1) {
            Sales_data trans(cin);
            if (cin) {
                if (total.isbn() == trans.isbn()) {
                    total = add(total, trans);
                } else {
                    print(cout, total); cout << std::endl;
                    total = trans;
                }
            } else {
                break;
            }
        }
        print(cout, total); cout << std::endl;
    } else {
        std::cerr << "No data?!" << std::endl;
        return -1;
    }

    return 0;
}
