#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 4

typedef struct {
    int key;
    int value;
} treeentry_t;

typedef struct treenode {
    int count;
    treeentry_t entry[MAX+1];
    struct treenode *branch[MAX+1];
} treenode_t;

void insert(treeentry_t *e, treenode_t *t)
{
    int i;
    for (i = 0; i < MAX; i++) {
        if (t->entry[i].key < e->key) {
        }
    }
}

treeentry_t *find(treeentry_t *e, treenode_t *t)
{
    return NULL;
}

int main()
{
    treeentry_t e;
    int i;
    treenode_t tree;
    memset(&tree, 0, sizeof(treenode_t));

    for (i = 0; i < 4; i++) {
        e.key = i;
        insert(&e, &tree);
    }
}

