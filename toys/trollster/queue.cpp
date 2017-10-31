#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

// https://juanchopanzacpp.wordpress.com/2013/02/26/concurrent-queue-c11/
//
template <typename T>
class Queue
{
 public:
  Queue<T>() { std::cout << "ctor" << std::endl; }
  ~Queue<T>() { std::cout << "dtor" << std::endl; }
 
  T pop()
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty())
    {
      cond_.wait(mlock);
    }
    auto item = queue_.front();
    queue_.pop();
    return item;
  }
 
  void pop(T& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty())
    {
      cond_.wait(mlock);
    }
    item = queue_.front();
    queue_.pop();
  }
 
  void push(const T& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(item);
    mlock.unlock();
    cond_.notify_one();
  }
 
  void push(T&& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(std::move(item));
    mlock.unlock();
    cond_.notify_one();
  }
 
  bool empty()
  {
      return queue_.empty();
  }

 private:
  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable cond_;
};

int main()
{
    Queue<int> q;

    for (int i = 0; i < 4; ++i) {
        q.push(i);
    }

    while (!q.empty()) {
        int v = q.pop();
        std::cout << "pop: " << v << std::endl;
    }

}
