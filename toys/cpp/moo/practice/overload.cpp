#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// conversion operators example
class SmallInt {
public:
    // allow conversion from int to Int
    SmallInt(int val) :
        i(val)
    { cout << "SmallInt: ctor(int)" << endl; }
    operator int() const { 
        cout << "SmallInt: int()" << endl;
        return i; 
    }
    //operator int*() const { 
    //    cout << "SmallInt: int*()" << endl;
    //    return pi; 
    //}
private:
    int i;
    int *pi;
};

class Int {
    friend std::ostream & operator<<(std::ostream &os, const Int& i);
    friend std::istream & operator>>(std::istream &is, Int& i);
    friend Int operator+(const Int& lhs, const Int& rhs);
    friend Int operator+=(const Int& lhs, const int rhs);
    friend bool operator==(const Int& lhs, const Int& rhs);
    friend bool operator!=(const Int& lhs, const Int& rhs);
    friend bool operator<(const Int& lhs, const Int& rhs);
    friend bool operator>(const Int& lhs, const Int& rhs);

public:
    Int() :
        os(cout), sep('x')
    { cout << "Int: ctor()" << endl; }

    Int(ostream &o, char c) :
        os(o), sep(c) 
    { cout << "Int: ctor(os,sep)" << endl; }

    Int(const Int &rhs) :
        os(cout), sep(' '), i(rhs.i) 
    { cout << "Int: copy ctor(&)" << endl; }

    ~Int() { cout << "Int: dtor" << endl; }

    Int& operator=(Int& rhs) {
        cout << "Int: copy assn" << endl;
        i = rhs.i;
        return *this;
    }
    // these work
    Int& operator=(int rhs) {
        cout << "Int: int =" << endl;
        i = rhs;
        return *this;
    }
    Int& operator+(const Int& rhs) {
        cout << "Int: +" << endl;
        i += rhs.i;
        return *this;
    }
    Int& operator+=(const Int& rhs) {
        cout << "Int: +=" << endl;
        //Int i = lhs;
        i += rhs.i;
        return *this;
    }
    // usually returns a reference, and has a const version as well
    // return a reference so we can also assign
    int& operator[](const int i) {
        cout << "Int: []" << endl;
        return this->i;
    }
    
    // prefix operators
    Int& operator++() {
        cout << "Int: pre ++" << endl;
        ++i;
        return *this;
    }
    Int& operator--() {
        cout << "Int: pre --" << endl;
        --i;
        return *this;
    }
    
    // postfix operators
    // must return the original state, but store the new state
    Int& operator++(int) {
        cout << "Int: post ++" << endl;
        Int &n = *this;
        i++;
        return n;
    }
    Int& operator--(int) {
        cout << "Int: post --" << endl;
        Int &n = *this;
        i--;
        return n;
    }
    // dereference operator (and arrow)
    Int& operator*() {
        cout << "Int: deref *" << endl;
        return *this;
    }
    Int* operator->() {
        cout << "Int: arrow ->" << endl;
        return &this->operator*();
    }

    // call operators
    Int operator() () {
        cout << "Int: ()()" << endl;
        Int ret;
        ret.m_i = ret.i = 91;
        return ret;
    }
    void operator() (const string &s) {
        cout << "Int: ()(s)" << endl;
        os << s << sep;
    }
    int operator() (int x, int y, int z) {
        cout << "Int: ()(xyz)" << endl;
        os << x << y << z << sep;
        return 42;
    }

public:
    int m_i;
private:
    int i;
    ostream &os;
    char sep;
};

bool operator==(const Int& lhs, const Int& rhs) {
    cout << "Int: ==" << endl;
    return (lhs.i == rhs.i);
}

bool operator!=(const Int& lhs, const Int& rhs) {
    cout << "Int: !=" << endl;
    return (lhs.i != rhs.i);
}

bool operator<(const Int& lhs, const Int& rhs) {
    cout << "Int: <" << endl;
    return (lhs.i < rhs.i);
}

bool operator>(const Int& lhs, const Int& rhs) {
    cout << "Int: >" << endl;
    return (lhs.i > rhs.i);
}

Int operator+(const Int& lhs, const Int& rhs) {
    cout << "Int: +'" << endl;
    Int i = lhs;
    i += rhs;
    return i;
}

Int operator+=(const Int& lhs, const int rhs) {
    cout << "Int: int +=" << endl;
    Int i = lhs;
    i.i += rhs;
    return i;
}


std::ostream & operator<<(std::ostream &os, const Int& i)
{
    return os << i.i;
}

std::istream & operator>>(std::istream &is, Int& i)
{
    int tmp;
    is >> tmp;
    // check for errors: wrong type, eof, ...
    // also, if more constraints are imposed on the input
    // and they are not met, then we can inject an error: failbit
    // is.setstate(std::ios::failbit);
    if (is) {
        i.i = tmp;
    } else {
        i.i = 0; // default initialize on error
    }
    return is;
}

int lookup(int x)
{
    return 42;
}

int lookup(int x, int y)
{
    return 43;
}

int lookup(int x, int y, double z)
{
    return 44;
}

int defaults(int x, int y = 5)
{
    return 42+x+y;
}

void test()
{
    Int i, j;
    i = j;
    i = 3;
    j = 42;
    Int k;
    k = 42;
    k = i + j;
    k += 4;
    j += k;
    if (i == j) {
        cout << "i == j" << endl;
    } else {
        cout << "i != j" << endl;
    }
    if (i < j) cout << i;
    if (i > j) cout << j;

    cin >> j;
    cout << j << endl;
    cout << k << endl; 
    cout << k[3] << endl;
    k[2] = 33;
    k[2]--;
    k[2]++;
    j++;
    --j++;
    cout << k[2] << endl;
    cout << "start member access ops" << endl;
    Int m;
    m.m_i = 42;
    Int *n;// = new Int();
    n = &m;
    cout << "deref: " << (*m).m_i << endl;
    cout << "arrow: " << m->m_i << endl;
    cout << "call op(): " << m().m_i << endl;
    string nm("bart");
    cout << "call op(s): " << endl;
    m(nm);
    Int q(cerr, 'v');
    q(nm);

    vector<string> vs = { "cindy", "mac", "claire" };
    for_each(vs.begin(), vs.end(), Int(cerr, '\n'));

    Int r;
    r(2,3,4);


    // SmallInt stuff
    cout << endl;
    cout << "test SmallInt" << endl;
    SmallInt si(42);
    SmallInt si2 = 24;
    int x = si2 + 4;
    cout << si << endl;
    cout << x << endl;
}

int main()
{
#if 0
    cout << "lookup(x)    : " << lookup(1) << endl;
    cout << "lookup(x,y)  : " << lookup(1,2) << endl;
    cout << "lookup(x,y,z): " << lookup(1,2,3.0) << endl;
    cout << "defaults(x)  : " << defaults(1) << endl;
    cout << "defaults(x,y): " << defaults(1,3) << endl;
#endif
    test();
}
