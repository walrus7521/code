#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>
#include "Sales_data.h"


using namespace std;


void reportResults(istream &in, ostream &os,
        const vector<vector<Sales_data>> &files)
{
    string s; // book to look for
    while (in >> s) {
        auto trans = findBook(files, s);
        if (trans.empty()) {
            cout << s << " not found in any stores" << endl;
            continue;
        }
        for (const auto &store : trans) { // for every store with a sale
            // get<n> returns the specified member from the tuple in store
            auto sum = accumulate(get<1>(store), get<2>(store), Sales_data(s));
            os << "store " << get<0>(store) << " sales: "
               << sum << endl;
        }
    }

}

int main()
{
    string null_book = "9-999-99999-9";
    ifstream in("data");

    Sales_data data1(in), data2;
    print(cout, data1);
    cout << endl;

    //data2.combine(null_book); // converting constructor
    //data2.combine("9-999-99999-9"); // illegal double conversion
    ///data2.combine(string("9-999-99999-9")); // okay - nope explicit
    //data2.combine(Sales_data("9-999-99999-9")); // okay - nope explicit
    //data2.combine(in); // okay - nope explicit

    print(cout, data2);
    cout << endl;

    return 0;
   
}

