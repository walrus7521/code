#include <iostream>
#include <string>

// use visitors on composite or collections
// double dispatch -> invoked method issues callback

using namespace std;

class Element;

// abstract interface visitor class
class Visitor
{
public:
    virtual void visit(Element *e) = 0;
protected:
    Visitor(){cout << "ctor - Visitor" << endl;}
};

// abstract element class with an accept(Visitor) method
class Element
{
public:
    virtual void accept(Visitor &v) = 0;
    virtual string get() = 0;
protected:
    Element(){cout << "ctor - Element" << endl;}
};

// concrete element classes
class ConcreteElementA: public Element
{
public:
    ConcreteElementA(){}
    virtual void accept(Visitor &v) { v.visit(this); }
    virtual string get() { return "ConcreteElementA"; }
};

class ConcreteElementB: public Element
{
public:
    ConcreteElementB(){}
    virtual void accept(Visitor &v) { v.visit(this); }
    virtual string get() { return "ConcreteElementB"; }
};

// concrete visitor classes for each "operation" to do on "elements"
class ConcreteVisitor1: public Visitor
{
    virtual void visit(Element *e) { cout << 
        "do Visit 1 on " << e->get() << '\n'; }
};

class ConcreteVisitor2: public Visitor
{
    virtual void visit(Element *e) { cout << 
        "do Visit 2 on " << e->get() << '\n'; }
};

int main()
{
  Element *list[] = { new ConcreteElementA(), new ConcreteElementB() };
  ConcreteVisitor1 v1; // Client creates "visitor" objects
  ConcreteVisitor2 v2;
  for (int i = 0; i < 2; i++) list[i]->accept(v1); // pass visitor to accept
  for (int i = 0; i < 2; i++) list[i]->accept(v2);
}

