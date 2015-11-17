#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "queue.h"

#define dprintf printf
//#define dprintf(...)

#define LT(a,b) ((a) < (b))
#define EQ(a,b) ((a) == (b))

enum {
    MAX_BRANCH = 4,
    MIN_BRANCH = MAX_BRANCH/2,
    TRUE = 1,
    FALSE = 0,
    MAXLENGTH = 10,
};

typedef char Key;
typedef char Value;

typedef struct {
    Key key;
    Value value;
} pair;

typedef struct _btree_node {
    int count;
    pair entry[MAX_BRANCH+1];
    struct _btree_node *branch[MAX_BRANCH+1];
} btree_node;

static int search_node(Key target, btree_node *current, int *pos)
{
    int found;
    if (LT(target, current->entry[1].key)) {
        *pos = 0;
        return FALSE;
    } else {
        for (*pos = current->count; 
                LT(target, current->entry[*pos].key) && *pos > 1; 
                (*pos)--) {
            ;
        }
        found = EQ(target, current->entry[*pos].key);
        //printf("found? %d: %c -> %c\n", found, target, current->entry[*pos].key);
        return found;
    }
}

static btree_node *btree_search(Key target, btree_node *root, int *intra_node_target_pos)
{
    printf("btree_search - enter root: %p - key %c\n", root, target);
    if (!root) {
        return NULL;
    } else
    if (search_node(target, root, intra_node_target_pos)) {
        return root;
    } else {
        return btree_search(target, root->branch[*intra_node_target_pos], intra_node_target_pos);
    }
}

static void btree_push_in(pair medentry, btree_node *medright, 
            btree_node *current, int pos)
{
    int i;
    for (i = current->count; i > pos; i--) {
        current->entry[i+1] = current->entry[i];
        current->branch[i+1] = current->branch[i];
    }
    current->entry[pos+1] = medentry;
    current->branch[pos+1] = medright;
    current->count++;
    //printf("push_in: count %d\n", current->count);
}

static void btree_split(pair medentry, btree_node *medright, 
           btree_node *current, int pos, pair *newmedian, 
           btree_node **newright)
{
    int i;
    int median;
    if (pos <= MIN_BRANCH) {
        median = MIN_BRANCH;
    } else {
        median = MIN_BRANCH+1;
    }
    *newright = (btree_node *) malloc(sizeof(btree_node));
    for (i = median+1; i <= MAX_BRANCH; i++) {
        (*newright)->entry[i-median] = current->entry[i];
        (*newright)->branch[i-median] = current->branch[i];
    }
    (*newright)->count = MAX_BRANCH - median;
    current->count = median;
    if (pos <= MIN_BRANCH) {
        btree_push_in(medentry, medright, current, pos);
    } else {
        btree_push_in(medentry, medright, *newright, pos-median);
    }
    *newmedian = current->entry[current->count];
    (*newright)->branch[0] = current->branch[current->count];
    current->count--;
}

static int btree_push_down(pair newentry, btree_node *current, 
             pair *medentry, btree_node **medright)
{
    int pos;
    if (current == NULL) {
        *medentry = newentry;
        *medright = NULL;
        return TRUE;
    } else {
        if (search_node(newentry.key, current, &pos)) {
            printf("warning: inserting duplicate key into B-Tree..\n");
        }
        if (btree_push_down(newentry, current->branch[pos], 
                                 medentry, medright)) {
            if (current->count < MAX_BRANCH) {
                btree_push_in(*medentry, *medright, current, pos);
                return FALSE;
            } else {
                btree_split(*medentry, *medright, current, pos, 
                                 medentry, medright);
                return TRUE;
            }
        }
        return FALSE;
    }
}

btree_node *btree_insert(pair newentry, btree_node *root)
{
    pair medentry;
    btree_node *medright;
    btree_node *newroot;

    if (btree_push_down(newentry, root, &medentry, &medright)) {
        newroot = (btree_node *) malloc(sizeof(btree_node));
        newroot->count = 1;
        newroot->entry[1] = medentry;
        newroot->branch[0] = root;
        newroot->branch[1] = medright;
        return newroot;
    }
    return root;
}

btree_node *btree_create()
{
    int i;
    btree_node *root;
    root = (btree_node *) malloc(sizeof(btree_node));
    root->count = 0;
    for (i = 0; i < MAX_BRANCH; i++) {
        root->branch[i] = NULL;
    }
    return root;
}

void btree_find(btree_node *root, Key key)
{
    btree_node *find;
    int i;
    find = btree_search(key, root, &i);
    if (find) {
        printf("found: %c\n", find->entry[i].key);
    }
}

btree_node *btree_show(btree_node *root)
{
    int pos;
    int counter = 1;
    char c;
    queue *q = slist_init();
    link *t;
    btree_node *node, *tnode;
    printf("btree_show - enter root: %p\n", root);
    if (!root)
        return NULL;
    enqueue(q, root);
    while (!slist_empty(q)) {
        t = dequeue(q);
        node = t->value;
        for (pos = 0; pos < node->count+1; pos++) {
            c = node->entry[pos].key;
            if (isalpha(c)) {
                printf(" entry[%d]=%c\n", pos, node->entry[pos].key);
            }
            if (node->branch[pos] != NULL) {
                tnode = node->branch[pos];
                enqueue(q, tnode);
                counter++;
            }
        }
    }
    printf("num nodes %d\n", counter);
    return NULL;
}

int btree_test()
{
    Key keys[] = {'a','g','o','y','f','b','w','k','d','h','m','v','j','e','s','i','r','x','c','z','q','l','n','t','u','p'};
    int num_keys;
    btree_node *root;
    pair entry;
    int i;
    dprintf("btree demo..\n");
    root = btree_create();
#if 1
    num_keys = sizeof(keys) / sizeof(char);
    for (i = 0; i < num_keys; i++) {
        entry.key = keys[i];
        root = btree_insert(entry, root);
    }
    btree_show(root);
#endif
#if 0
    for (i = 'a'; i <= 'z'; i++) {
        entry.key = (char) i;
        root = btree_insert(entry, root);
    }
    //btree_find(root, 'y');
    //btree_find(root, 'c');
    //btree_find(root, 'z');
    btree_show(root);
#endif
    return 0;
}

