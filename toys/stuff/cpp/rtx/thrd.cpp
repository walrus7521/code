#include <chrono>
#include <thread>
#include <mutex>
#include <iostream>

using namespace std::chrono_literals;

std::mutex g_pages_mutex;

void thread_1()
{
    for (;;) {
        g_pages_mutex.lock();
        std::cout << "thread_1" << std::endl;
        std::this_thread::sleep_for(2s);
        g_pages_mutex.unlock();
    }
}

void thread_2()
{
    for (;;) {
        g_pages_mutex.lock();
        std::cout << "thread_2" << std::endl;
        std::this_thread::sleep_for(2s);
        g_pages_mutex.unlock();
    }
}

void do_something()
{
    std::thread t1(thread_1);
    std::thread t2(thread_2);

    t1.join();
    t2.join();
}

int main()
{
    do_something();

    return 0;
}

