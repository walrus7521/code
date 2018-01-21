#include <stdexcept>
#include <iostream>
#include <memory>

// derived from: https://en.wikibooks.org

using namespace std;

class Product {
public:
    virtual int getPrice() const = 0;
    // without this, no destructor for derived Product's will be called.
    virtual ~Product() {};  
};

class Widget : public Product {
public:
    virtual int getPrice() const { return 850; };
    virtual ~Widget() {};
};

class Whosit : public Product {
public:
    virtual int getPrice() const { return 1050; };
    virtual ~Whosit() {};
};

class Flotchy : public Product {
public:
    virtual int getPrice() const { return 1150; };
    virtual ~Flotchy() {};
};

class ProductFactory {
public:
    enum ProductType {
        WidgetType,
        WhositType,
        FlotchyType
    };

    static unique_ptr<Product> createProduct(ProductType productType) {
        switch (productType) {
        case WidgetType:  return make_unique<Widget>();
        case WhositType:  return make_unique<Whosit>();
        case FlotchyType: return make_unique<Flotchy>();
        }
        throw "invalid product type.";
    }
};

void product_information(ProductFactory::ProductType productType)
{
    unique_ptr<Product> product = 
        ProductFactory::createProduct(productType);
    cout << "Price of " << productType << " is " << 
        product->getPrice() << std::endl;
}

int main()
{
    product_information(ProductFactory::WidgetType);
    product_information(ProductFactory::WhositType);
    product_information(ProductFactory::FlotchyType);
}

