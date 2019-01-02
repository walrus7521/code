#include <iostream>
#include <memory>

// client, target, adaptee, adapter

using namespace std;

// Desired interface
class Target
{
public:
    Target(){ cout << "Target ctor" << endl; }
    virtual void Request() = 0;
private:
};

// Legacy component
class Adaptee
{
public:
    Adaptee(){}
    void SpecificRequest() { cout << 
        "Adaptee SpecificRequest" << endl; }
private:
};

// Adapter wrapper - use private inheritance or composition
class Adapter: public Target, private Adaptee
{
public:
    Adapter() : Target() { cout << "Adapter ctor" << endl; }
    virtual void Request()
    {
        cout << "Adapter Request" << endl;
        SpecificRequest();
    }
private:
};

int main()
{
  shared_ptr<Target> target(new Adapter());
  target->Request();
}

