#include <stdio.h>
#include <stdlib.h>

typedef struct record {
} record_t;

typedef struct node {
} node_t;

node_t *insert(node_t *root, int key, int value)
{
    node_t *node = malloc(sizeof(node_t));
    return node;
}

int main()
{
    node_t *root = NULL;
    root = insert(root, 42, 17);
}

