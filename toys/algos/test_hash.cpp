#include <iostream>
#include "Hash.hpp"

using namespace std;
 
// Driver program to test methods of graph class
int main()
{
    Hash h(13);
    h.insert("abe", 0);
    h.insert("boa", 1);
    h.insert("cod", 2);
    h.insert("dia", 3);
    h.insert("eat", 4);
    h.insert("fat", 5);
 
    h.show();
    cout << endl;

    cout << "h(7)?: " << h.lookup("goa", 7) << endl;
    cout << "h(4)?: " << h.lookup("eat", 4) << endl;

    pair<string, int> p = h.fetch("eat", 4);
    cout << "f(4): " << p.first << ": " << p.second << endl;
    pair<string, int> p2 = h.fetch("goe", 7);
    cout << "f(7): " << p2.first << ": " << p2.second << endl;
 
    return 0;
}

