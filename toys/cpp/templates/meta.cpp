#include <iostream>
#include <string>

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


// another sample
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


int main()
{
    std::cout << Head<IntList<7,IntList<8, NullType>>>::value << std::endl;

    std::cout << "GCD (25,50) == " << GCD<25, 50>::RESULT << std::endl;
    std::cout << "GCD (113,0) == " << GCD<113, 0>::RESULT << std::endl;
    std::cout << "GCD::s: " << GCD<25,50>::s << std::endl;

    std::cout << "Fib 11: " << FIB<11>::RESULT << std::endl;

    test_conditional();

    return 0;
}
