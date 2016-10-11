#include <stdio.h>

typedef struct Symbol Symbol;
typedef struct Tree Tree;

struct Symbol {
    int value;
    char *name;
};

struct Tree {
    int op;
    int value;
    Symbol *symbol;
    Tree *left;
    Tree *right;
};

int pushop(Tree *t)  { return 0; }
int pushsop(Tree *t) { return 0; }
int addop(Tree *t)   { return 0; }
int divop(Tree *t)   { return 0; }
int maxop(Tree *t)   { return 0; }
int asnop(Tree *t)   { return 0; }

enum {
    NUMBER,
    VARIABLE,
    ADD,
    DIVIDE,
    MAX,
    ASSIGN,
    ENUM_SZ
};

int (*optab[])(Tree *) = {
    pushop,
    pushsop,
    addop,
    divop,
    maxop,
    asnop
};

int eval(Tree *t)
{
    return (*optab[t->op])(t);
}

typedef union Code Code;
union Code {
    void (*op)(void);
    int value;
    Symbol *symbol;
};

#define NCODE (16)
Code code[NCODE];

int generate(int codep, Tree *t)
{
    switch (t->op) {
        case NUMBER:
        case VARIABLE:
        case ADD:
        case DIVIDE:
        case MAX:
        case ASSIGN:
            break;
    }
}

int main()
{
}

