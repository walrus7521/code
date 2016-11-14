#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <lcthw/radixmap.h>
#include <lcthw/dbg.h>

RadixMap *RadixMap_create(size_t max)
{
    RadixMap *map = calloc(sizeof(RadixMap), 1);
    check_mem(map);

    map->contents = calloc(sizeof(RMElement), max + 1);
    check_mem(map->contents);

    map->temp = calloc(sizeof(RMElement), max + 1);
    check_mem(map->temp);

    map->max = max;
    map->end = 0;

    return map;
error:
    return NULL;
}

void RadixMap_destroy(RadixMap *map)
{
    if (map) {
        free(map->contents);
        free(map->temp);
        free(map);
    }
}

// here is where we stopped

void RadixMap_sort(RadixMap *map)
{
}

RMElement *RadixMap_find(RadixMap *map, uint32_t key)
{
}

int RadixMap_add(RadixMap *map, uint32_t key, uint32_t value)
{
}

int RadixMap_delete(RadixMap *map, RMElement *el)
{
}



