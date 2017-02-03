/* work derived from K&R */
#ifndef _MYHASH_H_
#define _MYHASH_H_

#define hash32(x) ((x)*2654435761)

typedef struct _pair {
    u64 key;
    void  *value;
    struct list_head entry;
} pair;

typedef struct {
    unsigned int buckets;
    struct list_head *symlist;
} hashtable;

hashtable *hash_create(unsigned int buckets);
void hash_destroy(hashtable *hashtab);
int hash_find(hashtable *hashtab, u64 key);
pair *hash_get(hashtable *hashtab, u64 key);
void hash_set(hashtable *hashtab, u64 key, void *value);
void hash_dump(hashtable *hashtab);

#endif // _MYHASH_H_
