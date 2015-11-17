#ifndef _TRIE_INTS_H_
#define _TRIE_INTS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//#define dprintf printf
#define dprintf(...)

#define MAXLENGTH 18
#define LETTERS   18
#define INVALID_KEY -1

typedef struct {
    char name[MAXLENGTH];
    int id;
} entry;
typedef struct {
    int len;
    int kval[MAXLENGTH];
} key;
typedef struct _trienode {
    struct _trienode *branch[LETTERS];
    entry *ref; // holds the string, also acts as the terminal sentinal
} trienode;

trienode *trcreatenode()
{
    int ch;
    trienode *tnode = (trienode *) malloc(sizeof(trienode));
    for (ch = 0; ch < LETTERS; ch++) tnode->branch[ch] = NULL;
    tnode->ref = NULL;
    return tnode;
}

void show_target(key *target)
{
    int i;
    for (i = 0; i < target->len; i++)
        dprintf("%d ", target->kval[i]);
}
trienode *trdelete(trienode *root, key *target)
{
    int i;
    dprintf("delete: "); show_target(target);
    for (i = 0; i < MAXLENGTH && root; i++) {
        if (target->kval[i] == INVALID_KEY) break;
        else root = root->branch[target->kval[i]];
    }
    if (root && !root->ref) { dprintf("null root\n"); return NULL; }
    else if (!root) { dprintf("not found: "); show_target(target); dprintf("\n"); }
    else {
        dprintf("=> %s\n", root->ref->name);
        free(root->ref);
        root->ref = NULL;
    }
    return root;
}

trienode *trsearch(trienode *root, key *target)
{
    int i;
    dprintf("search for: "); show_target(target);
    for (i = 0; i < MAXLENGTH && root; i++) {
        if (target->kval[i] == INVALID_KEY) break;
        else root = root->branch[target->kval[i]];
    }
    if ((root && !root->ref) || (!root))
    { dprintf("not found => "); show_target(target); dprintf("\n"); return NULL; }
    else dprintf("found => %s\n", root->ref->name);
    return root;
}

trienode *trinsert(trienode *root, key *newkey, entry *newentry)
{
    int i;
    trienode *saveroot;
    dprintf("inserting: "); show_target(newkey); dprintf(" = %s\n", newentry->name);
    if (!root) root = trcreatenode();
    saveroot = root;
    for (i = 0; i < MAXLENGTH; i++) {
        if (newkey->kval[i] == INVALID_KEY) break;
        else {
            if (!root->branch[newkey->kval[i]]) /* make a new node on root for newkey */
                root->branch[newkey->kval[i]] = trcreatenode();
            root = root->branch[newkey->kval[i]]; /* move down appropriate branch */
        }
    } /* at this point, we have tested for all characters of newkey */
    if (root->ref != NULL) { 
        dprintf("warning: tried to insert a duplicate key..."); show_target(newkey); dprintf("\n"); 
    } else
        root->ref = newentry;
    return saveroot;
}

void trshow(trienode *T, int d)
{
    int i;
    if (T != NULL) {
        if (T->ref)
            dprintf("ref[%d]: %s id %x\n", d, T->ref->name, T->ref->id);
        for (i = 0; i < LETTERS; i++)
            trshow(T->branch[i], d+1);
    }
}

void init_key(key *key, int len)
{
    int i;
    key->len = len;
    for (i = 0; i < MAXLENGTH; i++) key->kval[i] = INVALID_KEY;
//    for (i = 0; i < len; i++)
//        key->kval[i] = i;
}

int test_main()
{
    int i;
    trienode *root = NULL;
    key *newkey;
    entry *value;
    for (i = 0; i < 4; i++) {
        value = (entry *) malloc(sizeof(entry));
        memset(value, sizeof(entry), 0);
        sprintf(value->name, "%s%d", "bart", i);
        value->id = i;
        newkey = (key *) malloc(sizeof(key));
        init_key(newkey, 1+i);
        root = trinsert(root, newkey, value);
    }
    trshow(root, 0);
    //sprintf(newkey, "%s%d", "bart", 2);
    trsearch(root, newkey);
    trdelete(root, newkey);
    trsearch(root, newkey);

    return 0;
}

#endif // _TRIE_INTS_H_
