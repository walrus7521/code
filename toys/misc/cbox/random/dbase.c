#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MIN (2)
#define MAX (4)

typedef int key_t;

typedef struct {
    key_t key;
    int value;
} treeentry_t;

typedef struct treenode {
    int count;
    treeentry_t entry[MAX+1]; // 1-based
    struct treenode *branch[MAX+1]; // zero-based
} treenode_t;

bool search_node(key_t target, treenode_t *current, int *pos);

void init(treenode_t *root)
{
    int i;
    root->count = 0;
    for (i = 0; i < MAX+1; i++) {
        root->entry[i].key = 0;
        root->branch[i] = NULL;
    }
}

void push_in(treeentry_t medentry, treenode_t *medright, treenode_t *current, int pos)
{
    int i;
    for (i = current->count; i> pos; i--) {
        // shift all keys and branches to the right
        current->entry[i+1] = current->entry[i];
        current->branch[i+1] = current->branch[i];
    }
    current->entry[pos+1] = medentry;
    current->branch[pos+1] = medright;
    current->count++;
}

void split(treeentry_t medentry, treenode_t *medright, treenode_t *current, int pos,
           treeentry_t *newmedian, treenode_t **newright)
{
    int i;      // used for copying from *current to new node
    int median; // median position in the combined, overfull node
    if (pos <= MIN) median = MIN;
    else            median = MIN+1;
    // get a new node and put it on the right
    *newright = (treenode_t *) malloc(sizeof(treenode_t));
    for (i = median+1; i <= MAX; i++) {
        (*newright)->entry[i-median] = current->entry[i];
        (*newright)->branch[i-median] = current->branch[i];
    }
    (*newright)->count = MAX - median;
    current->count = median;
    if (pos <= MIN) push_in(medentry, medright, current, pos);
    else            push_in(medentry, medright, *newright, pos-median);
    *newmedian = current->entry[current->count];
    (*newright)->branch[0] = current->branch[current->count];
    current->count--;
}

bool push_down(treeentry_t newentry, treenode_t *current,
               treeentry_t *medentry, treenode_t **medright)
{
    int pos;
    if (current == NULL) { // empty tree, done
        *medentry = newentry;
        *medright = NULL;
        return true;
    } else {
        if (search_node(newentry.key, current, &pos)) {
            printf("warning: inserting duplicate key %d\n", newentry.key);
        }
        if (push_down(newentry, current->branch[pos], medentry, medright)) {
            push_in(*medentry, *medright, current, pos);
            return false;
        } else {
            split(*medentry, *medright, current, pos, medentry, medright);
            return true;
        }
        return false;
    }
}

treenode_t *insert(treeentry_t newentry, treenode_t *root)
{
    treeentry_t medentry; // potential new root
    treenode_t *medright; // right of medentry
    treenode_t *newroot;  // used to increase height
    if (push_down(newentry, root, &medentry, &medright)) {
        newroot = (treenode_t *) malloc(sizeof(treenode_t));
        newroot->count = 1;
        newroot->entry[1] = medentry; // key
        newroot->branch[0] = root;
        newroot->branch[1] = medright;
        return newroot;
    }
    return root;
}

void insert2(treeentry_t new_entry, treenode_t *root)
{
    printf("insert: %d\n", new_entry.key);
    root->count++;
    // 1-based indexing
    root->entry[root->count].key = new_entry.key;
#if 0
    int i;
    for (i = 0; i < MAX; i++) {
        if (root->entry[i].key < new_entry.key) {
        }
    }
#endif
}

void show_node(treenode_t *root)
{
    int i;
    for (i = 1; i <= root->count; i++) {
        printf("[%d] = %d\n", i, root->entry[i].key);
    }
}

bool search_node(key_t target, treenode_t *current, int *pos)
{
    //printf("search node: %d\n", target);
    if (target < current->entry[1].key) { // go left
        //printf("go left\n");
        *pos = 0;
        return false;
    } else {
        //printf("linear search - start at %d\n", current->count);
        for (*pos = current->count; target < current->entry[*pos].key && *pos > 1; (*pos)--) ;
        //printf("linear search - end at [%d] = %d\n", *pos, current->entry[*pos].key);
        return (target == current->entry[*pos].key);
    }
}

treenode_t *search_tree(key_t target, treenode_t *root, int *targetpos)
{
    if (!root) return NULL;

    else if (search_node(target, root, targetpos))
        return root;

    else
        return search_tree(target, root->branch[*targetpos], targetpos);
}

int main()
{
    treeentry_t e;
    int i;
    treenode_t *root = malloc(sizeof(treenode_t));
    memset(root, 0, sizeof(treenode_t));
    init(root);

    int a[] = {92, 42, 37, 19, 6, 54, 22, 23}; //, 9}; segfaults on any number less than last
    int len = sizeof(a) / sizeof(a[0]);

    for (i = 0; i < len; i++) {
        e.key = a[i];
        root = insert(e, root);
    }

    show_node(root);

    int targetpos = 0;
    for (i = 0; i < len; i++) {
        targetpos = 0;
        treenode_t *s = search_tree(a[i], root, &targetpos);
        if (s) printf("found [%d] => %d\n", targetpos, s->entry[targetpos].key);
    }
}

