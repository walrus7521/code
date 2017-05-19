// https://sourcemaking.com/design_patterns/visitor/cpp/2

#include <iostream>
#include <string>
using namespace std;

class This; class That; class TheOther;

// create visitor abstract class
class Visitor
{
public:
    virtual void visit(This *e) = 0;
    virtual void visit(That *e) = 0;
    virtual void visit(TheOther *e) = 0;
};

// create virtual element class with an accept(Visitor) method
class Element
{
public:
    virtual void accept(class Visitor &v) = 0;
};

class This: public Element
{
public:
     virtual void accept(Visitor &v) { v.visit(this); }
    string thiss() { return "This"; }
};

class That: public Element
{
public:
    virtual void accept(Visitor &v) { v.visit(this); }
    string that() { return "That"; }
};

class TheOther: public Element
{
public:
    virtual void accept(Visitor &v) { v.visit(this); }
    string theOther() { return "TheOther"; }
};

// Create a "visitor" derived class for each "operation" to do on "elements"
class UpVisitor: public Visitor
{
    virtual void visit(This *e) { cout << "do Up on " + e->thiss() << '\n'; }
    virtual void visit(That *e) { cout << "do Up on " + e->that() << '\n'; }
    virtual void visit(TheOther *e) { cout << "do Up on " + e->theOther() << '\n'; }
};

class DownVisitor: public Visitor
{
    virtual void visit(This *e) { cout << "do Down on " + e->thiss() << '\n'; }
    virtual void visit(That *e) { cout << "do Down on " + e->that() << '\n'; }
    virtual void visit(TheOther *e) { cout << "do Down on " + e->theOther() << '\n'; }
};

int main()
{
  Element *list[] = { new This(), new That(), new TheOther() };
  UpVisitor up; // Client creates "visitor" objects
  DownVisitor down;
  for (int i = 0; i < 3; i++) list[i]->accept(up); // pass visitor to accept
  for (int i = 0; i < 3; i++) list[i]->accept(down);
}

