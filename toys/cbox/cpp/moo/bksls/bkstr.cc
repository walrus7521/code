#include <iostream>
#include "Sales_item.h"

using std::istream_iterator;
using std::ostream_iterator;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

int main()
{
    istream_iterator<Sales_item> in_iter(cin), eof;
    ostream_iterator<Sales_item> out_iter(cout, "\n");

    Sales_item total = *in_iter++;
    if (cin >> total) {
        Sales_item trans;
        while (cin >> trans) {
            if (total.get_isbn() == trans.get_isbn())
                total += trans;
            else {
                cout << total << endl;
                total = trans;
            }
        }
        cout << total << endl;
    } else {
        // no input from user
        cerr << "No data?!" << endl;
        return -1;
    }
    return 0;
}

