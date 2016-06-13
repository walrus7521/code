#include <iostream>
#include <string>

using namespace std;

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

int main()
{
    string s = "bar";
    Foo *f = new Foo(2, &s);
    f->show();
}
