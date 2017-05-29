#include <string>
#include <iostream>
#include <memory>
using namespace std;

class Product // abstract product
{
public:
    Product() {}
    virtual ~Product() {}
    virtual void Create() = 0;
};

class ConcreteProduct : public Product
{
public:
    ConcreteProduct() {}
    void Create() {}
};

class Builder // abstract builder
{
public:
    virtual ~Builder() {};
    ConcreteProduct* getProduct() { return m_product; }
    virtual void Construct() = 0;
protected:
    ConcreteProduct* m_product;
};

class ConcreteBuilder : public Builder
{
public:
    virtual ~ConcreteBuilder() {};
    virtual void Construct() { m_product->Create(); }
};

class Director
{
public:
    void openProduct() { m_productBuilder->getProduct()->Create(); }
    void makeProduct(Builder* pb) {
        m_productBuilder = pb;
        m_productBuilder->Construct();
    }
private:
    Builder* m_productBuilder;
};

int main()
{
    Director dir;
    ConcreteBuilder builder;

    dir.makeProduct(&builder);
    dir.openProduct();

}
