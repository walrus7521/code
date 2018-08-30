#include <iostream>
#include "msg_queue.hpp"

int main()
{
    msgQueue<int> ibuf;
    int i;

    for (i = 0; i < 8; i++) {
        ibuf.push(i);
    }

    while (ibuf.size() > 0) {
        i = ibuf.front();
        ibuf.pop();
        std::cout << i << std::endl;
    }
}
