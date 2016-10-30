#include <stdio.h>
#include <pthread.h>

typedef struct rdwr_var {
    int readers;
    int writers;
    pthread_mutex_t mutex;
    pthread_cond_t lock_free;
} rdwr_t;

typedef void * rdwrattr_t;

int rdwr_init(rdwr_t *rdwrp, rdwrattr_t *attrp)
{
    rdwrp->readers = 0;
    rdwrp->writers = 0;
    return 0;
}
       
int rdwr_rlock(rdwr_t *rdwrp)
{
    // lock mutex
    // while writers
    //   cond_wait
    //readers++
    // unlock mutex
    return 0;
}

int rdwr_wlock(rdwr_t *rdwrp)
{
    // lock mutex
    // while readers || writers
    //   cond_wait
    // writers++
    // unlock mutex
    return 0;
}

int rdwr_runlock(rdwr_t *rdwrp)
{
    // lock mutex
    // if readers == 0
    //      unlock mutex
    //      return -1
    // else
    //      readers--
    //      if readers == 0
    //          cond_signal
    //      unlock mutex
    //      return 0
    return 0;
}

int rdwr_wunlock(rdwr_t *rdwrp)
{
    // lock mutex
    // if writers == 0
    //      unlock mutex
    //      return -1
    //  else
    //      writers = 0 // can only be one
    //      cond_bcast
    //      unlock mutex
    //      return 0
    return 0;
}


int main()
{
    rdwr_t rdwr;
    rdwr_init(&rdwr, NULL);
    rdwr_rlock(&rdwr);
    rdwr_runlock(&rdwr);
    rdwr_wlock(&rdwr);
    rdwr_wunlock(&rdwr);
}

