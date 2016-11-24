#include <iostream>
#include <string>

// oop: 1. data abstraction - separate interface from implementation
//      2. inheritance - model relationships among similar types
//      3. dynamic binding - use objects of similar types and ignore how they differ

// inheritance: forms a hierarchy:
//  base class
//  derived classes

// base class
// represents undiscounted books
class Quote {
public:
    Quote() = default; //
    Quote(const std::string &book, double sales_price) :
        bookNo(book), price(sales_price) {}
    std::string isbn() const { return bookNo; } // same for all classes
    virtual double net_price(std::size_t n) const { // specific to each class, dynamic binding
        return n * price;
    }
    virtual ~Quote() = default; // dynamic binding for destructor
private:
    std::string bookNo; // ISBN
protected:
    double price = 0.0; // normal, undiscounted price
};

// represents books with quantity discount
class Bulk_quote : public Quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string&, double, std::size_t, double);
    double net_price(std::size_t n) const override;
private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};


using namespace std;

// dynamic binding, we can use the same code to process objects
// of either Quote or Bulk_quote: item needs to be reference or pointer
double print_total(ostream &os, const Quote &item, size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << " # sold: " << n 
       << " total due: " << ret << endl;

    return ret;
}


int main()
{
    Quote q;
    Bulk_quote b;
    print_total(cout, q, 1);
    print_total(cout, b, 1);
}
