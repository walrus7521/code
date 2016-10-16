#include <iostream>

using namespace std;

int lookup(int x)
{
    return 42;
}

int lookup(int x, int y)
{
    return 43;
}

int lookup(int x, int y, double z)
{
    return 44;
}

int defaults(int x, int y = 5)
{
    return 42+x+y;
}

int main()
{
    cout << "lookup(x)    : " << lookup(1) << endl;
    cout << "lookup(x,y)  : " << lookup(1,2) << endl;
    cout << "lookup(x,y,z): " << lookup(1,2,3.0) << endl;
    cout << "defaults(x)  : " << defaults(1) << endl;
    cout << "defaults(x,y): " << defaults(1,3) << endl;
}
