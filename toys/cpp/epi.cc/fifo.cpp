#include "pch.hpp"
#include "Fifo.hpp"

using namespace std;

void test_fifo_int()
{
    Fifo<int> fifo = { .next = nullptr, .tail = nullptr, .key = 42 };
    Fifo_put(&fifo, 67);
    Fifo_put(&fifo, 42);
    Fifo_put(&fifo, 43);
    Fifo_put(&fifo, 68);
    Fifo_show(&fifo);
    while (!Fifo_empty(&fifo)) {
        cout << "get: " << Fifo_get(&fifo) << endl;
    }
}

void test_fifo_str()
{
    Fifo<string> fifo = { .next = nullptr, .tail = nullptr, .key = string("41") };
    Fifo_put(&fifo, string("67"));
    Fifo_put(&fifo, string("42"));
    Fifo_put(&fifo, string("43"));
    Fifo_put(&fifo, string("68"));
    Fifo_show(&fifo);
    while (!Fifo_empty(&fifo)) {
        cout << "get: " << Fifo_get(&fifo) << endl;
    }
}

int main()
{
    test_fifo_str();
}

