#include <iostream>
#include "Hash.hpp"

using namespace std;
 
// Driver program to test methods of graph class
int main()
{
    Hash h(13);
    h.addHash(0);
    h.addHash(1);
    h.addHash(2);
    h.addHash(3);
    h.addHash(4);
    h.addHash(5);
 
    h.show();
    cout << endl;

    cout << "h(7)?: " << h.findHash(7) << endl;
    cout << "h(4)?: " << h.findHash(4) << endl;
 
    return 0;
}

