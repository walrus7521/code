#include <iostream>

using std::cout; using std::endl;

int main()
{
    int x, y;
    auto add = [](int x, int y) { return x+y; };
    cout << add(40,2) << endl;
    return 0;
}

