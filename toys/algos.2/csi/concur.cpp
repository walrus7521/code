#ifndef _CONCUR_H
#define _CONCUR_H

#include <thread>
#include <iostream>
#include <deque>

struct Buffer
{
    // Add them as member variables here
    std::mutex mu, cout_mu;
    std::condition_variable cond;

    // Your normal variables here
    std::deque<int> buffer_;
    const unsigned int size_ = 10;

};

void Buffer_add(Buffer *buf, int num) {
    while (true) {
        std::unique_lock<std::mutex> locker(buf->mu);

        buf->cond.wait(locker, [buf](){return buf->buffer_.size() < buf->size_;});
        buf->buffer_.push_back(num);
        locker.unlock();
        buf->cond.notify_all();
        return;
    }
}

int Buffer_remove(Buffer *buf) {
    while (true)
    {
        std::unique_lock<std::mutex> locker(buf->mu);
        buf->cond.wait(locker, [buf](){return buf->buffer_.size() > 0;});
        int back = buf->buffer_.back();
        buf->buffer_.pop_back();
        locker.unlock();
        buf->cond.notify_all();
        return back;
    }
}



#endif // _CONCUR_H

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
