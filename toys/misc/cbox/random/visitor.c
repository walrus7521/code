#include <stdio.h>
#include <stdlib.h>

// use visitors on composite or collections
// double dispatch -> invoked method issues callback

struct _element;

// abstract interface visitor class
typedef struct _visitor
{
    void (*visit)(struct _element *e);
} Visitor;

// abstract element class with an accept(Visitor) method
typedef struct _element
{
    void (*accept)(Visitor *v);
    char *(*get)();
} Element;

// concrete element classes
typedef struct _this
{
    Element e;
    //void accept(Visitor &v) { v.visit(this); }
    //string get() { return "This"; }
} This;

typedef struct _that
{
    Element e;
    //virtual void accept(Visitor &v) { v.visit(this); }
    //virtual string get() { return "That"; }
} That;

void IRQ_V1()
{
}
#if 0
// concrete visitor classes for each "operation" to do on "elements"
class UpVisitor: public Visitor
{
    virtual void visit(Element *e) { cout << "do Up on " << e->get() << '\n'; }
};

class DownVisitor: public Visitor
{
    virtual void visit(Element *e) { cout << "do Down on " << e->get() << '\n'; }
};
#endif

int main()
{
  Element *list[3]; // = { new This(), new That() };
  //UpVisitor up; // Client creates "visitor" objects
  //DownVisitor down;
  //for (int i = 0; i < 2; i++) list[i]->accept(up); // pass visitor to accept
  //for (int i = 0; i < 2; i++) list[i]->accept(down);
}

