#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

// https://accu.org/index.php/journals/1422
// functional programming using c++ templates

// checkout:
// https://www.codeproject.com/articles/3743/a-gentle-introduction-to-template-metaprogramming


struct NullType;
template <int x, typename xs> struct IntList;

template <typename T> struct Head;
template <int x, typename xs>
struct Head<IntList<x,xs> > {
    enum { value = x };
};
template <typename T> struct Tail;
template <int x, typename xs>
struct Tail<IntList<x,xs> > {
    typedef xs result;
};

// http://tismith.id.au/2014/template-metaprogramming-fun.html
template< int a, int b > struct GCD {
    static const int RESULT = GCD< b, a % b >::RESULT;
    static std::string s;
};
template< int a > struct GCD< a, 0 > {
    static const int RESULT = a;
};
template <int a, int b> std::string GCD<a,b>::s = "hoser"; // weird behaviour



template< int i > struct FIB {
    static const int RESULT = FIB< i - 1 >::RESULT + FIB< i - 2 >::RESULT;
};
template< > struct FIB< 1 > {
    static const int RESULT = 1;
};
template< > struct FIB< 2 > {
    static const int RESULT = 1;
};

//create the conditional -- may belong .hpp file
template< bool CONDITION, class THEN, class ELSE > struct IF {};
template<class THEN, class ELSE> struct IF< false, THEN, ELSE > {
    typedef ELSE TEST;
};
template<class THEN, class ELSE> struct IF< true, THEN, ELSE > {
    typedef THEN TEST;
};
// use the conditional
struct A {
    static const int RESULT = 1;
};
struct B {
    static const int RESULT = 0;
};
struct A1 {
    static inline void EXEC(void) {
        std::cout << "TRUE!";
    }
};
struct B1 {
    static inline void EXEC(void) {
        std::cout << "FALSE!";
    }
};

void test_conditional()
{
    std::cout << "true = " << IF<true, A, B>::TEST::RESULT << std::endl;
    std::cout << "true = " << IF<false, A, B>::TEST::RESULT << std::endl;
 
    std::cout << "true = ";
    IF<true, A1, B1>::TEST::EXEC();
    std::cout << std::endl;

    std::cout << "false = ";
    IF<false, A1, B1>::TEST::EXEC();
    std::cout << std::endl;
}

enum {
    ZERO=0,
    ONE,
    TWO,
    THREE,
    FOUR,
};

// function table
int addx(int i, int j)       { cout << "addx: "; return i + j; }
int subx(int i, int j)       { cout << "subx: "; return i - j; }
int mulx(int i, int j)       { cout << "mulx: "; return i * j; }
int divx(int i, int j)       { cout << "divx: "; return i / j; }
auto modx = [](int i, int j) { cout << "modx: "; return i % j; }; // lambda

template<typename T, typename U, typename V> using ifun = T(U, V);
using ifunx = ifun<int, int, int>;
function<ifunx> ifx1 = addx;
function<ifunx> ifx2 = subx;
function<ifunx> ifx3 = mulx;
function<ifunx> ifx4 = divx;
function<ifunx> ifx5 = modx;
// create a function table using the function<> template
map<int, function<ifunx>> binops = {
    {0, ifx1},
    {1, ifx2},
    {2, ifx3},
    {3, ifx4},
    {4, ifx5},
};



// use array of functors
template< int a > struct SWITCH {
    static const int RESULT = SWITCH< a-1 >::RESULT;
    //static inline void EXEC(void) {
    static inline void EXEC(int b) {
        switch (b) {
            case ONE:   cout << "ONE  : "; cout << binops[b](10,5); break;
            case TWO:   cout << "TWO  : "; cout << binops[b](10,5); break;
            case THREE: cout << "THREE: "; cout << binops[b](10,5); break;
            case FOUR:  cout << "FOUR : "; cout << binops[b](10,5); break;
        }
        cout << ": " << b << endl;
        SWITCH<a-1>::EXEC(b-1);
        //SWITCH<a-1>::RESULT;
    }
};
template<> struct SWITCH< 0 > {
    static const int RESULT = 0;
    //static inline void EXEC(void) {
    static inline void EXEC(int b = 0) {
        cout << "ZERO : 0" << endl;
    }
};

const int n_cases = 42;
void test_switch(int idx)
{

    SWITCH<n_cases>::EXEC(idx);
    //cout << SWITCH<val>::RESULT << endl;
}

// part ii -- lists
struct EmptyList{};
template <int a, typename L> struct LIST {
    static const int HEAD = a;
    typedef L TAIL;
};
template <class L>
struct SUM {
    static const int RESULT = 0;
};
// a template specialization
template <int a, class TAIL>
struct SUM< LIST< a, TAIL > > {
    static const int RESULT = a + SUM<TAIL>::RESULT;
};
typedef LIST<1, LIST<2, LIST<3, LIST<4, EmptyList>>>> MyList;

void test_list()
{
    cout << "HEAD : " << MyList::HEAD << endl;
    cout << "SUM  : " << SUM< MyList >::RESULT << endl;
}


int main()
{
    std::cout << Head<IntList<7,IntList<8, NullType>>>::value << std::endl;

    std::cout << "GCD (25,50) == " << GCD<25, 50>::RESULT << std::endl;
    std::cout << "GCD (113,0) == " << GCD<113, 0>::RESULT << std::endl;
    std::cout << "GCD::s: " << GCD<25,50>::s << std::endl;

    std::cout << "Fib 11: " << FIB<11>::RESULT << std::endl;

    test_conditional();
    test_switch(42);
    test_list();

    return 0;
}
