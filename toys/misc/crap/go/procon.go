package main

import (
    "fmt"
    "time"
    "sync"
)

const BUF_SIZE int = 5

type Buffer struct {
    buf [BUF_SIZE]int
    length int
};

var wg sync.WaitGroup

func Pro(ch chan<-int) {
    defer wg.Done()
    for i := 0; i < 10; i++ {
        ch <- i
        time.Sleep(time.Second * 1)
    }
}

func Con(ch <-chan int) {
    defer wg.Done()
    for {
        val := <-ch
        fmt.Println(val)
    }
}

func main() {
    ch := make(chan int)
    wg.Add(2)
    go Pro(ch)
    go Con(ch)
    wg.Wait()
    var input string
    fmt.Scanln(&input)
}

// produce random numbers
//void* producer(void *arg) {
//    buffer_t *buffer = (buffer_t*)arg;
//
//    while(1) {
//        pthread_mutex_lock(&buffer->mutex);
//
//        while (buffer->len == BUF_SIZE) { // full
//            // wait until some elements are consumed
//            pthread_cond_wait(&buffer->can_produce, &buffer->mutex);
//        }
//
//        // in real life it may be some data fetched from
//        // sensors, the web, or just some I/O
//        int t = rand();
//        printf("%p Produced: %d\n", pthread_self(), t);
//
//        // append data to the buffer
//        buffer->buf[buffer->len] = t;
//        ++buffer->len;
//
//        // signal the fact that new items may be consumed
//        pthread_cond_signal(&buffer->can_consume);
//        pthread_mutex_unlock(&buffer->mutex);
//    }
//
//    // never reached
//    return NULL;
//}

// consume random numbers
//void* consumer(void *arg) {
//    buffer_t *buffer = (buffer_t*)arg;
//
//    while(1) {
//        pthread_mutex_lock(&buffer->mutex);
//
//        // single consume -> use if
//        //if(buffer->len == 0) { // empty
//        // multiple consumers -> use while
//        while (buffer->len == 0) { // empty
//            // wait for new items to be appended to the buffer
//            pthread_cond_wait(&buffer->can_consume, &buffer->mutex);
//        }
//
//        // grab data
//        --buffer->len;
//        printf("%p Consumed: %d\n", pthread_self(), buffer->buf[buffer->len]);
//
//        // signal the fact that new items may be produced
//        pthread_cond_signal(&buffer->can_produce);
//        pthread_mutex_unlock(&buffer->mutex);
//    }
//
//    // never reached
//    return NULL;
//}

//int main(int argc, char *argv[]) {
//    buffer_t buffer = {
//        .len = 0,
//        .mutex = PTHREAD_MUTEX_INITIALIZER,
//        .can_produce = PTHREAD_COND_INITIALIZER,
//        .can_consume = PTHREAD_COND_INITIALIZER
//    };
//
//    pthread_t prod, cons;
//    pthread_create(&prod, NULL, producer, (void*)&buffer);
//    pthread_create(&cons, NULL, consumer, (void*)&buffer);
//
//    pthread_join(prod, NULL); // will wait forever
//    pthread_join(cons, NULL);
//
//    return 0;
//}

