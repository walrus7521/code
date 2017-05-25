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
class This: public Element
{
public:
    This(){}
    virtual void accept(Visitor &v) { v.visit(this); }
    virtual string get() { return "This"; }
};

class That: public Element
{
public:
    That(){}
    virtual void accept(Visitor &v) { v.visit(this); }
    virtual string get() { return "That"; }
};

// concrete visitor classes for each "operation" to do on "elements"
class UpVisitor: public Visitor
{
    virtual void visit(Element *e) { cout << "do Up on " << e->get() << '\n'; }
};

class DownVisitor: public Visitor
{
    virtual void visit(Element *e) { cout << "do Down on " << e->get() << '\n'; }
};

int main()
{
  Element *list[] = { new This(), new That() };
  UpVisitor up; // Client creates "visitor" objects
  DownVisitor down;
  for (int i = 0; i < 2; i++) list[i]->accept(up); // pass visitor to accept
  for (int i = 0; i < 2; i++) list[i]->accept(down);
}
