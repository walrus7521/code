/*
 * This is a solution to crypt kicker 110204/843
 *   I encoded the dictionary and encrypted words like the following:
 *      and  => 123
 *    yertle => 123452
 *
 *   and stored the dictionary words in a trie for later searching
 *   for the encrypted values.
 *
 *   the only memory malloc'd is for the dictionary, all the decryption is 
 *   done on the fly.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* #define dprintf printf */
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
    entry *ref; /* holds the string, also acts as the terminal sentinal */
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
}



/*
 * 6
 * and
 * dick
 * jane
 * puff
 * spot
 * yertle
 * bjvg xsb hxsn xsb qymm xsb rqat xsb pnetfn
 * xxxx yyy zzzz www yyyy aaa bbbb ccc dddddd
 */


#define MAX_WORD 32
#define MAX_LINE 120
#define MAX_DICT 1024
#define MAX_ALPHA 26
#define INVALID_CODE '*'

typedef struct {
    char word[MAX_WORD];
    int   len;
    int   sig[MAX_WORD];
} crypto_entry;

typedef struct {
    int count;
    crypto_entry e[MAX_DICT];
} table;

trienode *root = NULL;

int find_encode(char c, char *encode, int len)
{
    int i;
    for (i = 1; i <= len; i++) {
        if (encode[i] != INVALID_CODE && encode[i] == c)
            return i;
    }
    return 0;
}

void make_sig(char *s, char *sig, int len)
{
    int i, k = 1, i_encoder = 1;;
    char c = s[0];
    char encode[MAX_WORD];
    dprintf("sig of: %s is ", s);
    for (i = 0; i < MAX_WORD; i++) encode[i] = INVALID_CODE;
    encode[1] = s[0];
    for (i = 0; i < len; i++) {
        if ((k = find_encode(s[i], encode, i_encoder))) {
            sig[i] = k;
        } else {
            encode[++i_encoder] = s[i];
            sig[i] = i_encoder;
        }
    }
    dprintf("normalized: ");
    for (i = 0; i < len; i++) dprintf("%d ", sig[i]);
    dprintf("\n");
}

void get_dict(int n)
{
    int i, len, j;
    char word[MAX_WORD], sig[MAX_WORD];
    key *newkey;
    entry *value;
    for (i = 0; i < n; i++) {
        value = (entry *) malloc(sizeof(entry));
        newkey = (key *) malloc(sizeof(key));
        memset(value, sizeof(entry), 0);
        memset(word, '\0', MAX_WORD);
        memset(sig, '\0', MAX_WORD);
        scanf("%s\n", word);
        len = strlen(word);
        make_sig(word, sig, len);
        sprintf(value->name, "%s", word);
        value->id = i;
        init_key(newkey, len);
        for (j = 0; j < len; j++) newkey->kval[j] = sig[j];
        root = trinsert(root, newkey, value);
        dprintf("word[%d] = %s, len %d\n", i, value->name, newkey->len);
    }
}

void decrypt(char *word, trienode *node)
{
    dprintf("decrypting: %s -> %s\n", word, node->ref->name);
    printf("%s ", node->ref->name);
}

void blanks(int len)
{
    int i;
    for (i = 0; i < len; i++) printf("*");
    printf(" ");
}

int get_cryptos(char *line)
/* return word count
 */
{
    int wc = 0, len, j;
    char word[MAX_WORD], sig[MAX_WORD];
    key newkey;
    trienode *node;
    while (*line != '\0') {
        memset(word, '\0', MAX_WORD);
        memset(sig, '\0', MAX_WORD);
        sscanf(line, "%s", word);
        len = strlen(word);
        make_sig(word, sig, len);
        init_key(&newkey, len);
        for (j = 0; j < len; j++) newkey.kval[j] = sig[j];
        node = trsearch(root, &newkey);
        if (node) decrypt(word, node);
        else      blanks(len);
        line += len+1;
        wc++;
    }
    return wc;
}

int main()
{
    int n, wc;
    char line[MAX_LINE], *pline;
    scanf("%d\n", &n);
    get_dict(n);
    memset(line, '\0', MAX_LINE);
    while (fgets(line, MAX_LINE, stdin)) {
        pline = line;
        wc = get_cryptos(pline);
        printf("\n");
        memset(line, '\0', MAX_LINE);
    }
    trshow(root, 0);
    return 0;
}

