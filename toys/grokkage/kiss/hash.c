#include "types.h"

pair_t *new_pair(char *key, int value) {
    pair_t *p = malloc(sizeof(pair_t));
    p->value = value;
    p->next = NULL;
    strcpy(p->key, key);
    return p;
}

hash_t *new_hash() {
    hash_t *h = malloc(sizeof(hash_t));
    h->size = MAX_HASH;
    for (int i = 0; i < h->size; i++) h->p[i] = NULL;
    return h;
}

int hash(hash_t *h, char *key) {
    int len = strlen(key);
    int hval = 0;
    for (int i = 0; i < len; i++) { hval += key[i]; }
    return hval % h->size;
}

void insert(hash_t *h, char *key, int value) {
    pair_t *p = new_pair(key, value);
    int hval = hash(h, p->key);
    if (h->p[hval] == NULL) {
        h->p[hval] = p;
    } else {
        p->next = h->p[hval];
        h->p[hval] = p;
    }
}

int find(hash_t *h, char *key) {
    int hval = hash(h, key);
    pair_t *t = h->p[hval];
    while (t) {
        if (0 == strcmp(t->key, key)) { return t->value; }
        t = t->next;
    }
    return 0;
}

void show(hash_t *h) {
    for (int i = 0; i < MAX_HASH; i++) {
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
    if ((value = find(h, "bart"))) printf("found: bart -> %d\n", value);
    if ((value = find(h, "dude"))) printf("found: dude -> %d\n", value);
    if ((value = find(h, "chad"))) printf("found: chad -> %d\n", value);
    if ((value = find(h, "snrk"))) printf("found: chad -> %d\n", value);

    show(h);

}

