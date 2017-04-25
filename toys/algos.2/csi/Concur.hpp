#ifndef _CONCUR_H
#define _CONCUR_H

#include <thread>

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
