#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <iostream>
#include <string>

class Sales_data;
std::istream &read(std::istream &is, Sales_data &item);

class Sales_data {

friend Sales_data add(const Sales_data &lhs, const Sales_data &rhs);
friend std::ostream &print(std::ostream &os, const Sales_data &item);
friend std::istream &read(std::istream &is, Sales_data &item);

public:
    Sales_data(const std::string &s, unsigned n, double p):
        bookNo(s), units_sold(n), revenue(p*n) {}
    Sales_data() : Sales_data("", 0, 0) {} //= default;
    explicit Sales_data(const std::string &s) : Sales_data(s, 0, 0) {}
    explicit Sales_data(std::istream &is) : Sales_data() { read(is, *this); }
    std::string isbn() const { return bookNo; } // const modifies the this
    Sales_data& combine(const Sales_data&);

private:
    double avg_price() const; // const modifies the this
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

double Sales_data::avg_price() const {
    if (units_sold)
        return revenue / units_sold;
    else
        return 0;
}

Sales_data& Sales_data::combine(const Sales_data& rhs) {
    units_sold += rhs.units_sold;
    revenue    += rhs.revenue;
    return *this;
}

std::istream &read(std::istream &is, Sales_data &item) {
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item) {
    os << item.isbn() << "\t" << item.units_sold << "\t" 
       << item.revenue << "\t" << item.avg_price();
    return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

#endif
