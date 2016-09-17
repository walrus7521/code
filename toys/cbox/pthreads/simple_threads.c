#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <pthread.h>

void do_one_thing(int *);
void do_another_thing(int *);
void do_wrap_up(int, int);

int shared_mem_id;
int *shared_mem_ptr;
int r1 = 0;
int r2 = 0;

int main()
{
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, (void *) do_one_thing, (void *) &r1);
    pthread_create(&thread2, NULL, (void *) do_another_thing, (void *) &r2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    do_wrap_up(r1, r2);
    return 0;
}



void do_one_thing(int *pnum_times) {
    int i, j, x;
    for (i = 0; i < 4; i++) {
        printf("do one thing\n");
        for (j = 0; j < 10000; j++) {
            x += i;
        }
        (*pnum_times)++;
    }
}

void do_another_thing(int *pnum_times) {
    int i, j, x;
    for (i = 0; i < 4; i++) {
        printf("do another thing\n");
        for (j = 0; j < 10000; j++) {
            x += i;
        }
        (*pnum_times)++;
    }
}

void do_wrap_up(int one_times, int another_times) {
    int total;
    total = one_times + another_times;
    printf("wrap up: one thing %d, another %d, total %d\n",
            one_times, another_times, total);

}



