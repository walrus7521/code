#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#ifndef _TYPES_H_
#define _TYPES_H_

#define exchg(X, Y) { \
    (X) = (X) ^ (Y);  \
    (Y) = (Y) ^ (X);  \
    (X) = (X) ^ (Y); }

/* array
 */
#define MAX_ARRAY (256)
typedef struct array {
    int size;
    int a[MAX_ARRAY];
} array_t;
typedef struct string {
    int size;
    int s[MAX_ARRAY];
} string_t;

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

#define MAX_RING (32)
typedef struct ring {
    int q[MAX_RING];
    int head;
    int tail;    
} ring_t;

/* graph
 */
#define MAX_VERT (16)
typedef struct graph {
    int n_vert;
    int m[MAX_VERT][MAX_VERT];
    int parent[MAX_VERT];
    int visited[MAX_VERT];
} graph_t;

/* tree
 */
typedef struct tree {
    struct tree *left;
    struct tree *right;
    int key;
} tree_t;

/* trie
 */
#define TRIE_SIZE (27)
#define TERM      (26)
typedef struct trie {
    struct trie *m[TRIE_SIZE];
} trie_t;

/* heap
 */
#define HEAP_SIZE (32)
typedef struct heap {
    int size;
    int h[HEAP_SIZE];
} heap_t;

/* hash
 */
#define MAX_HASH (101)
typedef struct pair {
    char key[16];
    int value;
    struct pair *next;
} pair_t;
typedef struct hash {
    int size;
    pair_t *p[MAX_HASH];
} hash_t;

#endif // _TYPES_H_

