#include <iostream>
#include <string>

using namespace std;

class Prototype
{
protected:
    string _id;
public: 
    Prototype(string id) {
        _id = id;
    }
    string GetId() {
        return _id;
    }
    virtual Prototype *Clone() = 0;
};
 
class ConcretePrototype1 : public Prototype
{
public:
    ConcretePrototype1(string id) : Prototype(id){}
    // Returns a shallow copy
    Prototype *Clone() {
        Prototype *c = new ConcretePrototype1("II");
        *c = *this;
        return c;
    }
};
 
class ConcretePrototype2 : public Prototype
{
public:
    ConcretePrototype2(string id) : Prototype(id){}
    // Returns a shallow copy
    Prototype *Clone() {
        Prototype *c = new ConcretePrototype2("II");
        *c = *this;
        return c;
    }
};

int main()
{
    // Create two instances and clone each
    ConcretePrototype1 *p1 = new ConcretePrototype1("I");
    ConcretePrototype1 *c1 = (ConcretePrototype1 *) p1->Clone();
    cout << "Cloned: " << c1->GetId() << endl;

    ConcretePrototype2 *p2 = new ConcretePrototype2("II");
    ConcretePrototype2 *c2 = (ConcretePrototype2 *) p2->Clone();
    cout << "Cloned: " << c2->GetId() << endl;
}
 
