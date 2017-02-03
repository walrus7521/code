/* work derived from K&R */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MULTIPLIER = 31, NHASH = 255 };

typedef struct _pair {
    char  *key;
    void  *value;
    struct _pair *next;
} pair;

typedef struct _hashtable {
    unsigned int buckets;
    unsigned int multiplier;
    struct _pair **symtab;
} hashtable;

hashtable *create(unsigned int buckets, unsigned int multiplier)
{
    pair **sym;
    hashtable *hash;
    int i;
    hash = (hashtable *) malloc(sizeof(hashtable));
    sym = (pair **) malloc(buckets * sizeof(pair*));
    hash->symtab = sym;
    hash->buckets = buckets;
    hash->multiplier = multiplier;
    for (i = 0; i < (int) buckets; i++) {
        hash->symtab[i] = NULL;
    }
    return hash;
}

static unsigned int hash(char *str, unsigned int buckets, unsigned int multiplier)
{
    unsigned int h;
    unsigned char *p;

    h = 0;
    for (p = (unsigned char *) str; *p != '\0'; p++) {
        h = (multiplier * h) + *p;
    }
    return (h % buckets);
}

static pair* lookup(hashtable *hashtab, char *key, int create, void *value)
{
    int h;
    pair *sym, **symtab;
    symtab = hashtab->symtab;
    h = hash(key, hashtab->buckets, hashtab->multiplier);
    for (sym = symtab[h]; sym != NULL; sym = sym->next) {
        if (strcmp(key, sym->key) == 0) {
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

int find(hashtable *hashtab, char *key)
{
    pair *sym = lookup(hashtab, key, 0, 0);
    return (sym != NULL) ? 1 : 0;
}

pair *get(hashtable *hashtab, char *key)
{
    pair *sym = lookup(hashtab, key, 0, 0);
    return (sym != NULL) ? sym->value : NULL;
}

void set(hashtable *hashtab, char *key, void *value)
{
    pair *sym = lookup(hashtab, key, 1, value);
    if (sym) sym->value = value;
}

int hash_test()
{
    pair *sym;
    char *key = "dude";
    hashtable *hashtab;
    int val1, val2;
    hashtab = create(NHASH, MULTIPLIER);
    set(hashtab, key, 76);
    if (find(hashtab, key)) {
        val1= get(hashtab, key);
        val2 = val1 + 22;
        set(hashtab, key, val2);
        val2= get(hashtab, key);
        printf("found: %s %d -> %d\n", key, val1, val2);
    } else {
        printf("not found: %s\n", key);
    }
    return 0;
}

