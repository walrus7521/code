#include "types.h"

int hash(hash_t *h, char *key);

pair_t *new_pair(char *key, int value)
{
    pair_t *p = malloc(sizeof(pair_t));
    p->value = value;
    p->next = NULL;
    strcpy(p->key, key);
    return p;
}

hash_t *new_hash()
{
    hash_t *h = malloc(sizeof(hash_t));
    h->size = MAX_HASH;
    for (int i = 0; i < h->size; i++) h->p[i] = NULL;
    return h;
}

void insert(hash_t *h, pair_t *p)
{
    int hval = hash(h, p->key);
    if (h->p[hval] == NULL) {
        h->p[hval] = p;
    } else {
        p->next = h->p[hval];
        h->p[hval] = p;
    }
}

int hash(hash_t *h, char *key)
{
    int len = strlen(key);
    int hval = 0;
    for (int i = 0; i < len; i++) {
        hval += key[i];
    }
    return hval % h->size;
}

int find(hash_t *h, char *key, int value)
{
    int hval = hash(h, key);
    pair_t *t = h->p[hval];
    while (t) {
        if (0 == strcmp(t->key, key)) {
            return t->value;
        }
        t = t->next;
    }
    pair_t *n = new_pair(key, value);
    insert(h, n);
    return 0;
}

void show(hash_t *h)
{
    for (int i = 0; i < MAX_HASH; i++) {
        if (h->p[i]) {
            pair_t *p = h->p[i];
            while (p) {
                printf("p->%s => %d\n", p->key, p->value);
                p= p->next;
            }
        }
    }
}

int main()
{
    hash_t *h = new_hash();
    find(h, "bart", 42);
    find(h, "dude", 17);
    find(h, "chad", 37);
    show(h);
}

