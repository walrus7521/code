#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// http://pfacka.binaryparadise.com/articles/guide-to-advanced-programming-in-C.html
// can be combined with mempool to add ref counting to mempool memory, useful
// for debugging
// 
#define MAX_REF_OBJ 100
#define RC_ERROR -1

struct mem_obj_t {
    void *ptr;
    uint16_t count;
};

static struct mem_obj_t references[MAX_REF_OBJ];
static uint16_t reference_count = 0;

/* create memory object and return handle */
uint16_t create(size_t size)
{

    if (reference_count >= MAX_REF_OBJ)
        return RC_ERROR;
    if (size) {
        void *ptr = calloc(1, size);

        if (ptr != NULL){
            references[reference_count].ptr = ptr;
            references[reference_count].count = 0;
            return reference_count++;
        }
    }
    return RC_ERROR;
}

/* get memory object and increment reference counter */
void* retain(uint16_t handle) 
{
    if(handle < reference_count && handle >= 0){
        references[handle].count++;
        return references[handle].ptr;
    } else {
        return NULL;
    }
}

/* decrement reference counter */
void release(uint16_t handle) 
{
    printf("release\n");
    if(handle < reference_count && handle >= 0){
        struct mem_obj_t *object = &references[handle];

        if (object->count <= 1){
            printf("released\n");
            free(object->ptr);
            reference_count--;
        } else {
            printf("decremented\n");
            object->count--;
        }
    }
}

int main()
{
    int ref = create(256); // ref counted handle of 256 bytes of mem
    char *name1 = (char *) retain(ref);
    char *name2 = (char *) retain(ref);
    release(ref);
    release(ref);
    char *name3 = (char *) retain(ref);
    printf("nm1 %p, nm2 %p, nm3 %p\n", name1, name2, name3);
}

