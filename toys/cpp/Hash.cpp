#include <iostream>
#include <string>

using namespace std;

int StringHash(const string& str, int modulus) {
    const int kMult = 997;
    int val = 0;
    for (char c : str) {
        val = (val * kMult + c) % modulus;
    }
    return val;
}

int main()
{
    cout << StringHash("hello", 23) << endl;
    cout << StringHash("dude", 23) << endl;

}
