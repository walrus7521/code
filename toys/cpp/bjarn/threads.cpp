#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Message {
public:
    string crap;
};

queue<Message*> mqueue;
condition_variable mcond;
mutex mmutex;

bool cancel = false;

void consumer()
{
    while (!cancel) {
        unique_lock<mutex> lck{mmutex};
        auto m = mqueue.front();
        cout << m->crap << endl;
        mqueue.pop();
        lck.unlock();
    }
}

void producer()
{
    Message *m = new Message();
    while (!cancel) {
        //Message m;
        m->crap = "wusup";
        unique_lock<mutex> lck{mmutex};
        mqueue.push(m);
        mcond.notify_one();
        //lck.unlock();
    }
}

int main()
{
    thread t1 {producer};
    thread t2 {consumer};

    this_thread::sleep_for(seconds{4});
    cancel = true;
    t1.join();
    t2.join();
}

