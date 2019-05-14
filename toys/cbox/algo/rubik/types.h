#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

typedef struct list {
    struct list *next;
    int val;
} list;

typedef struct tree {
    struct tree *left, *right;
    int val;
} tree;

// array abstractions
// queue, stack

#endif //_TYPES_H_
