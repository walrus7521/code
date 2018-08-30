#include <thread>
#include <queue>
#include <mutex>

template <typename T>
class msgQueue
{
private:
    std::queue<T> mQueue;
    std::mutex mutex;
public:
    void pop()
    {
        std::lock_guard<std::mutex> qlock(mutex);
        mQueue.pop();
    }

    T front()
    {
        std::lock_guard<std::mutex> qlock(mutex);
        return mQueue.front();
    }

    int size()
    {
        std::lock_guard<std::mutex> qlock(mutex);
        return mQueue.size();
    }

    void push(T &data)
    {
        std::lock_guard<std::mutex> qlock(mutex);
        mQueue.push(data);
    }
};
