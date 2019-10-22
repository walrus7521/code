#include <iostream>
#include <memory>

// all classes public to keep it simple

class Product {
public:
    int m_i = 1;
    std::shared_ptr<int> m_p = std::make_shared<int>(3);
    Product *clone() const {
        // use default copy constructor
        Product *product = new Product(*this);
        product->m_p = std::make_shared<int>(*m_p);
        return product;
    }
};

// create template print
template <typename T1, typename T2>
void print(const T1& t1, const T2& t2) {
    std::cout << t1 << t2 << std::endl;
}

int main() {
    Product *product = new Product();
    Product *clone = product->clone();

    print("product: m_i=", product->m_i);
    print("clone:   m_i=", clone->m_i);
}
