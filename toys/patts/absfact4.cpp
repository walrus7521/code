#include <stdexcept>
#include <iostream>
#include <memory>


class AbstractFactory
{
public:
    AbstractProductA *CreateProductA() = 0;
    AbstractProductB *CreateProductB() = 0;
};
 
class ConcreteFactory1 : public AbstractFactory
{
public:
    AbstractProductA *CreateProductA()
    {
      return new ProductA1();
    }
    AbstractProductB *CreateProductB()
    {
      return new ProductB1();
    }
};
 
class ConcreteFactory2 : public AbstractFactory
{
    AbstractProductA *CreateProductA()
    {
      return new ProductA2();
    }
    AbstractProductB *CreateProductB()
    {
      return new ProductB2();
    }
};
 
class AbstractProductA
{
};
 
class AbstractProductB
{
public:
    void Interact(AbstractProductA a) = 0;
};
 
class ProductA1 : public AbstractProductA
{
};
 
class ProductB1 : public AbstractProductB
{
public:
    void Interact(AbstractProductA a)
    {
      Console.WriteLine(this.GetType().Name +
        " interacts with " + a.GetType().Name);
    }
};
 
class ProductA2 : public AbstractProductA
{
};
 
class ProductB2 : public AbstractProductB
{
    public override void Interact(AbstractProductA a)
    {
      Console.WriteLine(this.GetType().Name +
        " interacts with " + a.GetType().Name);
    }
};
 
class Client
{
    private AbstractProductA _abstractProductA;
    private AbstractProductB _abstractProductB;
 
    // Constructor
    public Client(AbstractFactory factory)
    {
      _abstractProductB = factory.CreateProductB();
      _abstractProductA = factory.CreateProductA();
    }
 
    public void Run()
    {
      _abstractProductB.Interact(_abstractProductA);
    }
};
 
int main()
{
    // Abstract factory #1
    //AbstractFactory factory1 = new ConcreteFactory1();
    //Client client1 = new Client(factory1);
    //client1.Run();
 
    // Abstract factory #2
    //AbstractFactory factory2 = new ConcreteFactory2();
    //Client client2 = new Client(factory2);
    //client2.Run();
 
}
 
