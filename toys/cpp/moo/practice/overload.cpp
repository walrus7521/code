#include <iostream>

using namespace std;

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
    Int() { cout << "Int: ctor" << endl; }
    ~Int() { cout << "Int: dtor" << endl; }
    Int(const Int &rhs) :
        i(rhs.i) { cout << "Int: copy ctor" << endl; }
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
 
private:
    int i;
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
