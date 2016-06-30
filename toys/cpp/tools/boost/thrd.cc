/*
 * This is example 5.1 "Creating an execution thread."
 *
 */

#include <algorithm>
#include <fstream>
#include <iterator>
#include <boost/thread.hpp>
#include <boost/bind.hpp>


void set_not_first_run() {
}

bool is_first_run();

void fill_file_with_data(char fill_char, std::size_t size, const char *filename) {
    std::ofstream ofs(filename);
    std::fill_n(std::ostreambuf_iterator<char>(ofs), size, fill_char);
    set_not_first_run();
}

void do_it(int data) {
    for (int i = 0; i < 4; ++i)
        std::cout << data+2*i << std::endl;
}

int main()
{
    boost::thread t(boost::bind(
            &fill_file_with_data,
            'g',
            64 * 1024,
            "save_file.txt"
    ));

    t.join();

#if 0
    boost::thread t(boost::bind(&do_it, 7));
    t.join();
    t.detach();
#endif
}
