/*
 * This is example chapter 5 "Creating variables that are unique per thread."
 *
 */

#include <boost/noncopyable.hpp>
#include <boost/thread/tss.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>

class connection: boost::noncopyable {
public:
    void open(){}
    void send_result(int result){ std::cout << "result: " << result << std::endl; }
};

boost::thread_specific_ptr<connection> connection_ptr;

connection& get_connection() {
    connection* p = connection_ptr.get();
    if (!p) {
        std::cout << "new ptr" << std::endl;
        connection_ptr.reset(new connection);
        p = connection_ptr.get();
        p->open();
    }
    return *p;
}

void task() {
    int result;
    result = 42;
    get_connection().send_result(result); // first time to get a connection
    get_connection().send_result(result);
}

int main()
{
    boost::thread run1(&task);
    boost::thread run2(&task);
    boost::thread run3(&task);

    run1.join();
    run2.join();
    run3.join();
}
