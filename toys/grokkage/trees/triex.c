#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH (3)
#define LETTERS   (26)

typedef char Key[MAXLENGTH];
typedef struct trienode Trienode;
typedef struct entry Entry;

struct entry {
    struct entry *next;
    int id;
    Key key;
    char name[8];
};

struct trienode {
    Trienode *branch[LETTERS];
    Entry *ref;
};

Trienode *CreateNode(void)
{
    int ch;
    Trienode *new = (Trienode *) malloc(sizeof(Trienode));

    for (ch = 0; ch < LETTERS; ch++) {
        new->branch[ch] = NULL;
    }
    new->ref = NULL;
    return new;
}

Trienode *TrieSearch(Trienode *root, Key target)
{
    int i;
    for (i = 0; i < MAXLENGTH; i++) {
        if (target[i] == '\0') {
            break;
        } else {
            root = root->branch[target[i] - 'a'];
        }
    }
    if (root && !root->ref) {
        return NULL;
    }
    return root;
}

Trienode *InsertTrie(Trienode *root, Key newkey, Entry *newentry)
{
    int i;
    Trienode *saveroot;
    if (!root) {
        root = CreateNode();
    }
    saveroot = root;

    for (i = 0; i < MAXLENGTH; i++) {
        if (newkey[i] == '\0') {
            break;
        } else {
            if (!root->branch[newkey[i]-'a']) {
                root->branch[newkey[i]-'a'] = CreateNode();
            }
            root = root->branch[newkey[i]-'a'];
        }
    }

    if (root->ref != NULL) {
        printf("warning duplicate key\n");
        Entry *e = root->ref;
        root->ref = newentry;
        root->ref->next = e;
    } else {
        //printf("inserting entry: %s\n", *newentry);
        root->ref = newentry;
    }
    return saveroot;
}


int main()
{
    printf("trie\n");
    Trienode *root = NULL; 
    Trienode *searchroot = NULL; 

    Entry entry1 = { NULL, 42, "car", "cars" };
    root = InsertTrie(root, "car", &entry1);

    Entry entry2 = { NULL, 47, "car", "carpet" };
    root = InsertTrie(root, "car", &entry2);

    searchroot = TrieSearch(root, "cars");
    if (NULL != searchroot) {
        Entry *e = searchroot->ref;
        while (e) {
            if (!strcmp(e->name, "cars")) {
                printf("found: %s\n", e->name);
            }
            e = e->next;
        }
    }

    searchroot = TrieSearch(root, "carpet");
    if (NULL != searchroot) {
        Entry *e = searchroot->ref;
        while (e) {
            if (!strcmp(e->name, "carpet")) {
                printf("found: %s\n", e->name);
            }
            e = e->next;
        }
    }

    // 1. suck in dictionary
    // 2. create cli to query

}


