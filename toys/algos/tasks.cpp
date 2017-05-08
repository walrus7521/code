#include <thread>
#include <condition_variable>
#include <mutex>
#include <iostream>
#include <queue>

// todo, launch a long running task and wait for completion

std::mutex mx;
std::condition_variable event_signal;
std::queue<int> q;

bool finished = false;

void producer(int n) {
    for(int i=0; i<n; ++i) {
        std::lock_guard<std::mutex> lk(mx);
        q.push(i);
        std::cout << "pushing " << i << std::endl;
        event_signal.notify_all();
    }
    std::lock_guard<std::mutex> lk(mx);
    finished = true;
    event_signal.notify_all();
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lk(mx);
        event_signal.wait(lk, []{ return finished || !q.empty(); });
        while (!q.empty()) {
            std::cout << "consuming " << q.front() << std::endl;
            q.pop();
        }
        if (finished) break;
    }
}

void slave(int n)
{
    for(int i=0; i<n; ++i) {
        std::lock_guard<std::mutex> lk(mx);
        std::cout << "do task: " << i << std::endl;
        q.push(i);
        event_signal.notify_all();
    }
    std::lock_guard<std::mutex> lk(mx);
    finished = true;
    event_signal.notify_all();
}

void master()
{
    std::thread t1(slave, 10); // 10 is the int parameter to slave
    while (true) {
        std::unique_lock<std::mutex> lk(mx);
        event_signal.wait(lk, []{ return finished || !q.empty(); });
        while (!q.empty()) {
            std::cout << "cleanup task: " << q.front() << std::endl;
            q.pop();
        }
        if (finished) break;
    }
    t1.join();
    std::cout << "finished!" << std::endl;
}

void dual_procon()
{
    std::thread t1(producer, 10);
    std::thread t2(consumer);
    t1.join();
    t2.join();
    std::cout << "finished!" << std::endl;
}

int main() {
    //master();
    dual_procon();
}
