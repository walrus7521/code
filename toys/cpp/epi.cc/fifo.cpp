#include "pch.hpp"
#include "Fifo.hpp"

void test_fifo()
{
    int arr[32] = {0};
    Fifo<int> fifo = { .next = nullptr, .last = nullptr, .key = 42 };
    Fifo_put(&fifo, 67);
    Fifo_put(&fifo, 42);
    Fifo_put(&fifo, 43);
    Fifo_put(&fifo, 68);
    Fifo_show(&fifo);


    while (!Fifo_empty(&fifo)) {
        printf("get: %d\n", Fifo_get(&fifo));
    }
}

int main()
{
    test_fifo();
}

