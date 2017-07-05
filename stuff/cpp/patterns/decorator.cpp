#include <iostream>

using namespace std;

class Component { // abstract
public:
    virtual void Operation() = 0;
};
 
class ConcreteComponent : public Component {
public:
    void Operation() { // override
        cout << "ConcreteComponent.Operation()" << endl;
    }
};
 
class Decorator : public Component { // abstract 
protected:
    Component *_component;
public: 
    void SetComponent(Component *component) {
        _component = component;
    }
    void Operation() { // override 
        if (_component != NULL) {
            _component->Operation();
        }
    }
};
 
class ConcreteDecoratorA : public Decorator {
public:
    void Operation() { // override 
        Decorator::Operation();
        cout << "ConcreteDecoratorA.Operation()" << endl;
    }
};
 
class ConcreteDecoratorB : public Decorator {
public:
    void Operation() { // override 
        Decorator::Operation();
        cout << "ConcreteDecoratorB.Operation()" << endl;
        AddedBehavior();
    }
    void AddedBehavior() { cout << "yo added" << endl; }
};

int main()
{
    // Create ConcreteComponent and two Decorators
    ConcreteComponent *c = new ConcreteComponent();
    ConcreteDecoratorA *d1 = new ConcreteDecoratorA();
    ConcreteDecoratorB *d2 = new ConcreteDecoratorB();
 
    // Link decorators
    d1->SetComponent(c);
    d2->SetComponent(d1);
 
    d2->Operation();
}
 
