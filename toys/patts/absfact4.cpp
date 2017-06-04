#include <stdexcept>
#include <iostream>
#include <memory>

using namespace std;

class AbstractProductA;
class AbstractProductB;

class AbstractFactory
{
protected:
public:
    string _name;
    virtual AbstractProductA *CreateProductA() = 0;
    virtual AbstractProductB *CreateProductB() = 0;
};
 
class ConcreteFactory1 : public AbstractFactory
{
public:
    AbstractProductA *CreateProductA();
    AbstractProductB *CreateProductB();
};
 
class ConcreteFactory2 : public AbstractFactory
{
public:
    AbstractProductA *CreateProductA();
    AbstractProductB *CreateProductB();
};
 
//class ProductA1;
//class ProductB1;
//class ProductA2;
//class ProductB2;

class AbstractProductA
{
public:
    string _name;
};
 
class AbstractProductB
{
public:
    string _name;
    virtual void Interact(AbstractProductA *a) = 0;
};
 
class ProductA1 : public AbstractProductA
{
};
 
class ProductB1 : public AbstractProductB
{
public:
    void Interact(AbstractProductA *a)
    {
        cout << "Product B1 -> " << a->_name << endl;
        cout << a->_name << endl;
    }
};
 
class ProductA2 : public AbstractProductA
{
};
 
class ProductB2 : public AbstractProductB
{
public:
    void Interact(AbstractProductA *a)
    {
        cout << "Product B2 -> " << a->_name << endl;
    }
};
 

AbstractProductA *ConcreteFactory1::CreateProductA()
{
    _name = "A1";
    return new ProductA1();
}
AbstractProductB *ConcreteFactory1::CreateProductB()
{
    _name = "B1";
    return new ProductB1();
}

AbstractProductA *ConcreteFactory2::CreateProductA()
{
    _name = "A2";
    return (AbstractProductA *) new ProductA2();
}
AbstractProductB *ConcreteFactory2::CreateProductB()
{
    _name = "B2";
    return (AbstractProductB *) new ProductB2();
}

class Client
{
private:
    AbstractProductA *_abstractProductA;
    AbstractProductB *_abstractProductB;
public:
    // Constructor
    Client(AbstractFactory *factory)
    {
      _abstractProductB = factory->CreateProductB();
      _abstractProductA = factory->CreateProductA();
    }
 
    void Run()
    {
      _abstractProductB->Interact(_abstractProductA);
    }
};
 
int main()
{
    // Abstract factory #1
    AbstractFactory *factory1 = new ConcreteFactory1();
    Client *client1 = new Client(factory1);
    client1->Run();
 
    // Abstract factory #2
    AbstractFactory *factory2 = new ConcreteFactory2();
    Client *client2 = new Client(factory2);
    client2->Run();
 
}
 
