#include <iostream>
#include <cstdlib>
#include "set.hpp"

int main()
{
    int m = 256;
    int maxval = 256;

    Set S(m, maxval);

    while (S.size() < m) {
        S.insert(rand() % maxval);
    }

    int *v = new int[m];

    S.report(v);

    for (int i = 0; i < m; i++) {
        std::cout << v[i] << "\n";
    }


}       
       

