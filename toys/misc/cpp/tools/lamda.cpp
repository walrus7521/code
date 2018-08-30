#include <iostream>

using std::cout; using std::endl;

int main()
{
    int x, y;
    auto add = [](int x, int y) { return x+y; };
    auto lambda = [](auto x){ return x; };
    cout << add(40,2) << endl;
    cout << lambda("Hello generic lambda!\n");
    return 0;
}

