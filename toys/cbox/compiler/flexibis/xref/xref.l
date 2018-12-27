
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* symbol table */
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

/* include file stack */
struct bufstack {
    struct bufstack *prev;
    YY_BUFFER_STATE bs;
    int lineno;
    char *filename;
    FILE *f;
} *curbs = 0;

int newfile(char *fn);
int popfile(void);
int defining;

%}

%option noyywrap yylineno nodefault

%x COMMENT
%x IFILE

/* universal character name */
UCN     (\\u[0-9a-fA-F]{4}|\\U[0-9a-fA-F]{8})
/* float exponent */
EXP     ([Ee][-+]?[0-9]+)
/* integer length */
ILEN    ([Uu](L|l|LL|ll)?|(L|l|LL|ll)[Uu]?)
            

%%

 /* comments */
"/*"                {BEGIN(COMMENT); }
<COMMENT>"*/"       {BEGIN(INITIAL); }
<COMMENT>([^*]|\n)+|.
<COMMENT><<EOF>>    { printf("%s:%d: Unterminated comment\n",
                        curfilename, yylineno); return 0; }
 /* C++ comment */
"//".*\n

 /* declaration keywords */
_Bool       |
_Complex    |
_Imaginary  |
auto        |
char        |
const       |
double      |
enum        |
extern      |
float       |
inline      |
int         |
long        |
register    |
restrict    |
short       |
signed      |
static      |
struct      |
typedef     |
union       |
unsigned    |
void        |
volatile    { defining = 1; }

 /* keywords  - ignore */
break
case
continue
default
do
else
for
goto
if
return
sizeof
switch
while

 /* constants */

 /* integers */
0[0-7]*{ILEN}?
[1-9][0-9]*{ILEN}?
0[Xx][0-9a-fA-F]+{ILEN}?

 /* decimal float */
([0-9]*\.[0-9]+|[0-9]+\.[0-9]+\.){EXP}?[flFL]?
[0-9]+{EXP}[flFL]?

 /* hex float */
0[Xx]([0-9a-fA-F]*\.[0-9a-fA-F]+|[0-9a-fA-F]+\.?)[Pp][-+]?[0-9]+[flFL]?

 /* punctuators */
"{"|"<%"|";"        { defining = 1; }

"["|"]"|"("|")"|"{"|"}"|"."|"->"
"++"|"--"|"&"|"*"|"+"|"-"|"~"|"!"
"/"|"%"|"<<"|">>"|"<"|">"|"<="|">="|"=="|"!="|"^"|"|"|"&&"|"||"
"?"|":"|";"|"..."|"\""|"\\"
"="|"*="|"/="|"%="|"+="|"-="|"<<="|">>="|"&="|"^="|"|="
","|"#"|"##"
"<:"|":>"|"%>"|"%:"|"%:%:"

 /* identifier */
([_a-zA-Z]|{UCN})([_a-zA-Z0-9]|{UCN})* {
    addref(yylineno, curfilename, yytext, defining); }

 /* whitespace */
[ \t\n]+

 /* continued line */
\\$

 /* some preprocessor stuff */
"#"" "*if.*\n
"#"" "*else.*\n
"#"" "endif.*\n
"#"" "define.*\n
"#"" "*line.*\n

 /* recognize an include */
^"#"[ \t]*include[ \t]*[\"<]    { BEGIN IFILE; }
<IFILE>[^ \t\n\">]+             {
                                    { int c;
                                      while ((c = input()) && c != '\n') ;
                                    }
                                    newfile(yytext);
                                    BEGIN INITIAL;
                                }

<IFILE>.|\n                     { fprintf(stderr, "%s:%d bad include line\n", 
                                        curfilename, yylineno);
                                  BEGIN INITIAL;
                                }

<<EOF>>                         { if (!popfile()) yyterminate(); }

 /* invalid character */
.                               {  printf("%s:%d: mystery char '%s'\n",
                                    curfilename, yylineno, yytext);
                                }


%%

int main(int argc, char **argv)
{
    int i;
    struct nlist *sp = NULL;

    for (i = 0; i < NHASH; i++) hashtab[i] = NULL;

    if (argc < 2) { /* just use stdin */
        fprintf(stderr, "need filename\n");
        return (1);
    }
    if (newfile(argv[1])) {
        yylex();
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
    //printf("addref: %d:%s\n", lineno, word);
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
            if (strlen(ref->name)) {
                printf("%s = %d\n", ref->name, ref->hashtag);
            }
            ref = ref->next;
        }
    }
}

int newfile(char *fn)
{
    FILE *f = fopen(fn, "r");
    struct bufstack *bs = malloc(sizeof(struct bufstack));

    if (!f) { perror(fn); return 0; }
    if (!bs) { perror("malloc"); exit(1); }

    if (curbs) curbs->lineno = yylineno;
    bs->prev = curbs;

    bs->bs = yy_create_buffer(f, YY_BUF_SIZE);
    bs->f = f;
    bs->filename = strdup(fn);
    yy_switch_to_buffer(bs->bs);
    curbs = bs;
    yylineno = 1;
    curfilename = bs->filename;
    return 1;
}

int popfile(void)
{
    struct bufstack *bs = curbs;
    struct bufstack *prevbs;

    if (!bs) return 0;

    fclose(bs->f);
    free(bs->filename);
    yy_delete_buffer(bs->bs);

    prevbs = bs->prev;
    free(bs);

    if (!prevbs) return 0;

    yy_switch_to_buffer(prevbs->bs);
    curbs = prevbs;
    yylineno = curbs->lineno;
    curfilename = curbs->filename;

    return 1;
}


