#include <iostream>
#include "Screen.h"

using namespace std;

int main()
{
    Screen s(60,80,'.');
    s.move(30,40);
    s.set('#').display(cout);

    return 0;
}
