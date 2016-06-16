#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLENGTH 10
#define LETTERS   26
//typedef char entry[MAXLENGTH];
typedef struct _entry {
    char name[MAXLENGTH];
    int id;
} entry;
typedef char key[MAXLENGTH];
typedef struct _trienode {
    struct _trienode *branch[LETTERS];
    struct _entry *ref; // holds the string, also acts as the terminal sentinal
} trienode;

trienode *trcreatenode()
{
    int ch;
    trienode *tnode = (trienode *) malloc(sizeof(trienode));
    for (ch = 0; ch < LETTERS; ch++) {
        tnode->branch[ch] = NULL;
    }
    tnode->ref = NULL;
    return tnode;
}

trienode *trdelete(trienode *root, key target)
{
    int i;
    for (i = 0; i < MAXLENGTH && root; i++) {
        if (target[i] == '\0') {
            break;
        } else {
            root = root->branch[target[i]-'a'];
        }
    }
    if (root && !root->ref) {
        printf("not found: %s\n", target);
        return NULL;
    } else
    if (!root) {
        printf("not found: %s\n", target);
    } else {
        printf("delete:     %s\n", root->ref->name);
        free(root->ref);
        root->ref = NULL;
    }
    return root;
}

trienode *trsearch(trienode *root, key target)
{
    int i;
    for (i = 0; i < MAXLENGTH && root; i++) {
        if (target[i] == '\0') {
            break;
        } else {
            root = root->branch[target[i]-'a'];
        }
    }
    if (root && !root->ref) {
        printf("not found: %s\n", target);
        return NULL;
    } else
    if (!root) {
        printf("not found: %s\n", target);
    } else {
        printf("found:     %s\n", root->ref->name);
    }
    return root;
}

trienode *trinsert(trienode *root, key newkey, entry *newentry)
{
    int i;
    trienode *saveroot;

    printf("inserting: key %s val %s\n", newkey, newentry->name);
    if (!root) {
        root = trcreatenode();
    }
    saveroot = root;

    for (i = 0; i < MAXLENGTH; i++) {
        if (newkey[i] == '\0') {
            break;
        } else {
            if (!root->branch[newkey[i]-'a']) {
                /* make a new node on the root for newkey */
                root->branch[newkey[i]-'a'] = trcreatenode();
            }
            /* move down the appropriate branch */
            root = root->branch[newkey[i]-'a'];
        }
    }
    /* at this point, we have tested for all characters of newkey */
    if (root->ref != NULL) {
        printf("warning: tried to insert a duplicate key...%s\n", newkey);
    } else {
        root->ref = newentry;
    }
    return saveroot;
}

void trshow(trienode *T, int d)
{
    int i;
    if (T != NULL) {
        if (T->ref) {
            printf("ref[%d]: %s id %x\n", d, T->ref->name, T->ref->id);
        }
        for (i = 0; i < LETTERS; i++) {
            trshow(T->branch[i], d+1);
        }
    }
}

void usage()
{
    printf("i: insert <string>, f: find <string>, d: delete <string>, s: show trie, q/x: exit\n");
}

void set_key_val(key k, entry *e, char *m, int len)
{
    int i;
    for (i = 0; i < len; i++) {
        k[i] = m[i];
        e->name[i] = m[i];
    }
}

void trie_test()
{
    int id = 1;
    trienode *root = NULL;
    key newkey;
    entry *value;
    unsigned char c;
    while (1) {
        putchar('$'); putchar(' ');
        c = (unsigned char) getchar();
        switch (c) {
            case 'i': // insert
                printf(" insert: ");
                value = (entry *) malloc(sizeof(entry));
                memset(value, sizeof(entry), 0);
                scanf("%s", value->name);
                value->id = ++id;
                sprintf(newkey, "%s", value->name);
                root = trinsert(root, newkey, value);
                getchar();
                break;
            case 'f': // find
                printf(" find: ");
                scanf("%s", (char *) &newkey);
                trsearch(root, newkey);
                getchar();
                break;
            case 'd': // delete
                printf(" delete: ");
                scanf("%s", (char *) &newkey);
                trdelete(root, newkey);
                getchar();
                break;
            case 's': // show
                trshow(root, 0);
                getchar();
                break;
            case '?': // usage
                usage();
                getchar();
                break;
            case 'q': // quit
            case 'x': // quit
                exit(0);
            default:
                break;
        }
    }
}

