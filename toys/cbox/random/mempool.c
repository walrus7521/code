#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// http://pfacka.binaryparadise.com/articles/guide-to-advanced-programming-in-C.html
// can be combined with refcount.c to add reference counting to the pool

struct pool_t{
    void *ptr;
    size_t size;
    size_t used;
};

/* create memory pool*/
struct pool_t* create_pool(size_t size) {
    struct pool_t* pool = calloc(1, sizeof(struct pool_t));
    if(pool == NULL) return NULL;
    if (size) {
        void *mem = calloc(1, size);

        if (mem != NULL) {
            pool->ptr = mem;
            pool->size = size;
            pool->used = 0;
            return pool;
        }
    }
    free(pool);
    return NULL;
}

/* allocate memory from memory pool */
void* pool_alloc(struct pool_t* pool, size_t size) {

    if(pool == NULL)
        return NULL;

    size_t avail_size = pool->size - pool->used;

    if (size && size <= avail_size){
        void *mem = pool->ptr + pool->used;
        pool->used += size;
        return mem;
    }
    return NULL;
}

void pool_free(struct pool_t* pool, size_t size)
{
    if(pool == NULL)
        return;
    pool->used -= size;    
}

void show_pool(struct pool_t *pool)
{
    int avail = pool->size - pool->used;
    printf("size: %3d\tused %3d\tavail %3d\n", pool->size, pool->used, avail);
}

/* release memory for whole pool */
void delete_pool(struct pool_t* pool) {
    if (pool != NULL) {
        free(pool->ptr);
        free(pool);
    }
}

int main()
{
    struct pool_t *pool = create_pool(256);
    show_pool(pool);
    char *name = (char *) pool_alloc(pool, 16);
    show_pool(pool);
    if (name) {
        memcpy(name, "dave", 4);
        printf("name: %s\n", name);
        pool_free(pool, 16);
        show_pool(pool);
    }
}
