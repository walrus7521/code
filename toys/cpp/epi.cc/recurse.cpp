#include <iostream>
#include <vector>

using namespace std;

#define swap(a,b) { \
    int tmp = a; \
    tmp = a; \
    a = b; \
    b = tmp; \
}

// iterative: broken
int fibi(int x)
{
    int a = 1;
    int b = 1;
    for (int i = 2; i < x; i++) {
        a = a + b;
        swap(a,b);
    }
    return b;
}

// results in exponential number of calls.
int fibr(int x)
{
    if (x < 2)
        return 1;

    return fibr(x-1) + fibr(x-2);
}

#define N 256 // max value in call chain
// Recursion with DP:
int fibd(int x)
{
    static vector<int> cache(N, -1); // oh yeah!!

    int result = cache[x];

    if (result == -1) {
        // not in cache
        if (x < 2) {
            result = 1;
        } else {
            result = fibd(x-1) + fibd(x-2);
        }
        cache[x] = result;
        cout << "miss: cache[" << x << "] = " << result << endl;
    } else {// else skip due to cache !!!
        cout << "hit:  cache[" << x << "] = " << result << endl;
    }
    return result;
}

int main()
{
    int x = 7;

    int y = 4, z = 2;
    cout << "y: " << y << ", z: " << z << endl;
    swap(y,z);
    cout << "y: " << y << ", z: " << z << endl;

    cout << "fibi(" << x << ") = " << fibi(x) << endl;
    cout << "fibr(" << x << ") = " << fibr(x) << endl;
    cout << "fibd(" << x << ") = " << fibd(x) << endl;
}

