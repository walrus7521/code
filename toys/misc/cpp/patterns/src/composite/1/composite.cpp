#include <iostream>
#include <vector>
using namespace std;

class Component
{
  public:
    virtual void traverse() = 0;
};

class Primitive: public Component
{
    int value;
  public:
    Primitive(int val)
    {
        value = val;
    }
    void traverse()
    {
        cout << value << "  ";
    }
};

class Composite: public Component
{
    vector < Component * > children;
    int value;
  public:
    Composite(int val)
    {
        value = val;
    }
    void add(Component *c)
    {
        children.push_back(c);
    }
    void traverse()
    {
        cout << value << "  ";
        for (int i = 0; i < children.size(); i++)
          children[i]->traverse();
    }
};

class Row: public Composite
{
  public:
    // Two different kinds of "con-
    Row(int val): Composite(val){}
    // tainer" classes.  Most of the
    void traverse()
    {
        // "meat" is in the Composite
        cout << "Row"; // base class.
        Composite::traverse();
    }
};

class Column: public Composite
{
  public:
    Column(int val): Composite(val){}
    void traverse()
    {
        cout << "Col";
        Composite::traverse();
    }
};

int main()
{
  Row first(1);                 // Row1
  Column second(2);             //   |
  Column third(3);              //   +-- Col2
  Row fourth(4);                //   |     |
  Row fifth(5);                 //   |     +-- 7
  first.add(&second);           //   +-- Col3
  first.add(&third);            //   |     |
  third.add(&fourth);           //   |     +-- Row4
  third.add(&fifth);            //   |     |     |

  Primitive p6(6);
  first.add(&p6);               //   |     |     +-- 9
  Primitive p7(7);
  second.add(&p7);              //   |     +-- Row5
  Primitive p8(8);
  third.add(&p8);               //   |     |     |
  Primitive p9(9);
  fourth.add(&p9);              //   |     |     +-- 10
  Primitive p10(10);
  fifth.add(&p10);              //   |     +-- 8
  first.traverse();             //   +-- 6
  cout << '\n';                 
}
