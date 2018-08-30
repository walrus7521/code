/*
 * This is example 5.2 "Sync access to a common resource."
 *
 */

#include <cassert>
#include <cstddef>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <iostream>

int shared_i = 0;
boost::mutex i_mutex;

void do_inc() {
    for (std::size_t i = 0; i < 30000; ++i) {
        int i_snapshot;
        { // critical section begin
            boost::lock_guard<boost::mutex> lock(i_mutex);
            i_snapshot = ++shared_i;
        } // critical section end
    }
}

void do_dec() {
    for (std::size_t i = 0; i < 30000; ++i) {
        int i_snapshot;
        { // critical section begin
            boost::lock_guard<boost::mutex> lock(i_mutex);
            i_snapshot = --shared_i;
        } // critical section end
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
