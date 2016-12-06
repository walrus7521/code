#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <memory>
#include <functional>

using namespace std;

template <typename T>
int compare(const T &v1, const T &v2)
{
    //if (v1 < v2) return -1;
    //if (v2 < v1) return 1;
    // more generic, allows use on classes
    // that may not support <
    // goal: reduce the requirements on classes using this function
    cout << "compare orig version" << endl;
    if (less<T>()(v1, v2)) return -1;
    if (less<T>()(v2, v1)) return 1;
    return 0;
}
// template specialization or original version
template <>
int compare(const char* const &p1, const char* const &p2)
{
    cout << "specialization compare version" << endl;
    return strcmp(p1, p2);
}
// nontype parameters
template <unsigned N, unsigned M>
int compare2(const char (&p1)[N], const char (&p2)[M])
{
    cout << "compare nontype version" << endl;
    return strcmp(p1, p2);
}
template <typename T, typename F = less<T>>
int compare3(const T &v1, const T &v2, F f = F())
{
    cout << "compare3 version" << endl;
    if (f(v1, v2)) return -1;
    if (f(v2, v1)) return 1;
    return 0;
}
template <typename T, typename U, typename F = less<T>>
int FlexibleCompare(const T &v1, const U &u2, F f = F())
{
    cout << "FlexibleCompare version" << endl;
    if (f(v1, u2)) return -1;
    if (f(u2, v1)) return 1;
    return 0;
}



// dump container
template <template <typename> class ContainerType, typename ValueType>
void print_container(const ContainerType<ValueType>& c) {
  for (const auto& v : c) {
    std::cout << v << ' ';
  }
  std::cout << '\n';
}

// delete wrapper, for debugging purposes
class DebugDelete {
public:
    DebugDelete(ostream &s = cerr) : os(s) {}
    template <typename T> void operator()(T *p) const
    { os << "deleting unique_ptr to: " << *p << endl; delete p; }
private:
    ostream &os;
};


void DeleteStringPtr(string *s)
{
    if (nullptr != s) {
        cout << "deleting shared_ptr to: " << *s << endl;
    } else {
        cout << "deleting shared_ptr   : " << s << endl;
    }
    delete s;
}

template <typename T>
void my_deleter(T *t)
{
    cout << "my_deleter of shared_ptr to: " << *t << endl;
    delete t;
}

template <typename T>
void my_deleter2(T *t)
{
    cout << "my_deleter2 of shared_ptr to: " << *t << endl;
    delete t;
}

template <typename T>
T foo(T* p)
{
    T tmp = *p;
    return tmp;
}

#include "Blob.h"

void test_blob()
{
    Blob<string> b1;
    {
        Blob<string> b2 = {"a", "an", "the"};
        b1 = b2;
        b2.push_back("about");
        cout << b2.front() << endl;
        b2++;
        cout << b2 << endl;
    }

    StrBlob sb1 = {"bass", "guitar", "fiddle", "piano"};
    for (auto &s : sb1) {
        cout << s << endl;
    }

    IntBlob ib1 = {2,5,3,2,2,5,9,6,3,0};
    for (auto &i : ib1) {
        cout << i << endl;
    }

    clump<int> ib2 = {2,1,3,4,5,6,8,5,1,9};
    for (auto &i : ib2) {
        cout << i << endl;
    }

    twin<int> win;
    partNo<string> books;

    int ia[] = {0,1,2,3,4,5,6,7,8,9};
    vector<long> vi = {0,1,2,3,4,5,6,7,8,9};
    list<const char*> w = {"now","is","the","time"};

    // instantiate Blob<int> using template ctor
    Blob<int> a1(begin(ia), end(ia)); // Blob<int>::Blob(int*, int*);
    Blob<int> a2(vi.begin(), vi.end());
    Blob<string> a3(w.begin(), w.end());

}
// static members of template classes
template <typename T> 
class Foo {
public:
    static size_t count() { return ctr; }
    // specialize just a function
    void Bar() { cout << "Bar1" << endl; }
private:
    static size_t ctr;
};
template<> void Foo<int>::Bar() { cout << "Bar2" << endl; }

template <typename T> 
size_t Foo<T>::ctr = 0;

template <typename elemType> class ListItem;

template <typename elemType> 
class List {
public:
private:
    ListItem<elemType> *front, *end;
};

// iterate a container of unknown type
// using a trailing return type
template <typename It>
auto fcn(It beg, It end) -> decltype(*beg)
{
    for (;beg != end; ++beg) {
        cout << *beg << ' ';
    }
    cout << '\n';
    return *beg;
}

