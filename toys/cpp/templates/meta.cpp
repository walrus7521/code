#include <iostream>

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
};

template< int a > struct GCD< a, 0 > {
 static const int RESULT = a;
};


int main()
{
    std::cout << Head<IntList<7,IntList<8, NullType>>>::value << std::endl;

    std::cout << "GCD (25,50) == " << GCD<25, 50>::RESULT << std::endl;


    return 0;
}
