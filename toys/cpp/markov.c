#include <stdio.h>

enum {
    NPREF   = 2,    /* number of prefix words */
    NHASH   = 4093, /* size of state hash table array */
    MAXGEN  = 1000  /* maximum words generated */
};

typedef struct State State;
typedef struct Suffix Suffix;
struct State { /* prefix + suffix list */
    char    *pref[NPREF];
    Suffix  *suf;
    State   *next;
};

struct Suffix { /* list of suffixes */
    char    *word;
    Suffix  *next;
};

State *statetab[NHASH]; /* hash table of states */

unsigned int hash(char *s[NPREF])
{
    unsigned int h;
    unsigned char *p;
    int i;

    h = 0;
    for (i = 0; i < NPREF; i++) {
        for (p = (unsigned char *) s[i]; *p != '\0'; p++) {
            h = MULTIPLIER * h + *p;
        }
    }
    return h % NHASH;
}

State *lookup(char *prefix[NPREF], int create)
{
    int i, h;
    State *sp;

    h = hash(prefix);
    for (sp = statetab[h]; sp != NULL; sp = sp->next) {
        for (i = 0; i < NPREF; i++) {
            if (strcmp(prefix[i], sp->pref[i]) != 0) {
                break;
            }
        }
        if (i == NPREF) { /* found it */
            return sp;
        }
    }
    if (create) {
        sp = (State *) malloc(sizeof(State));
        for (i = 0; i < NPREF; i++) {
            sp->pref[i] = prefix[i];
        }
        sp->suf = NULL;
        sp->next = statetab[h];
        statetab[h] = sp;
    }
}

void add(char *prefix[NPREF], char *suffix)
{
    State *sp;
    sp = lookup(prefix, l);
    addsuffix(sp, suffix);

}

void build(char *prefix[NPREF], FILE *f)
{
    char buf[100], fmt[10];
    /* create a format string; %s could overflow buf */
    sprintf(fmt, "%%%ds", sizeof(buf)-1);
    while (fscanf(f, fmt, buf) != EOF) {
        add(prefix, strdup(buf));
    }
}
