/* work derived from K&R */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NBUCKETS 255
typedef struct _pair {
    unsigned int key;
    unsigned int value;
    struct _pair *next;
} pair;

typedef struct _hashtable {
    unsigned int buckets;
    struct _pair **symtab;
} hashtable;

hashtable *hash_create(unsigned int buckets)
{
    pair **sym;
    hashtable *hash;
    int i;
    hash = (hashtable *) malloc(sizeof(hashtable));
    sym = (pair **) malloc(buckets * sizeof(pair*));
    hash->symtab = sym;
    hash->buckets = buckets;
    for (i = 0; i < (int) buckets; i++) {
        hash->symtab[i] = NULL;
    }
    return hash;
}

static unsigned int hash(unsigned int addr, unsigned int buckets)
{
    return (addr % buckets);
}

static pair* lookup(hashtable *hashtab, unsigned int key, int create, unsigned int value)
{
    int h;
    pair *sym, **symtab;
    symtab = hashtab->symtab;
    h = hash(key, hashtab->buckets);
    for (sym = symtab[h]; sym != NULL; sym = sym->next) {
        if (key == sym->key) {
            //printf("found %d -> %s\n", sym->value, sym->key);
            return sym;

        }
    }
    if (create) {
        sym = (pair *) malloc(sizeof(pair));
        sym->key = key;
        sym->value = value;
        sym->next = symtab[h];
        symtab[h] = sym;
        //printf("pair(%s, %d)\n", sym->key, sym->value);
    }
    return sym;
}

int find(hashtable *hashtab, unsigned int key)
{
    pair *sym = lookup(hashtab, key, 0, 0);
    return (sym != NULL) ? 1 : 0;
}

unsigned int get_ref(hashtable *hashtab, unsigned int key)
{
    pair *sym = lookup(hashtab, key, 0, 0);
    return (sym != NULL) ? sym->value : -1;
}

void set_ref(hashtable *hashtab, unsigned int key, unsigned int value)
{
    pair *sym = lookup(hashtab, key, 1, value);
    if (sym) sym->value = value;
}

int hash_test()
{
    int key = 77;
    hashtable *hashtab;
    int val1, val2;
    hashtab = hash_create(NBUCKETS);
    set_ref(hashtab, key, 76);
    if (find(hashtab, key)) {
        val1= get_ref(hashtab, key);
        val2 = val1 + 22;
        set_ref(hashtab, key, val2);
        val2= get_ref(hashtab, key);
        printf("found: %d %d -> %d\n", key, val1, val2);
    } else {
        printf("not found: %d\n", key);
    }
    return 0;
}

