#include <iostream>
#include <thread>
#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <chrono>
//#include <unistd.h>

using namespace std;

#define BUF_SIZE 5

// the buffer works like a stack for
// the sake of simplicity, if needed
// we may implement a queue
typedef struct {
    int buf[BUF_SIZE]; // the buffer
    size_t len; // number of items in the buffer
    condition_variable can_produce; // signaled when items are removed
    condition_variable can_consume; // signaled when items are added
    mutex m;
} buffer_t;

buffer_t buffer = {
        .len = 0,
        //.can_produce = PTHREAD_COND_INITIALIZER,
        //.can_consume = PTHREAD_COND_INITIALIZER
};


// produce random numbers
//void producer(void *arg) {
void producer()
{
    //lock_guard<mutex> guard(m);
    while(1) {
        unique_lock<mutex> lck(buffer.m);
        cout << "pro\n";
        //while (buffer.len == BUF_SIZE) { // full
            // wait until some elements are consumed
        buffer.can_produce.wait_for(lck,  
                bool((buffer.len < BUF_SIZE)));
        //}
#if 0

        // in real life it may be some data fetched from
        // sensors, the web, or just some I/O
        int t = rand();
        printf("%p Produced: %d\n", pthread_self(), t);

        // append data to the buffer
        buffer->buf[buffer->len] = t;
        ++buffer->len;

        // signal the fact that new items may be consumed
        pthread_cond_signal(&buffer->can_consume);
        pthread_mutex_unlock(&buffer->mutex);
#endif
        lck.unlock();
    }
}

// consume random numbers
//void consumer(void *arg)
void consumer()
{
    //lock_guard<mutex> guard(m);
    //buffer_t *buffer = (buffer_t*)arg;

    while(1) {
        unique_lock<mutex> lck(buffer.m);
        cout << "con\n";
#if 0

        // single consume -> use if
        //if(buffer->len == 0) { // empty
        // multiple consumers -> use while
        while (buffer->len == 0) { // empty
            // wait for new items to be appended to the buffer
            pthread_cond_wait(&buffer->can_consume, &buffer->mutex);
        }

        // grab data
        --buffer->len;
        printf("%p Consumed: %d\n", pthread_self(), buffer->buf[buffer->len]);

        // signal the fact that new items may be produced
        pthread_cond_signal(&buffer->can_produce);
        pthread_mutex_unlock(&buffer->mutex);
#endif
        lck.unlock();
    }

}

int main(int argc, char *argv[]) {
    buffer_t buffer = {
        .len = 0,
        //.mutex = PTHREAD_MUTEX_INITIALIZER,
        //.can_produce = PTHREAD_COND_INITIALIZER,
        //.can_consume = PTHREAD_COND_INITIALIZER
    };

    thread prod(producer);
    thread cons(consumer);

    prod.join(); // will wait forever
    cons.join();

    return 0;
}

