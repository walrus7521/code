#include <iostream>
#include "queue.hpp"

using namespace boost::interprocess; 

int main(int argc, char* argv[ ]) 
{
    int i;
    printf("consumer\n");

    shared_memory_object shm(open_only, "shq", read_write);
    mapped_region region(shm, read_write);

    void *mem = region.get_address();

    struct queue *q = static_cast<struct queue *>(mem);

    for (i = 0; i < q->size; i++) {

        scoped_lock<interprocess_mutex> lock(q->mutex);
        if (!q->data_avail) {
            q->cond_empty.wait(lock);
        }
        printf("recv[%02d]: (%02d, %02d)\n", i, q->entries[i].key, q->entries[i].value);
        q->data_avail = false;
        q->cond_full.notify_one();
    }

}

