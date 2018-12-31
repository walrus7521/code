#ifndef _hash_h_
#define _hash_h_

#include <stdbool.h>

typedef struct map *map_ptr;

map_ptr map_new();
void map_delete(map_ptr tab);
bool map_lookup(map_ptr tab, char *key, int *value);
bool map_insert(map_ptr tab, char *key, int value);
bool map_remove(map_ptr tab, char *key, int *value);
void iterate(map_ptr tab);

#endif // _hash_h_

