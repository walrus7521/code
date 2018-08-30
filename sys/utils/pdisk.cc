#include <sys/types.h>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <semaphore.h>
#include <poll.h>
#include <sys/time.h>
#include <errno.h>
#include <map>

using std::cout;
using std::endl;

pthread_t disk_thread1;
pthread_t disk_thread2;
pthread_mutex_t disk_mutex;
int tnum1 = 5;
int tnum2 = 7;

timespec addtime(timespec t1, timespec t2)
{
    timespec ret;
    ret.tv_sec = t1.tv_sec + t2.tv_sec;
    ret.tv_nsec =  t1.tv_nsec + t2.tv_nsec;
    if (ret.tv_nsec >= 1000000000) {
        ret.tv_nsec -= 1000000000;
        ++ret.tv_sec;
    }
    return ret;
}

timespec difftime(timespec start, timespec end)
{
    timespec ret;
    if ((end.tv_nsec - start.tv_nsec) < 0) {
        ret.tv_sec = end.tv_sec - start.tv_sec-1;
        ret.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    } else {
        ret.tv_sec = end.tv_sec - start.tv_sec;
        ret.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return ret;
}

void *start_routine(void *arg)
{
    struct timespec now, deadline;
    int *tnum = (int *) arg;
    int thread_no = *tnum;

    pthread_mutex_lock(&disk_mutex);
    cout << "thread num " << thread_no << endl;
    pthread_mutex_unlock(&disk_mutex);

    clock_gettime(CLOCK_REALTIME, &now);
    deadline.tv_sec = 10 /  1000000000;
    deadline.tv_nsec = 10 % 1000000000;
    deadline = addtime(now, deadline);
    std::cout << "yo dude\n";
    while (1) {
        pthread_mutex_lock(&disk_mutex);
        std::cout << "loop " << thread_no << endl;
        pthread_mutex_unlock(&disk_mutex);
        sched_yield();
        sleep(1); // = usleep(1000000);
    }
    clock_gettime(CLOCK_REALTIME, &now);
    if (difftime(now, deadline).tv_sec < 0) {
        cout << "timeout\n";
    } else {
        cout << "on time...\n";
    }
    return NULL;
}

void async_action(int sigNum, siginfo_t *siginfo, void*)
{
    cout << "async_sigaction\n";
}

void startup()
{
    struct sigaction sa;

    sa.sa_sigaction = async_action;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGPOLL, &sa, NULL);

    pthread_mutex_init(&disk_mutex, NULL);
    pthread_create(&disk_thread1, NULL, start_routine, (void*) &tnum1);
    pthread_create(&disk_thread2, NULL, start_routine, (void*) &tnum2);
    std::cout << "pthread created\n";
    pthread_join(disk_thread1, NULL);
    pthread_join(disk_thread2, NULL);
}

void alarm_handler(int signo)
{
    cout << "alarm went off \n";
}

int main()
{
    int rc;
    struct itimerval delay;

    signal(SIGALRM, alarm_handler);

    delay.it_interval.tv_sec = 10;
    delay.it_interval.tv_usec = 0;
    delay.it_value.tv_sec = 10;
    delay.it_value.tv_usec = 0;
    rc = setitimer(ITIMER_REAL, &delay, NULL);
    if (rc)
        cout << "timer create failed " << errno << endl;
    startup();

    return 0;
}