// using type_traits to obtain the unknown type
template <typename It>
auto fcn2(It beg, It end) ->
    typename remove_reference<decltype(*beg)>::type
{
    for (;beg != end; ++beg) {
        cout << *beg << ' ';
    }
    cout << '\n';
    return *beg;
}

template <typename T> void g(T&& val) {
    cout << "g(" << val << ")" << endl;
    vector<T> v;
    v.push_back(val);
    for (auto& i : v) {
        cout << i << endl;
    }

}

// FORWARDING
template <typename F, typename T1, typename T2>
void flip1(F f, T1 t1, T2 t2)
{
    f(t2, t1);
}
// this one works by using RValue refs - it preserves
// both constness and lvalue/rvalue-ness
template <typename F, typename T1, typename T2>
void flip2(F f, T1 &&t1, T2 &&t2)
{
    f(t2, t1);
}
template <typename F, typename T1, typename T2>
void flip3(F f, T1 &&t1, T2 &&t2)
{
    f(std::forward<T2>(t2), std::forward<T1>(t1));
}
void f2(int i, int &j)
{
    cout << "f2: " << i << " " << ++j << endl;
}
void f(int v1, int &v2)
{
    cout << "f: " << v1 << " " << ++v2 << endl;
}

// 16.3 TEMPLATE OVERLOADING
template <typename T> string debug_rep(const T &t)
{
    cout << "debug_rep:1" << endl;
    ostringstream ret;
    ret << t;
    return ret.str(); // return copy of string
}
// pointer version
template <typename T> string debug_rep(T *p)
{
    cout << "debug_rep:2" << endl;
    ostringstream ret;
    ret << "pointer: " << p;
    if (p) {
        ret << " " << debug_rep(*p);
    } else {
        ret << " null pointer";
    }
    return ret.str();
}
string debug_rep(const string &s)
{
    cout << "debug_rep:3" << endl;
    return '"' + s + '"';
}
// c-style char strings and literals
string debug_rep(char *p)
{
    cout << "debug_rep:4" << endl;
    return debug_rep(string(p));
}
string debug_rep(const char *p)
{
    cout << "debug_rep:5" << endl;
    return debug_rep(string(p));
}

// 16.4 VARIADIC TEMPLATES
template <typename T, typename ... Args>
void foo(const T &t, const Args& ... rest)
{
    cout << "Args: " << sizeof ... (Args) << endl;
    cout << "Rest: " << sizeof ... (rest) << endl;
    //for (int i = 0; i < sizeof ... (Args); ++i) {
    //    cout << (Args)[i] << endl;
    //}
}
// Forwarding Parameter Packs
// -- see StrVec::emplace_back

// 16.5 TEMPLATE SPECIALIZATION
// overload std namepace version of hash
// use this class in hash below
//template <class T> class std::hash; // needed for friending
class FooMan {
    friend class std::hash<FooMan>;
private:
    string name;
    int age;
    float factor;
public:
    FooMan(string n, int a, float f) :
        name(n), age(a), factor(f) {}
    //bool operator==(const FooMan& lhs, const FooMan& rhs) {
    bool operator==(const FooMan& rhs) {
        cout << "FooMan: ==" << endl;

#if 0 // can't get this working
        size_t lhash = hash<FooMan>{}(this);
        size_t rhash = hash<FooMan>{}(rhs);
#endif
#if 1
        size_t lhash = std::hash<string>{}(this->name) ^
                       std::hash<int>{}(this->age) ^
                       std::hash<float>{}(this->factor);
 
        size_t rhash = std::hash<string>{}(rhs.name) ^
                       std::hash<int>{}(rhs.age) ^
                       std::hash<float>{}(rhs.factor);
 
#endif
        return (lhash == rhash);
    }
};

namespace std {
template <>
    struct hash<FooMan>
    {
        typedef size_t result_type;
        typedef FooMan argument_type;
        size_t operator()(const FooMan& f) const {
            cout << "specialized hasher: ";
            return std::hash<string>()(f.name) ^
                   std::hash<int>()(f.age) ^
                   std::hash<float>()(f.factor);
        }

    };
} // close namespace

// partial specializations of class templates
template <class T> struct rem_ref {
    typedef T type;
};
template <class T> struct rem_ref<T&> {
    typedef T type;
};
template <class T> struct rem_ref<T&&> {
    typedef T type;
};


