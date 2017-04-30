//utility.hpp
#include <iostream>

namespace utility
{
    void function1();
    void function2();
    void function3();

    template<typename T>
    void function4()
    {
       //function template definition should be here!
       std::cout << "function 4" << std::endl;
    }
}
