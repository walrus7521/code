#include <stdexcept>
#include <iostream>
#include <memory>

using namespace std;

class AbstractProductA;
class AbstractProductB;

class AbstractFactory {
public:
    string _name;
    virtual AbstractProductA *CreateProductA() = 0;
    virtual AbstractProductB *CreateProductB() = 0;
};
 
class ConcreteFactory1 : public AbstractFactory {
public:
    AbstractProductA *CreateProductA();
    AbstractProductB *CreateProductB();
};
 
class ConcreteFactory2 : public AbstractFactory {
public:
    AbstractProductA *CreateProductA();
    AbstractProductB *CreateProductB();
};
 
class AbstractProductA {
public:
    string _name;
    virtual void Interact(AbstractProductB *a) = 0;
};
 
class AbstractProductB {
public:
    string _name;
    virtual void Interact(AbstractProductA *a) = 0;
};
 
class ProductA1 : public AbstractProductA {
public:
    ProductA1() { _name = "ProductA1"; }
    void Interact(AbstractProductB *b) {
        cout << _name << " -> " << b->_name << endl;
    }
};
 
class ProductB1 : public AbstractProductB {
public:
    ProductB1() { _name = "ProductB1"; }
    void Interact(AbstractProductA *a) {
        cout << _name << " -> " << a->_name << endl;
    }
};
 
class ProductA2 : public AbstractProductA {
public:
    ProductA2() { _name = "ProductA2"; }
    void Interact(AbstractProductB *b) {
        cout << _name << " -> " << b->_name << endl;
    }
};
 
class ProductB2 : public AbstractProductB {
public:
    ProductB2() { _name = "ProductB2"; }
    void Interact(AbstractProductA *a) {
        cout << _name << " -> " << a->_name << endl;
    }
};

AbstractProductA *ConcreteFactory1::CreateProductA() {
    _name = "Factory1 for A";
    return new ProductA1();
}
AbstractProductB *ConcreteFactory1::CreateProductB() {
    _name = "Factory1 for B";
    return new ProductB1();
}
AbstractProductA *ConcreteFactory2::CreateProductA() {
    _name = "Factory2 for A";
    return (AbstractProductA *) new ProductA2();
}
AbstractProductB *ConcreteFactory2::CreateProductB() {
    _name = "Factory2 for B";
    return (AbstractProductB *) new ProductB2();
}

class Client {
private:
    AbstractProductA *_abstractProductA;
    AbstractProductB *_abstractProductB;
public:
    Client(AbstractFactory *factory) {
      _abstractProductB = factory->CreateProductB();
      _abstractProductA = factory->CreateProductA();
    }
    void Run() {
      _abstractProductB->Interact(_abstractProductA);
    }
};
 
int main()
{
    AbstractFactory *factory1 = new ConcreteFactory1();
    Client *client1 = new Client(factory1);
    client1->Run();
 
    AbstractFactory *factory2 = new ConcreteFactory2();
    Client *client2 = new Client(factory2);
    client2->Run();
}
 
