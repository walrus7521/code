#include <iostream>
#include "Person.h"

int main()
{
    Person dude(std::cin);
    //while (read(std::cin, dude)) {
        print(std::cout, dude); std::cout << std::endl;
    //}
    return 0;
}
