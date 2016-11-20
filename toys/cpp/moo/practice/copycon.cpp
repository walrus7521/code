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

class HasPtr_ValueLike {
    friend void swap(HasPtr_ValueLike &lhs, HasPtr_ValueLike &rhs);
public:
    HasPtr_ValueLike(const string& s = string()) :
        ps(new string(s)), i(0)
    {
        cout << "HasPtr_ValueLike: ctor" << endl;
    }
    ~HasPtr_ValueLike() {
        cout << "HasPtr_ValueLike: dtor" << endl;
        delete ps;
    }
    HasPtr_ValueLike(const HasPtr_ValueLike &rhs) :
        i(rhs.i),
        ps(new string(*rhs.ps))
    { cout << "HasPtr_ValueLike: copy ctor" << endl; } // copy constructor
    
    // value-like copy assignment
    HasPtr_ValueLike& operator=(const HasPtr_ValueLike& rhs)
    { 
        cout << "HasPtr_ValueLike: copy assn" << endl; 
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

void swap(HasPtr_ValueLike &lhs, HasPtr_ValueLike &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}

// we would normally use shared_ptr's to manage the destrution 
// of the string pointer, but we will instead implement reference
// counting because we love pain.
class HasPtr_PointerLike {
    friend void swap(HasPtr_PointerLike &lhs, HasPtr_PointerLike &rhs);
public:
    HasPtr_PointerLike(const string& s = string()) :
        ps(new string(s)), i(0), use(new size_t(1))
    {
        cout << "HasPtr_PointerLike: ctor" << endl;
    }
    ~HasPtr_PointerLike() {
        cout << "HasPtr_PointerLike: dtor" << endl;
        if (--*use == 0) {
            delete ps;
            delete use;
        }
    }
    HasPtr_PointerLike(const HasPtr_PointerLike &rhs) :
        i(rhs.i),
        ps(rhs.ps),
        use(rhs.use)
    { 
        cout << "HasPtr_PointerLike: copy ctor" << endl; 
        ++*use;
    } // copy constructor
    
    // value-like copy assignment
    HasPtr_PointerLike& operator=(const HasPtr_PointerLike& rhs)
    { 
        cout << "HasPtr_PointerLike: copy assn" << endl; 
        swap(*this, rhs);
        ++*rhs.use;
        if (--*use == 0) {
            delete ps;
            delete use;
        }
        ps = rhs.ps;
        i = rhs.i;
        use = rhs.use;
        return *this; // return reference to lhs
    } // copy assignment

    void show()
    {
        cout << "show: " << *ps << endl;
    }

private:
    string *ps;
    int i;
    size_t *use;
};


void swap(HasPtr_PointerLike &lhs, HasPtr_PointerLike &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}

void test_has_ptr_pointer_like()
{
    cout << "testing HasPtr_PointerLike - enter" << endl;
    HasPtr_PointerLike h1("bart");
    HasPtr_PointerLike h2("cindy");
    h1.show();
    h2 = h1;
    h2.show();
    cout << "testing HasPtr_PointerLike - exit" << endl;
}

void test_has_ptr_value_like()
{
    cout << "testing HasPtr_ValueLike - enter" << endl;
    HasPtr_ValueLike h1("bart");
    HasPtr_ValueLike h2("cindy");
    h1.show();
    h2 = h1;
    h2.show();
    cout << "testing HasPtr_ValueLike - exit" << endl;
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
    //test_has_ptr_value_like();
    test_has_ptr_pointer_like();
}


