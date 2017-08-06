#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

#include "hash.h"

map *map_new(unsigned int buckets, unsigned int multiplier) {
    map_entry **pr;
    map *hash;
    int i;
    hash = (map *) malloc(sizeof(map));
    pr = (map_entry **) malloc(buckets * sizeof(map_entry*));
    hash->prtab = pr;
    hash->buckets = buckets;
    hash->multiplier = multiplier;
    for (i = 0; i < (int) buckets; i++) {
        hash->prtab[i] = (map_entry *) malloc(sizeof(map_entry));
        hash->prtab[i]->next = NULL;
    }
    return hash;
}

void map_delete(map *tab) {
    map_entry **prtab = tab->prtab, *pr, *pr_prev, *tmp;
    int i;
    for (i = 0; i < tab->buckets; ++i) {
        pr = prtab[i]->next;
        pr_prev = prtab[i];
        while (pr) {
            tmp = pr;
            printf("free %s\n", pr->key);
            free(pr->key);
            pr_prev->next = pr->next;
            pr_prev = pr;
            pr = pr->next;
            free(tmp);
        }
        free(prtab[i]);
    }
    free(prtab);
    free(tab);
}

// this is knuths algorithm for integers, can be used for pointers as well
unsigned int integer_hash(unsigned long long key, unsigned int buckets)
{
    return ((key * 2654435761 % (unsigned int) pow(2,32)) % buckets);
}

unsigned int string_hash(char *str, unsigned int buckets, unsigned int multiplier)
{
    unsigned char *p;
    unsigned int h = 0;
    for (p = (unsigned char *) str; *p != '\0'; p++) {
        h = (multiplier * h) + *p;
    }
    return (h % buckets);
}

map_entry* map_lookup(map *tab, char *key)
{
    int h;
    map_entry *pr, **prtab;
    prtab = tab->prtab;
    h = string_hash(key, tab->buckets, tab->multiplier);
    for (pr = prtab[h]->next; pr != NULL; pr = pr->next) {
        if (strcmp(key, pr->key) == 0) {
            //printf("found %d -> %s\n", pr->value, pr->key);
            return pr;

        }
    }
    return NULL;
}

map_entry* map_insert(map *tab, char *key, int value)
{
    int h;
    char *dup_key;
    map_entry *pr, **prtab;
    prtab = tab->prtab;
    h = string_hash(key, tab->buckets, tab->multiplier);
    pr = (map_entry *) malloc(sizeof(map_entry));
    dup_key = strdup(key);
    pr->key = dup_key;
    pr->value = value;
    pr->next = prtab[h]->next;
    prtab[h]->next = pr;
    printf("map_inserted(%s, %d)\n", pr->key, pr->value);
    return pr;
}

map_entry* map_remove(map *tab, char *key)
{
    int h;
    map_entry *pr, *prev_pr, **prtab;
    prtab = tab->prtab;
    h = string_hash(key, tab->buckets, tab->multiplier);
    prev_pr = prtab[h];
    pr = prtab[h]->next;
    while (pr != NULL) {
        if (strcmp(key, pr->key) == 0) {
            printf("removing %d -> %s\n", pr->value, pr->key);
            prev_pr->next = pr->next;
            return pr;
        }
        prev_pr = pr;
        pr = pr->next;
    }
    return NULL;
}

void iterate(map *tab) {
    int i, j;
    map_entry **prtab = tab->prtab;
    printf("hash iterate...(enter)\n");
    for (i = 0; i < tab->buckets; ++i) {
        map_entry *pr = prtab[i]->next;
        j = 0;
        while (pr) {
            printf("tab[%d][%d] = %s -> %d\n", i, j, pr->key, pr->value);
            pr = pr->next;
            ++j;
        }
    }
    printf("hash iterate...(exit)\n");
}

int hash_test()
{
    map_entry *pr;
    char key[8];
    map *tab;
    tab = map_new(NBUCKETS, MULTIPLIER);

    map_insert(tab, "dude", 76);
    map_insert(tab, "dude", 76);
    map_insert(tab, "bart", 77);
    map_insert(tab, "cindy", 78);
    map_insert(tab, "zoey", 79);
    map_insert(tab, "rowdy", 80);

    strcpy(key, "dude");
    if ((pr = map_lookup(tab, key))) {
        printf("found: %s -> %d\n", key, pr->value);
    } else {
        printf("not found: %s\n", key);
    }

    iterate(tab);

    pr = map_remove(tab, key);
    if (pr) {
        printf("removed %s -> %d\n", pr->key, pr->value);
        free(pr);
    }
    if ((pr = map_lookup(tab, key))) {
        printf("found: %s -> %d\n", key, pr->value);
    } else {
        printf("not found: %s\n", key);
    }
    map_delete(tab);
    return 0;
}

