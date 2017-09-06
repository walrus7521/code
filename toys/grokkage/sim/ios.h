#ifndef __ios_h_
#define __ios_h_

#include <pthread.h>
typedef pthread_mutex_t     kmutex;
typedef pthread_cond_t      kevent;
typedef pthread_t           kthread;
#define kmutex_lock         pthread_mutex_lock
#define kmutex_unlock       pthread_mutex_unlock
#define kevent_wait         pthread_cond_wait
#define kevent_notify_all   pthread_cond_broadcast
#define kevent_notify       pthread_cond_signal
#define kthread_create      pthread_create
#define KMUTEX_INIT        (PTHREAD_MUTEX_INITIALIZER)
#define KEVENT_INIT        (PTHREAD_COND_INITIALIZER)

// generic IO handling
enum {
    EVENT_STATE_COMPLETE,
    EVENT_STATE_PENDING
};

enum {
    EVENT_TYPE_NOTIFICATION, // multiple waiters released
    EVENT_TYPE_SYNCHRONIZATION // only one waiter is released
};

typedef int (*io_completion_routine)(void *dev, void *irp, void *ctx);

struct event {
    int state;
    int type;
    kmutex mtx;
    kevent cv;
    io_completion_routine cb;
};
 
enum {
    IO_REQUEST_READ,
    IO_REQUEST_WRITE,
    IO_REQUEST_IOCTL,
    IO_REQUEST_IRQ
};

struct irp {
    int io_type;
    char *buffer;
    int size;
    struct event event;
    void *dev;
};

#if 0
struct io_queue {
    void **buffer;
    int capacity;
    int size;
    int write;
    int read;
    kmutex mutex;
    kevent full;
    kevent empty;
};
struct io_queue *ioqueue_create();
void ioqueue_put(struct io_queue *io_queue, void *value);
void *ioqueue_get(struct io_queue *io_queue);
int ioqueue_size(struct io_queue *io_queue);
void *kio_thread(void *arg);
#endif
void ios_put(void *value);
void ios_init();
void ios_rescan();
void add_devices();
int init_event(struct event *ev, int type, io_completion_routine cb);
void wait_event(struct event *ev);




#endif // __ios_h_
