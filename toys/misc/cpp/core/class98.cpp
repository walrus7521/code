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
    Derived() { cout << "Derived ctor" << endl; }
    ~Derived() { cout << "Derived dtor" << endl; }
    int& operator[](int i) { return v[i]; }
    int size() const { return v.size(); }
    void show() { cout << 42 << endl; }
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
    Foo() : counter_(0), str_(NULL), bar_() {
    cout << "Foo default ctor" << endl; }
    Foo(int c, string *p) :
        counter_(c), str_(p), bar_(c) {}
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
//    string s = "bar";
//    Foo *f = new Foo(2, &s);
//    f->show();
    test_vclass();
}
