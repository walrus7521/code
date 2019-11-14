#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_HASH (101)
typedef struct pair {
    char key[16];
    int value;
    struct pair *next;
} pair_t;
typedef struct hash {
    int size;
    pair_t *p[MAX_HASH];
} hash_t;


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
    int i;
    hash_t *h = malloc(sizeof(hash_t));
    h->size = MAX_HASH;
    for (i = 0; i < h->size; i++) h->p[i] = NULL;
    return h;
}

int hash(hash_t *h, char *key)
{
    int i, len = strlen(key), hval=0;
    for (i = 0; i < len; i++) { hval += key[i]; }
    return hval % h->size;
}

void insert(hash_t *h, char *key, int value)
{
    pair_t *p = new_pair(key, value);
    int hval = hash(h, p->key);
    if (h->p[hval] == NULL) { h->p[hval] = p; } 
    else {
        p->next = h->p[hval];
        h->p[hval] = p;
    }
}

bool find(hash_t *h, char *key, int *value)
{
    int hval = hash(h, key);
    pair_t *t = h->p[hval];
    while (t) {
        if (0 == strcmp(t->key, key)) { *value = t->value; return true; }
        t = t->next;
    }
    return false;
}

void show(hash_t *h)
{
    int i;
    for (i = 0; i < MAX_HASH; i++) {
        if (h->p[i]) {
            pair_t *p = h->p[i];
            while (p) {
                printf("p->%s => %d : ", p->key, p->value);
                p= p->next;
            }
            printf("\n");
        }
    }
}

int main()
{
    hash_t *h = new_hash();
    pair_t *p;
    insert(h, "bart", 42);
    insert(h, "dude", 17);
    insert(h, "chad", 37);
    int value;
    if (find(h, "bart", &value)) printf("found: bart -> %d\n", value);
    if (find(h, "dude", &value)) printf("found: dude -> %d\n", value);
    if (find(h, "chad", &value)) printf("found: chad -> %d\n", value);
    if (find(h, "snrk", &value)) printf("found: snrk -> %d\n", value);
    show(h);
}

