#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "trie.h"

#if 0
#define TRIE_MAXLENGTH 10
#define TRIE_LETTERS   26

typedef struct _trie_pair {
    char key[TRIE_MAXLENGTH];
    int value;
} trie_pair;

typedef struct _trie_node {
    struct _trie_node *branch[TRIE_LETTERS];
    trie_pair *ref; // holds the string, also acts as the terminal sentinal
} trie_node;
#endif

trie_pair *pair_new(char key[4], int val) {
    trie_pair *pr = (trie_pair *) malloc(sizeof(trie_pair));
    strncpy(pr->key, key, 4);
    pr->value = val;
    return pr;
}

trie_node *trie_new()
{
    int ch;
    trie_node *tnode = (trie_node *) malloc(sizeof(trie_node));
    for (ch = 0; ch < TRIE_LETTERS; ch++) tnode->branch[ch] = NULL;
    tnode->ref = NULL;
    return tnode;
}

trie_node *trie_delete(trie_node *root, char *target)
/* need to delete last node if all its branches are NULL. 
   doing so requires us to set references to this node from 
   previous nodes to NULL, so we need a stack.
 */
{
    int i;
    for (i = 0; i < TRIE_MAXLENGTH && root; i++) {
        if (target[i] == '\0') break;
        else root = root->branch[target[i]-'a'];
    }
    if (root && !root->ref) return NULL;
    else if (!root) printf("not found: %s\n", target);
    else {
        printf("delete:      %s\n", root->ref->key);
        free(root->ref);
        root->ref = NULL;
    }
    return root;
}

trie_pair *trie_search(trie_node *root, char *target)
{
    int i;
    for (i = 0; i < TRIE_MAXLENGTH && root; i++) {
        if (target[i] == '\0') break;
        else {
            //printf("search[%d] = %c\n", i, target[i]);
            root = root->branch[target[i]-'a'];
        }
    }
    if ((root && !root->ref) || (!root)) {
         printf("not found:   %s\n", target);
         return NULL;
    } else printf("found entry: key %s, value %d\n", root->ref->key, root->ref->value);
    return root->ref;
}

trie_node *trie_insert(trie_node *root, trie_pair *entry)
{
    int i;
    trie_node *saveroot;
    
    if (!root) root = trie_new();
    saveroot = root;
    for (i = 0; i < TRIE_MAXLENGTH; i++) {
        if (entry->key[i] == '\0') break;
        else {
            if (!root->branch[entry->key[i]-'a']) { /* make a new node on root for key */
                root->branch[entry->key[i]-'a'] = trie_new(); // way cool!!
            }
            //printf("insert[%d] = %c\n", i, entry->key[i]);
            root = root->branch[entry->key[i]-'a']; /* move down appropriate branch */
        }
    } /* at this point, we have tested for all characters of key */
    if (root->ref != NULL)
        printf("warning: tried to insert a duplicate key...%s\n", entry->key);
    else
        root->ref = entry;
    return saveroot;
}

void trie_show(trie_node *T, int d)
{
    int i;
    if (T != NULL) {
        if (T->ref)
            printf("ref[%d]: key %s value %x\n", d, T->ref->key, T->ref->value);
        for (i = 0; i < TRIE_LETTERS; i++)
            trie_show(T->branch[i], d+1);
    }
}

int trie_test()
{
    trie_node *root = NULL;
    trie_pair *entry;
    root = trie_insert(root, pair_new("dog\0", 2));
    root = trie_insert(root, pair_new("cat\0", 3));
    root = trie_insert(root, pair_new("top\0", 4));
    root = trie_insert(root, pair_new("rat\0", 5));
    trie_show(root, 0);
    entry = trie_search(root, "cat");
    trie_delete(root, "dog");
    entry = trie_search(root, "dog");
    return 0;
}
