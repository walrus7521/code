#include <iostream>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
//#include <libs/interprocess/example/doc_anonymous_mutex_shared_data.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess; 

#define QUEUE_ENTRIES (32)
 
typedef struct _entry {
    int key;
    int value;
} ENTRY;

struct queue {
    int size;
    boost::interprocess::interprocess_mutex mutex;
    boost::interprocess::interprocess_condition cond_empty;
    boost::interprocess::interprocess_condition cond_full;
    bool data_avail;
    ENTRY entries[QUEUE_ENTRIES];
} queue;

boost::interprocess::interprocess_mutex mutex;

void dump_queue(struct queue *q)
{
    int i;
    //scoped_lock<interprocess_mutex> lock(q->mutex);
    for (i = 0; i < q->size; i++) {
        printf("q[%02d]: key: %02d, value: %02d\n", i, q->entries[i].key, q->entries[i].value);
    }
}

void init_queue(struct queue *q)
{
    int i;

    for (i = 0; i < q->size; i++) {
        scoped_lock<interprocess_mutex> lock(q->mutex);
        if(q->data_avail) {
            q->cond_full.wait(lock);
        }
        
        q->entries[i].key = 42 + i;
        q->entries[i].value = 17 + i;

        q->cond_empty.notify_one();
        //Mark message buffer as full
        //q->data_avail = true;
    }
}

int main(int argc, char* argv[ ]) 
{
    if (argc == 1) {
        try { 

            struct shm_remove
            {
                shm_remove() { shared_memory_object::remove("shq"); }
                ~shm_remove(){ shared_memory_object::remove("shq"); }
            } remover;

            // create the first shared memory object.: 
            //    create_only creates a new object
            //    open_only opens existing object
            shared_memory_object shm (create_only, "shq", read_write);
     
            // setting the size of the shared memory
            shm.truncate(256);

            // map the shared memory to current process 
            mapped_region region(shm, read_write); 

            // create a shared queue
            struct queue shq;
            shq.size = QUEUE_ENTRIES;
            shq.data_avail = false;
            init_queue(&shq);

            // access the mapped region using get_address
            //Write all the memory to 1
            //std::memset(region.get_address(), 1, region.get_size());
            std::memcpy(region.get_address(), &shq, sizeof(struct queue));
            //std::strcpy(static_cast<char* >(region.get_address()), "wusup\n");
        
            //Launch child process
            std::string s(argv[0]); s += " child ";
            printf("parent launching: %s\n", s.c_str());
            
            if(0 != std::system(s.c_str())) return 1;
            //while (1) ;

        // more code follows
        } catch (interprocess_exception& e) { 
            // .. .  clean up 
            printf("woops parent is toast\n");
        }
    } else {
        printf("child launched\n");

        //Open already created shared memory object.
        shared_memory_object shm (open_only, "shq", read_only);

        //Map the whole shared memory in this process
        mapped_region region(shm, read_only);

        //Check that memory was initialized to 1
        void *mem = static_cast<char*>(region.get_address());

        //Construct the shared structure in memory
        //shared_memory_log * data = static_cast<shared_memory_log*>(addr);

        struct queue *lq = static_cast<struct queue *>(mem);
        dump_queue(lq);

        //for(std::size_t i = 0; i < region.get_size(); ++i)
        //    if(*mem++ != 1)
        //        return 1;   //Error checking memory
   }
}

