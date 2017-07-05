#include <iostream>

using namespace std;

class Product {};
class ConcreteProductA : public Product {
public:
    ConcreteProductA() { cout << "Created ConcreteProductA" << endl; }
};
class ConcreteProductB : public Product {
public:
    ConcreteProductB() { cout << "Created ConcreteProductB" << endl; }
};
 
class Creator {
public:
    virtual Product *FactoryMethod() = 0;
};
 
class ConcreteCreatorA : public Creator {
public:
    Product *FactoryMethod() {
        return new ConcreteProductA();
    }
};
 
class ConcreteCreatorB : public Creator {
public:
    Product *FactoryMethod() {
        return new ConcreteProductB();
    }
};

int main()
{
    Creator *creators[2];
    Creator *c;
 
    creators[0] = new ConcreteCreatorA();
    creators[1] = new ConcreteCreatorB();
 
    for (auto& c : creators) {
        Product *product = c->FactoryMethod();
    }
}
 
