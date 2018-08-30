#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define FIFO_INITIALIZER(buffer) { buffer, sizeof(buffer) / sizeof(buffer[0]), 0, 0, 0, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER }

struct fifo {
    void **buffer;
    const int capacity;
    int size;
    int write;
    int read;
    pthread_mutex_t mutex;
    pthread_cond_t full;
    pthread_cond_t empty;
};

void fifo_put(struct fifo *fifo, void *value)
{
    pthread_mutex_lock(&(fifo->mutex));
    while (fifo->size == fifo->capacity) pthread_cond_wait(&(fifo->full), &(fifo->mutex));
    fifo->buffer[fifo->write] = value;
    ++fifo->size;
    ++fifo->write;
    fifo->write %= fifo->capacity;
    pthread_mutex_unlock(&(fifo->mutex));
    pthread_cond_broadcast(&(fifo->empty));
}

void *fifo_get(struct fifo *fifo)
{
    pthread_mutex_lock(&(fifo->mutex));
    while (fifo->size == 0) pthread_cond_wait(&(fifo->empty), &(fifo->mutex));
    void *value = fifo->buffer[fifo->read];
    --fifo->size;
    ++fifo->read;
    fifo->read %= fifo->capacity;
    pthread_mutex_unlock(&(fifo->mutex));
    pthread_cond_broadcast(&(fifo->full));
    return value;
}

int fifo_size(struct fifo *fifo)
{
    pthread_mutex_lock(&(fifo->mutex));
    int size = fifo->size;
    pthread_mutex_unlock(&(fifo->mutex));
    return size;
}

const int buffer_size = 10;
const int producers = 10;
const int producer_amount = 100;
const int consumers = 5;

void *producer(void *arg)
{
    int i;
    for (i = 0; i < producer_amount; ++ i) {
        int *value = malloc(sizeof(*value));
        *value = i;
        fifo_put(arg, value);
    }
}

void *consumer(void *arg)
{
    int i;
    for (i = 0; i < producer_amount * producers / consumers; ++ i) {
        int *value = fifo_get(arg);
        free(value);            
    }
}

int main()
{
    void *buffer[buffer_size];
    struct fifo fifo = FIFO_INITIALIZER(buffer);
    
    int i;
    pthread_t producers[producers];
    for (i = 0; i < sizeof(producers) / sizeof(producers[0]); ++ i) {
        pthread_create(&producers[i], NULL, producer, &fifo);
    }
    pthread_t consumers[consumers];
    for (i = 0; i < sizeof(consumers) / sizeof(consumers[0]); ++ i) {
        pthread_create(&consumers[i], NULL, consumer, &fifo);
    }
    for (i = 0; i < sizeof(producers) / sizeof(producers[0]); ++ i) {
        pthread_join(producers[i], NULL);
    }
    for (i = 0; i < sizeof(consumers) / sizeof(consumers[0]); ++ i) {
        pthread_join(consumers[i], NULL);
    }
}