int main()
{
    // specialization stuff
    Foo<string> fs;
    fs.Bar(); // calls regular function Bar
    Foo<int> fi;
    fi.Bar(); // calls specialized function Bar

    FooMan fm("toad", 123, 0.1);
    FooMan fm2("toad", 123, 0.1);
    if (fm == fm2) {
        cout << "equal FooMan" << endl;
    } else {
        cout << "non equal FooMan" << endl;
    }
    cout << hash<FooMan>{}(fm) << endl;
    cout << hash<FooMan>{}(fm2) << endl;

    vector<int> vi = {1,2,3,4}; 
    int x = 42;
    string name = "dude";
    cout << hash<string>{}(name) << endl;
    cout << hash<int>{}(42) << endl;
    cout << hash<int>{}(x) << endl;

    // partial template class specialization
    int i;
    rem_ref<decltype(42)>::type a;
    rem_ref<decltype(i)>::type b;
    rem_ref<decltype(std::move(i))>::type c;
    a = b = c = 43; // all are ints
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "c: " << c << endl;

#if 0
    // variadic templates
    int i = 0; 
    double d = 3.14;
    string s4 = "how now";
    // template parameter T is deduces from 1st parameter
    foo(i, s4, 42, d);  // three parameters in pack
    foo(s4, 42, "hi");   // two
    foo(d, s4);          // one
    foo("hi");          // zero empty pack
#endif

#if 0 // forwarding
    int it = 43;
    f(42, it);
    it = 43;
    flip2(f, it, 42);
    cout << "after call: " << it << endl;
    it = 43;
    flip2(f, 42, it); // now it will chg, T2 is a ref
    cout << "after call: " << it << endl;
    it = 43;
    flip3(f2, it, 42); // now it will chg, T2 is a ref
    cout << "after call: " << it << endl;
#endif
#if 0 // rvalues
    string s1("hi"), s2;
    s2 = std::move(string("bye!")); // move from rvalue
    cout << s2 << endl;
    s2 = std::move(s1); // s1 is indeterminate state after move
    cout << s2 << endl;
    g(42);
    // these won't compile
    //const int i = 43;
    //const int& j = i;
    //g(j);
#endif
#if 0
    cout << compare(1,0) << endl;
    string a = "hand", b = "bag";
    cout << compare(b,b) << endl;
    cout << compare("dou","bag") << endl;
    const char *p;
    const char *q;
    char ppp[] = "aaa";
    char qqq[] = "bbb";
    p = &ppp[0];
    q = &qqq[0];
    cout << compare(p, q) << endl; // specialization version

    vector<int> v1{1,2,3};
    vector<int> v2{4,5,6};

    cout << compare(v1, v2) << endl;
    cout << compare(v2, v1) << endl;

    cout << compare(1, 0) << endl;
    cout << compare(0, 1) << endl;
    cout << compare(1, 1) << endl;

    int rc = 42;
    rc = foo(&rc);
    cout << rc << endl;

    const char a2[4] = "bag";
    const char b2[4] = "dog";
    cout << compare(a2, b2) << endl;
    cout << compare2(a2, b2) << endl;
    cout << compare3(1,0) << endl;
    cout << compare3("bat","man") << endl;
    int aa = 2;
    long bb = 1;
    cout << FlexibleCompare(aa, bb) << endl;
#endif
#if 0
    vector<int> vi{1,2,3};
    vector<string> vs{"one","two","three"};
    const vector<string> cvs{"four","five","six"};
    auto &ii = fcn(vi.begin(), vi.end());
    auto &ss = fcn(vs.begin(), vs.end());
    // this one uses type traits
    auto &css = fcn2(cvs.begin(), cvs.end());
#endif
#if 0
    test_blob();

    Foo<int> fi;
    auto ct = Foo<int>::count();
    cout << "ct: " << ct << endl;
    ct = fi.count();
    cout << "ct: " << ct << endl;
    // demo customer deleter
    double *p = new double(3.14);
    DebugDelete d;
    d(p);
    int *ip = new int(42);
    DebugDelete()(ip);
#endif
#if 0
    // we can supply DebugDelete as the deleter to unique_ptr's
    unique_ptr<int, DebugDelete> p2(new int(43), DebugDelete());
    unique_ptr<string, DebugDelete> sp2(new string("dude"), DebugDelete());

    shared_ptr<string> ps(new string("the dawg"), DeleteStringPtr);
    shared_ptr<string> ps2(new string("homi"), my_deleter<string>);
    // reset to different deleter at run-time -- only shared_ptr's not unique_ptr's
    // looks like call to reset will call the original deleter first
    ps2.reset(new string("wusup"), my_deleter2<string>);
#endif
#if 0
    // template overloading
    string s("hi");
    cout << debug_rep(s) << endl;
    cout << debug_rep(&s) << endl;
    cout << debug_rep("hi world!") << endl;
    char s2[] = "hello dude";
    cout << debug_rep(s2) << endl;
#endif

}
