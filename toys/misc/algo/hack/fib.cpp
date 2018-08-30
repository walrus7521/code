#include <iostream>

using namespace std;

int fib(int x) {
    if (x == 0)
        return 0;
    if (x == 1)
        return 1;
    return fib(x-1)+fib(x-2);
}
int main() {
    //int n;
    //cin >> n;
    for (int i = 0; i < 20; ++i) {
        cout << fib(i) << endl;
    }
}
