#include <iostream>
#include <numeric>

using namespace std;

int gcd(int a, int b)
{
    for (;;)
    {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}

int lcm(int a, int b)
{
    int temp = gcd(a, b);
    cout << "gcd: " << temp << endl;
    return temp ? (a / temp * b) : 0;
}

int main()
{
    //int arr[] = { 5, 7, 9, 12 };
    int arr[] = { 3, 2 };
    int size = sizeof(arr) / sizeof(arr[0]);

    int result = std::accumulate(arr, arr + size, 1, lcm);

    std::cout << result << '\n';
}

