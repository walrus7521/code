#ifndef _THREAD_H_
#define _THREAD_H_


#if defined (WIN32)
#define MUTEX_TYPE          HANDLE
#define MUTEX_SETUP(x)      (x) = Create=Mutex(NULL, FALSE, NULL)
#define MUTEX_CLEANUP(x)    CloseHandle(x)
#define MUTEX_LOCK(x)       WaitForSingleObject((x), INFINITE)
#define MUTEX_UNLOCK(x)     ReleaseMutex(x)
#define THREAD_ID           GetCurrentThreadId()

#elif _POSIX_THREADS
#define MUTEX_TYPE          pthread_mutex_t
#define MUTEX_SETUP(x)      pthread_mutex_init(&(x), NULL)
#define MUTEX_CLEANUP(x)    pthread_mutex_destroy(&(x))
#define MUTEX_LOCK(x)       pthread_mutex_lock(&(x))
#define MUTEX_UNLOCK(x)     pthread_mutex_unlock(&(x))
#define THREAD_ID           pthread_self()

#else
    #error You must define mutex operations appropriate for your platform
#endif

struct CRYPTO_dynlock_value {
    MUTEX_TYPE mutex;
};

void print_errors(void);

int THREAD_setup(void);
int THREAD_cleanup(void);

#endif // _THREAD_H_
