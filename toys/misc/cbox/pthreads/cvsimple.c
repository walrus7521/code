#include <stdio.h>
#include <pthread.h>
#define TCOUNT 20
#define WATCH_COUNT 12

int count = 0;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t count_threshold_cv = PTHREAD_COND_INITIALIZER;
int thread_ids[3] = {0,1,2};

void watch_count(int *idp);
void inc_count(int *idp);

int main()
{
    int i;
    pthread_t threads[3];

    pthread_create(&threads[0], NULL, (void *) &inc_count, &thread_ids[0]);
    pthread_create(&threads[1], NULL, (void *) &inc_count, &thread_ids[1]);
    pthread_create(&threads[2], NULL, (void *) &watch_count, &thread_ids[2]);

    for (i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;

}

void watch_count(int *idp)
{
    pthread_mutex_lock(&count_mutex);
    while (1) {
        pthread_cond_wait(&count_threshold_cv, // system releases the mutex to wait
                &count_mutex);
        printf("watch_count(): Thread %d, Count is %d\n",
                *idp, count);
    }
    pthread_mutex_unlock(&count_mutex);
}

void inc_count(int *idp)
{
    int i;
    while (1) {
        pthread_mutex_lock(&count_mutex);
        count++;
        printf("inc_count(): Thread %d, old count %d, \
                new count %d\n", *idp, count-1, count);
        if (count % WATCH_COUNT == 0) {
            printf("signalling CV\n");
            //pthread_cond_signal(&count_threshold_cv); // wake one
            pthread_cond_broadcast(&count_threshold_cv); // wake all
        }
        pthread_mutex_unlock(&count_mutex);
    }
}


