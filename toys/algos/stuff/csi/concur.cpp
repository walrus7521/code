#include "pch.hpp"
#include "Concur.hpp"

// interface-ize this
// http://codereview.stackexchange.com/questions/84109/a-multi-threaded-producer-consumer-with-c11

using namespace std;


void producer(Buffer *b)
{
    while (true) {
        int num = std::rand() % 100;
        Buffer_add(b, num);
        b->cout_mu.lock();
        std::cout << "Produced: " << num << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        b->cout_mu.unlock();
    }
 
}

void consumer(Buffer *b)
{
    while (true) {
        int num = Buffer_remove(b);
        b->cout_mu.lock();
        std::cout << "Consumed: " << num << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        b->cout_mu.unlock();
    }
}


int main()
{
    Buffer b;
        
    std::thread producer_thread(&producer, &b);
    std::thread consumer_thread(&consumer, &b);

    producer_thread.join();
    consumer_thread.join();
}
