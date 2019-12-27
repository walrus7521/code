#include <thread>
#include <iostream>
#include <vector>

// http://www.bogotobogo.com/cplusplus/C11/1_C11_creating_thread.php
//
void thread_function()
{
    std::cout << "thread function\n";
}

class MyFunctor
{
public:
    void operator()() {
        std::cout << "functor\n";
    }
};


int main()
{
    MyFunctor fnctor;
    std::thread t1(fnctor);
    std::thread t2(&thread_function);

    std::cout << "main thread\n";
    t1.detach();

    if (t1.joinable()) {
        std::cout << "t1 joining" << std::endl;
        t1.join();
    } else {
        std::cout << "t1 not joinable" << std::endl;
    }

    if (t2.joinable()) {
        std::cout << "t2 joining" << std::endl;
        t2.join();
    } else {
        std::cout << "t2 not joinable" << std::endl;
    }
    
    return 0;
}
