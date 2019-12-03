#include <iostream>
#include "queue.hpp"

using namespace boost::interprocess; 

int main(int argc, char* argv[ ]) 
{
    printf("producer\n");
    try { 
        int i;

        struct shm_remove
        {
            shm_remove() { shared_memory_object::remove("shq"); }
            ~shm_remove(){ shared_memory_object::remove("shq"); }
        } remover;

        shared_memory_object shm (create_only, "shq", read_write);
     
        shm.truncate(256); // set size

        mapped_region region (shm, read_write);

        void * addr       = region.get_address();

        // create a shared queue
        struct queue *q = (struct queue *) addr;
        q->size = QUEUE_ENTRIES;
        q->data_avail = false;

        for (i = 0; i < q->size; i++) {
            scoped_lock<interprocess_mutex> lock(q->mutex);
            if(q->data_avail) {
                q->cond_full.wait(lock);
            }
            q->entries[i].key = 42 + i;
            q->entries[i].value = 17 + i;
            printf("sending[%02d]: (%02d, %02d)\n", i, q->entries[i].key, q->entries[i].value);

            q->cond_empty.notify_one();
            //Mark message buffer as full
            q->data_avail = true;
        }

    // more code follows
    } catch (interprocess_exception& e) { 
        // .. .  clean up 
        printf("woops parent is toast\n");
    }
}

