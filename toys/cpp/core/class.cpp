#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
}
