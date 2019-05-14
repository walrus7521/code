#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define exchg(A, B) { int t = A; A = B; B = t; } 

typedef struct list_t {
    struct list_t *next;
    int val;
} list_t;

typedef struct tree {
    struct tree *left, *right;
    int val;
} tree_t;

typedef struct graph_t {
    int n_vert;
    int m[8][8];
    int visited[8];
    int parent[8];
} graph_t;

// array abstractions
// queue, stack

#endif //_TYPES_H_
