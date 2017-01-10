#include <iostream>
#include <vector>

// kinds of recursion: linear, tail, binary, nested, and mutual.

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

int fac(int n)
{
    int ret = 1;
    static vector<int> cache(N, -1);
    if (n == 0 || n == 1) return 1;
    int result = cache[n];
    if (result == -1) {
        cout << "fac cache miss for: " << n << endl;
        return n * fac(n-1); // n! = n*(n - 1)!
    }
    cout << "fac cache hit: " << result << endl;
    return result;
}

void test_fib()
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

string reverse(string line)
{
    cout << "r: " << line << endl;
    if (line == "") return "";
    return reverse(line.substr(1)) + line[0];
}

void test_reverse()
{
    string s = "hello";
    cout << s.substr(0) << endl;
    cout << s.substr(1) + s[0] << endl;
    cout << s.substr(2) + s[1] + s[0] << endl;
    cout << s.substr(3) + s[2] + s[1] + s[0]  << endl;
    cout << s.substr(4) + s[3] + s[2] + s[1] + s[0] << endl;
    cout << reverse(s) << endl;
}

int main()
{
    int x = 7;
    cout << "fac(" << x << ") = " << fac(x) << endl;
    //test_fib();
    //test_reverse();
}

