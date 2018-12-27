
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {
    struct nlist *next;
    char *name;
    char *filename;
    int hashtag;
    int flags;
    int lineno;
};

#define NHASH (9997)
static struct nlist *hashtab[NHASH];

struct nlist *lookup(char *);
void addref(int, char *, char *, int);
void printrefs();
static int symcompare(const void *xa, const void *xb);
static unsigned int symhash(char *sym);

char *curfilename;

%}

%option noyywrap yylineno nodefault case-insensitive

%%

a |
an |
and |
are |
as |
at |
be |
but |
for |
in |
is |
it |
of |
on |
or |
that |
the |
this |
to      /* ignore all these */

                    /* the following matches English words */
[a-z]+(\'(s|t))?    { addref(yylineno, curfilename, yytext, 0); }
.|\n                /* ignore everything else */

%%

int main(int argc, char **argv)
{
    int i;
    struct nlist *sp = NULL;

    for (i = 0; i < NHASH; i++) hashtab[i] = NULL;

    if (argc < 2) { /* just use stdin */
        curfilename = "(stdin)";
        yylineno = 1;
        yylex();
    } else {
        for (i = 1; i < argc; i++) {
            FILE *f = fopen(argv[i], "r");
            if (!f) {
                perror(argv[i]);
                return (1);
            }
            curfilename = argv[i];

            yyrestart(f);
            yylineno = 1;
            yylex();
            fclose(f);
        }
    }
    printrefs();
}

static unsigned int symhash(char *sym)
{
    unsigned int hash = 0;
    unsigned c;

    while ((c = *sym++) != '\0') hash = hash * 9 ^ c;

    return hash%NHASH;
}

struct nlist *lookup(char *sym)
{
    int hashval = symhash(sym);
    struct nlist *np;
    for (np = hashtab[hashval]; np != NULL; np = np->next) {
        if (strcasecmp(sym, np->name) == 0) return np;
    }
    return NULL;
}

void addref(int lineno, char *filename, char *word, int flags)
{
    struct nlist *np;
    if ((np = lookup(word)) == NULL)  { /* not found */
        /* don't allow duplicates of same line and file */
        np = malloc(sizeof(struct nlist));
        if (np == NULL) return;
        int hashval = symhash(word);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
        np->hashtag = hashval;
        np->name = strdup(word);
        np->filename = filename; // ??? already strdup'd
        np->lineno = lineno;
        np->flags = flags;
    }
}

/* print the references
 * sort the table alphabetically
 * then flip each entry's reflist to get it into forward order
 * and print it out
 */

/* aux function for sorting */
static int symcompare(const void *xa, const void *xb)
{
    const struct nlist *a = xa;
    const struct nlist *b = xb;

    if (!a->name) {
        if (!b->name) return 0;
        return 1;
    }
    if (!b->name) return 1;
    return strcasecmp(a->name, b->name);
}

void printrefs()
{
    struct nlist *np;

    for (int i = 0; i < NHASH; i++) {
        np = hashtab[i];
        struct nlist *ref = np;
        while (ref) {
            printf("%s = %d\n", ref->name, ref->hashtag);
            ref = ref->next;
        }
        printf("\n");
    }
}

