#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {
    struct nlist *next;
    char *name;
    int defn;
};

#define HASHSIZE 101
struct nlist *hashtab[HASHSIZE];

void show()
{
    int i;
    for (i = 0; i < HASHSIZE; i++) {
        if (hashtab[i] != NULL) {
            struct nlist *np = hashtab[i];
            while (np) {
                printf("name: %s -> %d\n", np->name, np->defn);
                np = np->next;
            }
        }
    }
}

unsigned int hash(char *s)
{
    unsigned int hashval;
    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np; // found
        }
    }
    return NULL;
}

struct nlist *install(char *name, int defn)
{
    struct nlist *np;
    unsigned int hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        np->name = strdup(name);
        np->defn = defn;
        hashval = hash(name);
        np->next = hashtab[hashval]; // insert into list
        hashtab[hashval] = np;
        //printf("added %s %d, hash %d\n", np->name, np->defn, hashval);
    } else { // already there -- replace it?
        printf("dup %s\n", name);
    }
    return np;
}

void init()
{
    int i;
    for (i = 0; i < HASHSIZE; i++) {
        hashtab[i] = NULL;
    }
}

#ifndef _NO_MAIN_
int main()
#else
int test_hash()
#endif
{
    struct nlist *n;
    char name[] = "bart"; int k = 42;
    init();
    install("bart", 42);
    install("cindy", 43);
    install("clarissa", 44);
    install("mackenzie", 45);
    show();
    return 0;
}

