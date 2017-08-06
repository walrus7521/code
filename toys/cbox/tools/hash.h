#ifndef _HASH_H_
#define _HASH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

enum { MULTIPLIER = 31, NBUCKETS = 255 };

typedef struct _map_entry {
    struct _map_entry *next;
    char  *key;
    int value;
} map_entry;

typedef struct _map {
    unsigned int buckets;
    unsigned int multiplier;
    struct _map_entry **prtab;
} map;

map *map_new(unsigned int buckets, unsigned int multiplier);
void map_delete(map *tab);
unsigned int integer_hash(unsigned long long key, unsigned int buckets);
unsigned int string_hash(char *str, unsigned int buckets, unsigned int multiplier);
map_entry* map_lookup(map *tab, char *key);
map_entry* map_insert(map *tab, char *key, int value);
map_entry* map_remove(map *tab, char *key);
void iterate(map *tab);
int hash_test();

#endif // _HASH_H_
