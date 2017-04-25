#include <iostream>
#include <string>
#include <vector>
#include <set>

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

    // virtual function to return a dynamically allocated copy of itself
    // these members use reference qualifiers
    // define these in the derived class as well
    virtual Quote* clone() const & { return new Quote(*this); }
    virtual Quote* clone() && { return new Quote(std::move(*this)); }

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

    Bulk_quote* clone() const & override { return new Bulk_quote(*this); }
    Bulk_quote* clone() && override { return new Bulk_quote(std::move(*this)); }

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

double print_total(std::ostream &os, const Quote &item, std::size_t n);

class Basket {
public:
    // Basket uses synthesized default constructor and copy-control members
    void add_item1(const std::shared_ptr<Quote> &sale)
        { items.insert(sale); }

    // simulate virtual copy

    // these members can't just do new Quote(sale) or sale will be sliced down
    // we need to simulate a virtual copy -- see clone in Quote
    void add_item(const Quote& sale) { // copy the given object
        std::cout << "add_item copy " << std::endl;
        items.insert(std::shared_ptr<Quote>(sale.clone()));
    }
    void add_item(Quote&& sale) { // movde the given object
        std::cout << "add_item move " << std::endl;
        items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
    }

    // prints the total price for each book and the overall total for all items in basket
    double total_receipt(std::ostream& os) const {
        double sum = 0.0;
        // iter refers to first element in a batch of elements with same ISBN
        // upper_bound returns an iterator to the element just past end of that batch
        for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)) {
            // we know there's at least one element with this key in the basket
            // print the line item for this book
            sum += print_total(os, **iter, items.count(*iter));
        }
        os << "Total sale: " << sum << std::endl;
        return sum;
    }
private:
    // function to compare shared_ptrs needed by the multiset member
    static bool compare(const std::shared_ptr<Quote> &lhs,
                        const std::shared_ptr<Quote> &rhs)
        { return lhs->isbn() < rhs->isbn(); }
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};
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

    vector<Quote> qv1;
    qv1.push_back(Quote("111-111-11", 12.95));
    qv1.push_back(Quote("222-222-22", 13.95));
    qv1.push_back(Quote("333-333-33", 14.95));
    double avg = 0.0;
    int count = 0;
    for (const auto qvi : qv1) {
        cout << "qv: " << qvi.isbn() << endl;
        avg += qvi.net_price(1);
        count++;
    }
    cout << "avg price of qv1: " << avg / count << endl;
    
    vector<shared_ptr<Quote>> qvp;
    qvp.push_back(make_shared<Quote>("111-111-11", 12.95));
    qvp.push_back(make_shared<Quote>("222-222-22", 13.95));
    qvp.push_back(make_shared<Quote>("133-333-33", 14.95));
    for (const auto qvi : qvp) {
        cout << "qp: " << qvi->isbn() << endl;
        avg += qvi->net_price(1);
        count++;
    }
    cout << "avg price of qv1: " << avg / count << endl;

    
    cout << "Testing basket - begin" << endl;
    Basket bsk1;
    bsk1.add_item1(make_shared<Quote>("123", 45));
    bsk1.add_item1(make_shared<Bulk_quote>("456", 35, 3, .15));
    cout << "total1: " << bsk1.total_receipt(cout) << endl;

    Basket bsk2;
    bsk2.add_item(Quote("123", 45));
    bsk2.add_item(Bulk_quote("456", 35, 3, .15));
    bsk2.add_item(Bulk_quote("789", 25, 4, .12));
    cout << "total2: " << bsk2.total_receipt(cout) << endl;



    cout << "Testing basket - end" << endl;
}
