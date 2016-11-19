#include <iostream>
#include <string>

using namespace std;

class numbered {
public:
    static int random;
    numbered() {
        cout << "numbered: ctor" << endl;
        serial = random++;
    }
    numbered(const numbered& rhs) {
        cout << "numbered: copy ctor" << endl;
        serial = random++;
    }
    int get() const { return serial; }
private:
    int serial;
};

int numbered::random = 42;

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

void fr(const numbered& s)
{
    cout << "f(): " << s.get() << endl;
}

class HasPtr {
public:
    HasPtr(const string& s = string()) :
        ps(new string(s)), i(0)
    {
        cout << "HasPtr: ctor" << endl;
    }
    ~HasPtr() {
        cout << "HasPtr: dtor" << endl;
        delete ps;
    }
    HasPtr(const HasPtr &rhs) :
        i(rhs.i),
        ps(new string(*rhs.ps))
    { cout << "HasPtr: copy ctor" << endl; } // copy constructor
    
    // value-like copy assignment
    HasPtr& operator=(const HasPtr& rhs)
    { 
        cout << "HasPtr: copy assn" << endl; 
        auto newp = new string(*rhs.ps);
        delete ps;
        ps = newp;
        i = rhs.i;
        return *this; // return reference to lhs
    } // copy assignment

    void show()
    {
        cout << "show: " << *ps << endl;
    }

private:
    int i;
    string *ps;
};

void test_has_ptr()
{
    cout << "testing HasPtr - enter" << endl;
    HasPtr h1("bart");
    HasPtr h2("cindy");
    h1.show();
    h2 = h1;
    h2.show();
    cout << "testing HasPtr - exit" << endl;
}


int main()
{
#if 0
    Foo f;
    cout << "f: " << f.get() << endl;
    Foo g = f; // copy init
    cout << "g: " << g.get() << endl;
    Foo h(g); // direct init
    cout << "h: " << h.get() << endl;
    Foo j;
    j = g;
    cout << "j: " << j.get() << endl;

    numbered a, b = a, c = b;
    fr(a); fr(b); fr(c);
#endif
    test_has_ptr();
}


