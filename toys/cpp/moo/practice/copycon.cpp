#include <iostream>
#include <string>

using namespace std;

class Foo {
public:
    // default constructor
    // default initializes all members in order as appear in class
    // prior to running the body
    Foo() : name("Bart") { 
        cout << "Foo: ctor" << endl; } // default constructor

    // copy constructor should not be explicit
    Foo(const Foo &rhs) :
        units(rhs.units),
        name(rhs.name)
    { cout << "Foo: copy ctor" << endl; } // copy constructor
    
    // copy assignment
    Foo& operator=(const Foo& rhs)
    { cout << "Foo: copy assn" << endl; 
        name = rhs.name;
        units = rhs.units;
        return *this; // return reference to lhs
    } // copy assignment

    // destructor
    // body runs first, then the members are implicitly destroyed
    // in reverse order as appear in class
    // use smart pointers so they get automatically destroyed
    ~Foo() { cout << "Foo: dtor" << endl; }

    string get() { return name; }
private:
    std::string name;
    int units;
};

int main()
{
    Foo f;
    cout << "f: " << f.get() << endl;
    Foo g = f; // copy init
    cout << "g: " << g.get() << endl;
    Foo h(g); // direct init
    cout << "h: " << h.get() << endl;
    Foo j;
    j = g;
    cout << "j: " << j.get() << endl;
}

