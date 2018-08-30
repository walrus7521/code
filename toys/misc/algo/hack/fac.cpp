#include <iostream>

using namespace std;

unsigned long factorial(unsigned long f)
{
    if ( f == 0 ) 
        return 1;
    return(f * factorial(f - 1));
}

int main()
{
    int n;
    cin >> n;
    if (n >= 2 && n <= 12) {
        cout << factorial(n) << endl;
    }
}
