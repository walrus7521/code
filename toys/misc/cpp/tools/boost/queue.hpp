#include <string>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/mapped_region.hpp>

#define QUEUE_ENTRIES (32)
 
typedef struct _entry {
    int key;
    int value;
} ENTRY;

struct queue {
    boost::interprocess::shared_memory_object *shm;
    boost::interprocess::interprocess_mutex mutex;
    boost::interprocess::interprocess_condition cond_empty;
    boost::interprocess::interprocess_condition cond_full;
    int size;
    bool data_avail;
    ENTRY entries[QUEUE_ENTRIES];
} queue;

