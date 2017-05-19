#include <string>
#include <iostream>
#include <memory>
using namespace std;

class Product // abstract product
{
public:
    Product() {}
    virtual ~Product() {}
    virtual void setDough(const string& dough) = 0;
    virtual void setSauce(const string& sauce) = 0;
    virtual void setTopping(const string& topping) = 0;
    virtual void open() const = 0;
};

class ActualProduct : public Product
{
public:
    ActualProduct() {}
    void setDough(const string& dough) { m_dough = dough; }
    void setSauce(const string& sauce) { m_sauce = sauce; }
    void setTopping(const string& topping) { m_topping = topping; }
    void open() const {
        cout << "Product " << m_dough << " bred, " 
            << m_sauce << " and "
            << m_topping << " tops. Makes your eyes red just thinking about it." << endl;
    }
private:
    string m_dough;
    string m_sauce;
    string m_topping;
};

// abstract Builder
class ProductBuilder
{
public:
    virtual ~ProductBuilder() {};

    ActualProduct* getProduct() { return m_product; }
    void createNewProductProduct() { m_product = new ActualProduct(); }
    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildTopping() = 0;
protected:
    ActualProduct* m_product;
};

// concrete product builders
class HawaiianProductBuilder : public ProductBuilder
{
public:
    virtual ~HawaiianProductBuilder() {};
    virtual void buildDough() { m_product->setDough("cross"); }
    virtual void buildSauce() { m_product->setSauce("resin"); }
    virtual void buildTopping() { m_product->setTopping("red+leafy"); }
};

class MexicanProductBuilder : public ProductBuilder
{
public:
    virtual ~MexicanProductBuilder() {};
    virtual void buildDough() { m_product->setDough("getcha baked"); }
    virtual void buildSauce() { m_product->setSauce("hot"); }
    virtual void buildTopping() { m_product->setTopping("salami"); }
};

class Cook
{
public:
    void openProduct() { m_productBuilder->getProduct()->open(); }
    void makeProduct(ProductBuilder* pb) {
        m_productBuilder = pb;
        m_productBuilder->createNewProductProduct();
        m_productBuilder->buildDough();
        m_productBuilder->buildSauce();
        m_productBuilder->buildTopping();
    }
private:
    ProductBuilder* m_productBuilder;
};

int main()
{
    Cook cook;
    HawaiianProductBuilder hawaiianProductBuilder;
    MexicanProductBuilder  mexicanProductBuilder;

    cook.makeProduct(&hawaiianProductBuilder);
    cook.openProduct();

    cook.makeProduct(&mexicanProductBuilder);
    cook.openProduct();
}
