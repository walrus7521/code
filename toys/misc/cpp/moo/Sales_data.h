#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>
#include <iostream>
#include <vector>
#include <tuple>

class Sales_data {
friend std::istream &read(std::istream &is, Sales_data &item);
friend std::ostream &print(std::ostream &os, const Sales_data &item);
friend Sales_data add(const Sales_data &lhs, const Sales_data &rhs);
public:
    Sales_data() = default;
    Sales_data(const std::string &s, unsigned n, double p) :
        bookNo(s), units_sold(n), revenue(p*n) {}
    Sales_data(const std::string &s) : bookNo(s) {}
    Sales_data(std::istream& is) { read(is, *this); }
    std::string isbn() const { return bookNo; }
    Sales_data &combine(const Sales_data& rhs) 
    {
        units_sold += rhs.units_sold;
        revenue += rhs.revenue;
        return *this;
    }

    Sales_data& operator+(const Sales_data& rhs) {
        std::cout << "Sales_data: +" << std::endl;
        Sales_data &sum = *this;
        sum.units_sold += rhs.units_sold;
        sum.revenue += rhs.revenue;
        return sum;
    }
 
    //Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs) {
    //    Sales_data sum = lhs;
    //    sum += rhs;
    //    return sum;
    //}

private:
    double avg_price() const 
        { return units_sold ? revenue/units_sold : 0; }
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

std::istream &read(std::istream &is, Sales_data &item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

using namespace std;
typedef tuple<vector<Sales_data>::size_type,
              vector<Sales_data>::const_iterator,
              vector<Sales_data>::const_iterator> matches;


bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return (lhs.isbn() < rhs.isbn());
}


vector<matches>
findBook(const vector<vector<Sales_data>> &files,
         const string &book)
{
    vector<matches> ret;
    // for each store find the range of matching books, if any
    for (auto it = files.cbegin(); it != files.cend(); ++it) {
        // find the range of Sales_data that have the same ISBN
        auto found = equal_range(it->cbegin(), it->cend(),
                book, compareIsbn);
        if (found.first != found.second) { // this store had sales
            ret.push_back(make_tuple(it - files.cbegin(),
                        found.first, found.second));
        }
    }
    return ret;
}
#endif
