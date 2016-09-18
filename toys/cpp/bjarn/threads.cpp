#include <chrono> 
#include <condition_variable> 
#include <iostream> 
#include <mutex> 
#include <queue> 
#include <thread> 

// https://tatourian.com/2013/03/26/producer-consumer-inter-thread-communication-using-condition-variables-in-c/

// new: add is_full, is_empty cv's for bounded queue

using namespace std;

static const int MagicNumber = 8; // Unit test only, not for production code 

int main() 
{ 
    condition_variable  m_alarm;              // Notifies threads that more work is available 
    mutex               m_mutex;              // Synchronizes access to shared variables 
    queue<int>          m_queue;              // Accumulates data chunks 
    bool                m_isNotified = false; // This is a guard to prevent accidental spurious wakeups 
    bool                m_haveData   = true;  // Only used for sample to end consumer, not required in production

    thread producer([&m_mutex, &m_queue, &m_alarm, &m_isNotified, &m_haveData]() { 
        for (int i = 0; i < MagicNumber; ++i) { 
        this_thread::sleep_for(chrono::milliseconds(500));     // Executing some long operation 
            lock_guard<mutex> lock(m_mutex);  // Enter critical section 
            cout << "producer " << i << endl; 
            m_queue.push(i);                  // Add data chunk to the queue 
            m_isNotified = true;              // Consumer can be woken up and it is not a fluke (see spurious wakeups) 
            m_alarm.notify_one();             // Notify consumer 
        } 
        lock_guard<mutex> lock(m_mutex);      // Work is done, app can exit 
        m_isNotified = true; 
        m_haveData = false; 
        m_alarm.notify_one(); 
    }); 

    thread consumer([&m_mutex, &m_queue, &m_alarm, &m_isNotified, &m_haveData]() { 
        while (m_haveData) { // In production, this check will be done on whether there is more data in the queue 
            unique_lock<mutex> lock(m_mutex); // Must aquire unique_lock with condition variables 
            while (!m_isNotified) {           // Prevents from spurious wakeup 
                m_alarm.wait(lock);           // Wait for a signal from producer thread 
            } 
            while (!m_queue.empty()) {        // Process data and remove it from the queue 
                cout << "consumer " << m_queue.front() << endl; 
                m_queue.pop(); 
            } 
            m_isNotified = false;             // Protect from spurious wakeup 
        } 
    }); 

    // Join threads and finish app 
    producer.join(); 
    consumer.join(); 

    return 0; 
}
