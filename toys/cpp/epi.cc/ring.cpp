#include "pch.hpp"
#include "Ring.hpp"

int main()
{
    const int size = 32;
    int A[size] = {0};
    Ring<int> ring = { .read = 0, .write = 0, .size = size, .A = A };

}
