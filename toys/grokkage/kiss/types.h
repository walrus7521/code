#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* btree
 */
typedef struct record {
} record_t;

typedef struct node {
} node_t;


/* list
 */
typedef struct link {
    struct link *next;
    int key;
} link_t;

typedef struct {
    link_t *head;
    link_t *tail;
} list_t;


/* graph
 */
#define MAX_VERT (16)
typedef struct graph {
    int n_vert;
    int m[MAX_VERT][MAX_VERT];
    int que[MAX_VERT];
} graph_t;


/* tree
 */
typedef struct tree {
    struct tree *left;
    struct tree *right;
    int key;
} tree_t;


