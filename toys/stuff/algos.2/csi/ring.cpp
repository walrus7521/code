#include "pch.hpp"
#include "Ring.hpp"

using namespace std;

int main()
{
    int A[32] = {0};
    Ring<int> ring = { .read = 0, .write = 0, .size = 32, .A = A };

    for (int i = 0; i < 16; ++i) {
        //if (!Ring_empty(&ring)) {
        Ring_put(&ring, i);
        Ring_status(&ring);
        //}
    }
    Ring_status(&ring);
    Ring_show(&ring);
    while (!Ring_empty(&ring)) {
        int key = Ring_get(&ring);
        cout << "get: " << key << endl;
        Ring_status(&ring);
    }
}
