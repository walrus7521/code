#include <iostream>

int  main()
{
    int v[]= {0, 2, 4, 6, 8, 1, 3, 5, 7};
    
    for (auto x: v)
        std::cout << x << ' ';
    std::cout << '\n';

    for (auto& x: v)
        ++x;

    for (auto x: v)
        std::cout << x << ' ';
    std::cout << '\n';
}
