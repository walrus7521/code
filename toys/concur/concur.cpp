#include <iostream>
#include <thread>
#include <vector>

class background_task
{
public:
    // functor
    void operator()() const {
        std::cout << "yo sup\n";
    }
};

struct func
{
    int& i;
    func(int& i_) :i(i_){}
    void operator()()
    {
        for (int j = 0; j < 1000000; ++j) {
            ;
        }
    }
};

void task1()
{
    std::cout << "yo dude\n";
}

void do_work(int id)
{
    std::cout << "yo task: " << id << std::endl;
}

int main()
{
    //
    std::cout << "concur level: " << std::thread::hardware_concurrency() << std::endl;

    background_task f;
    std::thread t1(f);
    std::thread t2{background_task()};
    // lambda
    std::thread t3([]{
        task1();
    });

    t1.join();
    t2.join();
    t3.join();

    std::vector<std::thread> threads;
    for (int i = 0; i < 16; ++i) {
        threads.push_back(std::thread(do_work, i));
    }

    std::for_each(threads.begin(), threads.end(),
            std::mem_fn(&std::thread::join));
}
