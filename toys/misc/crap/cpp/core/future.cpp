#include <future>
#include <iostream>

int calculate_the_answer() { return 42; }
void do_stuff() {}

int main()
{
    std::future<int> the_answer = std::async(calculate_the_answer);
    do_stuff();
    std::cout << "answer: " << the_answer.get() <<std::endl;
}

