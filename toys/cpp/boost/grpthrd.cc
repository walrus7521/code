/*
 * This is example 5 "Manipulating a group of threads."
 *
 */

#include <deque>
#include <boost/function.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/condition_variable.hpp>
#include <iostream>


class work_queue {
public:
    typedef boost::function<void(int n)> task_type;

    void push_task(const task_type& task) {
        boost::unique_lock<boost::mutex> lock(tasks_mutex_);
        tasks_.push_back(task);
        lock.unlock();
        //cond_.notify_one(); // wakeup one waiter.
        cond_.notify_all(); // all wakeup waiters.
    }

    task_type try_pop_task() {
        task_type ret;
        boost::lock_guard<boost::mutex> lock(tasks_mutex_);
        if (!tasks_.empty()) {
            ret = tasks_.front();
            tasks_.pop_front();
        }
        return ret;
    }

    task_type pop_task() {
        boost::unique_lock<boost::mutex> lock(tasks_mutex_);
        while (tasks_.empty()) {
            cond_.wait(lock); // wait for notify
            // continue to the next check for tasks_.empty()
            // there should be an entry
        }
        task_type ret = tasks_.front();
        tasks_.pop_front();
        return ret;
    }

private:
    std::deque<task_type>       tasks_;
    boost::mutex                tasks_mutex_;
    boost::condition_variable   cond_;

};


work_queue g_queue;

void do_nothing(int n){ std::cout << "yo sup: " << n << std::endl; }

const std::size_t tests_tasks_count = 3000;

void pusher() {
    for (std::size_t i = 0; i < tests_tasks_count; ++i) {
        g_queue.push_task(&do_nothing);
    }
}

void popper_sync() {
    for (std::size_t i = 0; i < tests_tasks_count; ++i) {
        g_queue.pop_task() // get task
            (42); // execute task
    }
}


int main()
{
    boost::thread_group threads;

    threads.create_thread(&popper_sync);
    threads.create_thread(&popper_sync);
    threads.create_thread(&popper_sync);
    threads.create_thread(&pusher);
    threads.create_thread(&pusher);
    threads.create_thread(&pusher);
    threads.join_all();

    assert(!g_queue.try_pop_task());
    g_queue.push_task(&do_nothing);
    assert(g_queue.try_pop_task());
}
