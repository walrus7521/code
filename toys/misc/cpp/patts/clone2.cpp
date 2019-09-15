#include <iostream>
#include <memory>

class Product {
    int m_i = 1;
    std::shared_ptr<int> m_p = std::make_shared<int>(3);
public:
    // interface
    int i() const { return m_i; }
    std::shared_ptr<const int> p() const { return m_p; }
    virtual std::shared_ptr<const double> p2() const = 0;
    virtual Product* clone() const = 0;
protected:
    // implementation fc which can be
    // called from derived classes
    static void clone_imp(Product *product) {
        // update the member variables you choose
        product->m_p = std::make_shared<int>(*product->m_p);
    }
};

// derived class
class Product2: public Product {
    std::shared_ptr<double> m_p2 = 
        std::make_shared<double>(5.2);
public:
    std::shared_ptr<const double> p2() const { return m_p2; }
    // clone product
    virtual Product2* clone() const {
        // use the default copy constructor
        // to copy all member variables
        Product2* product = new Product2(*this);
        // update the member variables
        clone_imp(product);
        return product;
    }
protected:
    // implementation fc which can be
    // called from derived classes
    static void clone_imp(Product2* product) {\
        // update the member variables from the base class
        Product::clone_imp(product);
        // update the member variables you choose
        product->m_p2 = std::make_shared<double>(*product->m_p2);
    }
};

// print functions helper to have cleaner programs
template <typename T1, typename T2>
void print(const T1& t1, const T2& t2) {
    std::cout << t1 << t2 << std::endl;
}

int main() {
    Product *product = new Product2();
    Product *clone = product->clone();

    print("Product: m_i =", product->i());
    print("Cloned : m_i =", clone  ->i());
    print("Product: m_p =", product->p());
    print("Cloned : m_p =", clone  ->p());
    print("Product:*m_p =", *product->p());
    print("Cloned :*m_p =", *clone  ->p());
    print("Product: m_p2=",  product->p2());
    print("Cloned : m_p2=",  clone  ->p2());
    print("Product:*m_p2=", *product->p2());
    print("Cloned :*m_p2=", *clone  ->p2());
    return 0;
}
