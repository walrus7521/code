#include <iostream>
#include <string>
#include "Sales_data.h"


using namespace std;

int main()
{
    string null_book = "9-999-99999-9";


    Sales_data data1(cin), data2;
    print(cout, data1);
    cout << endl;

    //data2.combine(null_book); // converting constructor
    //data2.combine("9-999-99999-9"); // illegal double conversion
    ///data2.combine(string("9-999-99999-9")); // okay - nope explicit
    //data2.combine(Sales_data("9-999-99999-9")); // okay - nope explicit
    //data2.combine(cin); // okay - nope explicit

    print(cout, data2);
    cout << endl;

    return 0;
   
}

