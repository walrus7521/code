#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH (3)
#define LETTERS   (26)

typedef char Key[MAXLENGTH];
typedef struct trienode Trienode;
typedef char * Entry;

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
    } else {
        printf("inserting entry: %s\n", *newentry);
        root->ref = newentry;
    }
    return saveroot;
}


int main()
{
    printf("trie\n");
    Trienode *root = NULL; 

    //Entry entry1 = "cars";
    //root = InsertTrie(root, "car", &entry1);

    Entry entry2 = "carpet";
    root = InsertTrie(root, "car", &entry2);

    //root = TrieSearch(root, "cars");
    //if (NULL != root) {
    //    printf("found: %s\n", *root->ref);
    //}

    root = TrieSearch(root, "carpet");
    if (NULL != root) {
        printf("found: %s\n", *root->ref);
    }

}


