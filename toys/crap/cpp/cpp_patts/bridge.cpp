#include <iostream>
#include <memory>
using namespace std;

// abstraction, refined abstraction, implementor, 
// concrete implementors
class Implementor {
public:
    Implementor() { cout << "Implementor ctor" << endl; }
    virtual void OperationImpl() { 
        cout << "Implementor OperationImpl" << endl; }
};

class ConcreteImplementor: public Implementor {
public:
    ConcreteImplementor(): Implementor() { 
        cout << "ConcreteImplementor ctor" << endl; }
    virtual void OperationImpl() override {
        cout << "ConcreteImplementor OperationImpl" << endl;
    }
};

class Abstraction {
public:
    Abstraction(){ 
        cout << "Abstraction ctor" << endl;
        imp_ = make_shared<Implementor>();
    }
    virtual void Operation() {  // the bridge
        cout << "Abstraction Operation" << endl;
        imp_->OperationImpl(); }
protected:
    shared_ptr<Implementor> imp_;
};

class RefinedAbstraction: public Abstraction {
public:
    RefinedAbstraction() { 
        imp_ = make_shared<ConcreteImplementor>();
    }
};

int main() {
  shared_ptr<Abstraction> abs1(new Abstraction());
  shared_ptr<Abstraction> abs2(new RefinedAbstraction());
  abs1->Operation();
  abs2->Operation();
}
