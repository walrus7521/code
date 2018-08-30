/*
 * This is example 5 "Interrupting a thread."
 *  not working
 */

#include <algorithm>
#include <fstream>
#include <iterator>
#include <boost/thread.hpp>


void do_this(int data) {
    int i = 0;

    while (true) {
        boost::this_thread::interruption_point();
        boost::this_thread::yield();
    }
}

void do_that(boost::thread& t) {
    t.interrupt();
}

int main()
{
    boost::thread t1(boost::bind(&do_this, 42));
    //boost::thread t2(boost::bind(&t1));
    t1.join();
    t1.interrupt();
    //t2.join();
    std::cout << "called interrupt\n";
}
