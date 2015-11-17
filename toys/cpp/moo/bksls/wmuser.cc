#include <iostream>
#include "wmgr.h"

int main()
{
    Screen myScreen(5, 5, 'X');
    myScreen.move(4, 0).set('#'); //.display(std::cout);
    myScreen.move(3, 2).set('-'); //.display(std::cout);
    std::cout << "\n";
    myScreen.display(std::cout);
    std::cout << "\n";
    return 0;
}
