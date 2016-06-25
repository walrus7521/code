#include <iostream>
#include <string>
#include <vector>


/*

http://www.cplusplus.com/forum/beginner/157568/

Abstract class
An abstract class is, conceptually, a class that cannot be instantiated and 
is usually implemented as a class that has one or more pure virtual (abstract) 
functions.

A pure virtual function is one which must be overridden by any concrete 
(i.e., non-abstract) derived class. This is indicated in the declaration 
with the syntax " = 0" in the member function's declaration.

class AbstractClass {
public:
  virtual void AbstractMemberFunction() = 0; // Pure virtual function makes
                                             // this class Abstract class.
  virtual void NonAbstractMemberFunction1(); // Virtual function.
 
  void NonAbstractMemberFunction2();
};

In general an abstract class is used to define an implementation and is 
intended to be inherited from by concrete classes. It's a way of forcing a 
contract between the class designer and the users of that class

Interface
An interface has no implementation.
An interface class contains only a virtual destructor and pure virtual functions.
An interface class is a class that specifies the polymorphic interface i.e. pure 
virtual function declarations into a base class. The programmer using a class 
hierarchy can then do so via a base class that communicates only the interface of 
classes in the hierarchy.

class shape   // An interface class
{
  public:
    virtual ~shape();
    virtual void move_x(int x) = 0;
    virtual void move_y(int y) = 0;
    virtual void draw() = 0;
//...
};


Every interface class should have a virtual destructor. Virtual destructor makes 
sure that when a shape is deleted polymorphically, correct destructor of the 
derived class is invoked.

Differences
1 - interfaces can have no state or implementation
2 - a class that implements an interface must provide an implementation of all the 
    method of that interface
3 - abstract classes may contain state (data members) and/or implementation (methods)
4 - abstract classes can be inherited without implementing the abstract methods (though 
    such a derived class is abstract itself)
5 -interfaces may be multiple-inherited, abstract classes may not (this is probably the 
key concrete reason for interfaces to exist separately from abtract classes - they 
permit an implementation of multiple inheritance that removes many of the problems of 
general MI).
6- If you anticipate creating multiple versions of your component, create an abstract 
class. Abstract classes provide a simple and easy way to version your components. By 
updating the base class, all inheriting classes are automatically updated with the change. 
Interfaces, on the other hand, cannot be changed once created. If a new version of an 
interface is required, you must create a whole new interface.
7-If the functionality you are creating will be useful across a wide range of disparate 
objects, use an interface. Abstract classes should be used primarily for objects that 
are closely related, whereas interfaces are best suited for providing common 
functionality to unrelated classes.


 */  
using namespace std;

template<typename T>
class Template {
public:
    Template(const T& val) : value(val) {}
    void show() { cout << value << endl; }
private:
    T value;
};

// pure virtual base class
class Base {
public:
    virtual int& operator[](int) = 0;
    virtual int size() const = 0;
    virtual void show() = 0;
    virtual ~Base(){}
};

class Derived : public Base {
public:
    Derived(){ cout << "Derived ctor" << endl; }
    ~Derived(){ cout << "Derived dtor" << endl; }
    int& operator[](int i) override { return v[i]; }
    int size() const override { return v.size(); }
    void show() override { cout << 42 << endl; }
private:
    vector<int> v;
};

class Bar {
public:
    Bar() : counter_(0) {
    cout << "Bar default ctor" << endl; }
    Bar(int c) : counter_(c) {
    cout << "Bar(" << c << ")" << endl; }
private:
    int counter_;
};

// use initializer lists
class Foo {
public:
    Foo() : counter_(0), str_(NULL), bar_() 
    {
        cout << "Foo default ctor" << endl; 
    }

    Foo(int c, string *p) :
        counter_(c), str_(p), bar_(c) 
    {
        cout << "Foo ctor(" << c << ", " << *p << ")" << endl; 
    }

    void show() { cout << "counter: " << counter_ << 
                  " name: " << *str_ << endl;
    }
private:
    int counter_;
    string* str_;
    Bar bar_;
};

void polymorph(Base *b)
{
    b->show();
}

void test_vclass()
{
    Derived *d = new Derived();
    polymorph(d);
    delete d;
}

int main()
{
    string s = "bar";
    Foo *f = new Foo(2, &s);
    Foo f2;
    Bar *b = new Bar();
    Bar b2;
    f->show();
    test_vclass();
    int integer;

    // demonstrate rtti
    // use typeid to test type equality
    cout << "typeid name: " << typeid(f).name() << endl;
    cout << "typeid name: " << typeid(f2).name() << endl;
    cout << "typeid name: " << typeid(b).name() << endl;
    cout << "typeid name: " << typeid(b2).name() << endl;
    cout << "typeid name: " << typeid(integer).name() << endl;
    cout << "typeid name: " << typeid(int).name() << endl;

    if (typeid(*f) == typeid(*b)) {
        cout << "foo and bar are the same type." << endl;
    }
    if (typeid(f2) == typeid(*f)) {
        cout << "f2 and f are the same types" << endl;
    }
    if (typeid(b2) == typeid(*b)) {
        cout << "b2 and b are the same types" << endl;
    }
    if (typeid(integer) == typeid(int)) {
        cout << "integer is an int type" << endl;
    }

    // use dynamic cast to see if classes are related
    Derived *d = new Derived();
    if (dynamic_cast<Base*>(d)) {
        cout << "Derived is subclass of Base" << endl;
    }

    // test template
    Template<string> *t1 = new Template<string>("bart");
    Template<int> *t2 = new Template<int>(777);
    t1->show();
    t2->show();

}
