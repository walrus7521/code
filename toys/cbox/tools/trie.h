#ifndef _TRIE_H_
#define _TRIE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

trie_pair *pair_new(char key[4], int val);
trie_node *trie_new();
trie_node *trie_delete(trie_node *root, char *target);
trie_pair *trie_search(trie_node *root, char *target);
trie_node *trie_insert(trie_node *root, trie_pair *entry);
void trie_show(trie_node *T, int d);
int trie_test();

#endif // _TRIE_H_

