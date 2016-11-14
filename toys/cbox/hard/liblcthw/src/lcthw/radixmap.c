#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <lcthw/radixmap.h>
#include <lcthw/dbg.h>

RadixMap *RadixMap_create(size_t max)
{
    RadixMap *map = calloc(sizeof(RadixMap), 1);
    check_mem(map);


}

void RadixMap_destroy(RadixMap *map)
{
}

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



