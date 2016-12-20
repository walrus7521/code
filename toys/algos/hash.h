#include <stdlib.h>
#include <string.h>

typedef struct _pair {
    char *key;
    int val;
} pair;

typedef struct _list {
    pair p;
    struct _list *next;
} list;

typedef struct _hash {
    int nr_buckets;
    list **table;
} hash;

unsigned int hasher(char *str, unsigned int buckets, unsigned int multiplier)
{
    unsigned int h;
    unsigned char *p;

    h = 0;
    for (p = (unsigned char *) str; *p != '\0'; p++) {
        h = (multiplier * h) + *p;
    }
    return (h % buckets);
}

hash *createHash(int num_buckets) {
    hash *h = (hash *) malloc(sizeof(hash));
    h->table = (list **) calloc(num_buckets, sizeof(list *));
    int i;
    for (i = 0; i < num_buckets; i++) {
        h->table[i] = (list *) malloc(sizeof(list));
        h->table[i]->next = NULL;
    }
    h->nr_buckets = num_buckets;
    return h;
}

void insertHash(hash *h, char *key, int val)
{
    int b = hasher(key, h->nr_buckets, 31);
    printf("hasher: %d\n", b);
    if (h->table[b]->next == NULL) {
        list *node = (list *) malloc(sizeof(list));
        node->next = NULL;
        node->p.key = strdup(key);
        node->p.val = val;
        h->table[b]->next = node;
    } else {
        list *node = (list *) malloc(sizeof(list));
        node->next = NULL;
        node->p.key = strdup(key);
        node->p.val = val;
        node->next = h->table[b]->next;
        h->table[b]->next = node;
    }
}

void showHash(hash *h)
{
    int i;
    for (i = 0; i < h->nr_buckets; i++) {
        list *node = h->table[i]->next;
        while (node != NULL) {
            printf("key: %s, val: %d\n", node->p.key, node->p.val);
            node = node->next;
        }
    }
}

#if 0
    Hash(int nB) : B(nB) {
        table = new list<pair<string, int>>[B];
    }
    virtual ~Hash(){}
    void insert(string k, int v) {
        int b = hash2(k);
        pair<string, int> p = std::make_pair(k, v);
        table[b].push_back(p);
    }
    bool lookup(string k, int v) {
        int b = hash2(k);
        list<pair<string, int>>::iterator j; // used for bucket list entries
        for(j = table[b].begin(); j != table[b].end(); ++j) {
            if (k == j->first) {
                return true;
            }
        }
        return false;
    }
    pair<string, int> fetch(string k, int v) {
        int b = hash2(k);
        list<pair<string, int>>::iterator j; // used for bucket list entries
        for(j = table[b].begin(); j != table[b].end(); ++j) {
            if (k == j->first) {
                return *j;
            }
        }
        return std::make_pair(string("err"), -1);
    }
    void show() {
        list<pair<string, int>>::iterator j; // used for bucket list entries
        for (int i = 0; i < B; ++i) {
            for(j = table[i].begin(); j != table[i].end(); ++j) {
               cout << j->first << " => " << j->second << endl;
            }
        }
    }
private:
    int hash(int v) {
        return v % B;
    }
    int hash2(string str)
    {
        unsigned int h = 0;
        string::iterator it;
        for ( it = str.begin(); it < str.end(); ++it) {
            h = (31 * h) + *it;
        }        
        return (h % B);
    }
    int B;     // No. of hash buckets
    list<pair<string, int>> *table; // Pointer to an array containing buckets of hash entries
        
};

#endif
