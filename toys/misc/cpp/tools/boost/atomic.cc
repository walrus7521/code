/*
 * This is example 5.3 "Fast access to common resource using atomics."
 *
 */

#include <cassert>
#include <cstddef>
#include <boost/thread/thread.hpp>
#include <boost/atomic.hpp>
#include <iostream>

boost::atomic<int> shared_i(0);

void do_inc() {
    for (std::size_t i = 0; i < 30000; ++i) {
        int i_snapshot = ++shared_i;
    }
}

void do_dec() {
    for (std::size_t i = 0; i < 30000; ++i) {
        int i_snapshot = --shared_i;
    }
}

void run() {
    boost::thread t1(&do_inc);
    boost::thread t2(&do_dec);
    t1.join();
    t2.join();

    assert(shared_i == 0); // Oops!
    std::cout << "shared_i == " << shared_i << std::endl;
}


int main()
{
    run();
}
