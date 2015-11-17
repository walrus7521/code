#include <iostream>
#include <string>

struct Sales_data {
    std::string bookNo;
    unsigned units_sold;
    double revenue;
};

int main()
{
    Sales_data total, trans;
    double price = 0;

    if (std::cin >> total.bookNo >> total.units_sold >> price) {
        total.revenue = total.units_sold * price;
        while (std::cin >> trans.bookNo >> trans.units_sold >> price) {
            trans.revenue = trans.units_sold * price;
            if (total.bookNo == trans.bookNo) {
                total.revenue    += trans.revenue;
                total.units_sold += trans.units_sold;
            } else {
                std::cout << total.bookNo << "\t" << total.units_sold << "\t" << total.revenue << "\t" << total.revenue/total.units_sold << std::endl;
                total.bookNo = trans.bookNo;
                total.revenue = trans.revenue;
                total.units_sold = trans.units_sold;

                trans.bookNo.clear();
                trans.revenue = 0.0;
                trans.units_sold = 0;
            }
        }
        std::cout << total.bookNo << "\t" << total.units_sold << "\t" << total.revenue << "\t" << total.revenue/total.units_sold << std::endl;
    } else {
        std::cerr << "No data?!" << std::endl;
        return -1;
    }

    return 0;
}
