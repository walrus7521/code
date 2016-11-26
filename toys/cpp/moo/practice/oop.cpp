#include <iostream>
#include <string>

// oop: 1. data abstraction - separate interface from implementation
//      2. inheritance - model relationships among similar types
//      3. dynamic binding - use objects of similar types and ignore how they differ
//  note: dynamic binding only happens when a virtual function is called through
//        a pointer or reference.  this is because the static type can differ
//        from the dynamic type, so type resolution happens at run-time.

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
    virtual double net_price(std::size_t cnt) const { // specific to each class, dynamic binding
        std::cout << "Quote::net_price()" << std::endl;
        return cnt * price;
    }
    virtual ~Quote() = default; // dynamic binding for destructor
    static int num_instances;
private:
    std::string bookNo; // ISBN
protected:
    double price = 0.0; // normal, undiscounted price
};
int Quote::num_instances = 0;


// abstract base classes - pure virtual functions
// enforce a design intent using pure virtual functions
// define an abstract base class -- an example of refactoring
class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string& book, double price,
            std::size_t qty, double disc) :
        Quote(book, price), quantity(qty), discount(disc) {
            std::cout << "Disc_quote: ctor args" << std::endl;
        }

    double net_price(std::size_t) const = 0; // pure virtual
protected:
    std::size_t quantity = 0; // purchase size for the discount to apply
    double discount = 0.0; // fractional discount to apply
};


// represents books with quantity discount
class Bulk_quote : public Disc_quote {
public:
    // the using will inherit all constructors from Disc_quote
    using Disc_quote::Disc_quote; // inherit Disc_quote's constructors
    // no need for the constructors below

    //Bulk_quote() = default;
    // initializing base class using it's constructor
    //Bulk_quote(const std::string& book, double price, std::size_t qty, double disc) :
    //    Disc_quote(book, price, qty, disc) {
    //        std::cout << "Bulk_quote: ctor args" << std::endl;
    //        //Quote::num_instances++;
    //    }

    double net_price(std::size_t cnt) const override {
        std::cout << "Bulk_quote::net_price()" << std::endl;
        if (cnt >= quantity) {
            std::cout << "you got a discount, qty: " << quantity << " disc: " << discount << std::endl;
            return cnt * (1 - discount) * price;
        } else {
            return cnt * price;
        }
    }
private:
    //std::size_t min_qty = 0;
    //double discount = 0.0;
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
    Bulk_quote b("123-456-78", 39.95, 4, 0.2);
    Quote *baseP = &b;
    print_total(cout, q, 1);
    print_total(cout, b, 4);
    cout << "num quotes: " << Quote::num_instances << endl;
    double dis = baseP->net_price(42);
    cout << "dis: " << dis << endl;
    double undis = baseP->Quote::net_price(42);
    cout << "undis: " << undis << endl;

}
