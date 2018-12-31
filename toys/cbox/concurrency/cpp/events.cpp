#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <condition_variable>
#include <string>
#include <iostream>

using namespace std;

class Message {
public:
    string name;
};

queue<Message> mqueue;
condition_variable mcond;
mutex mmutex;
bool my_is_empty = true;

int counter = 0;


void consumer()
{
    while (true) {
        unique_lock<mutex> lck{mmutex};
        my_is_empty = mqueue.empty();
        mcond.wait(lck, []{return my_is_empty == false;});

        auto m = mqueue.front();
        cout << m.name << endl;
        mqueue.pop();
        lck.unlock();
    }
}

void producer()
{
    int id = 0;
    while (true) {
        Message m;
        m.name = "dude: " + to_string(id++);
        unique_lock<mutex> lck{mmutex};
        mqueue.push(m);
        my_is_empty = false;
        mcond.notify_one();
    }
}

int main()
{
    thread t1 {producer};
    thread t2 {consumer};

    t1.join(); // wait for thread to terminate
    t2.join();

    cout << "done\n";
}

