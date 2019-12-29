#include <iostream>
#include <string>

using namespace std;

const static int MAGIC_NUMBER = 4;

template <typename T>
void join(T* arr[], size_t n, T c, std::basic_string<T>& s)
{
    s.clear();
    cout << "here: " << n << '\n';

    for (int i = 0; i < n; ++i) {
        if (arr[i] != NULL)
            s += arr[i];
        if (i < n-1)
            s += c;
    }
}

int main()
{
    std::string ws;

    char *arr[MAGIC_NUMBER];

    arr[0] = "you";
    arr[1] = "ate";
    arr[2] = "my";
    arr[3] = "lunch";

    join(arr, MAGIC_NUMBER, '-', ws);
    cout << "joined: " << ws << '\n';
}
