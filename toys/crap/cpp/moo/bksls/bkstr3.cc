#include <iostream>
#include <string>
#include "Sales_data.h"

int main()
{
    Sales_data total(std::cin);
    double price = 0;
    if (std::cin) {
        while (1) {
            Sales_data trans(std::cin);
            if (std::cin) {
                if (total.isbn() == trans.isbn()) {
                    total = add(total, trans);
                } else {
                    print(std::cout, total); std::cout << std::endl;
                    total = trans;
                }
            } else {
                break;
            }
        }
        print(std::cout, total); std::cout << std::endl;
    } else {
        std::cerr << "No data?!" << std::endl;
        return -1;
    }

    return 0;
}
