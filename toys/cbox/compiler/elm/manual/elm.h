#ifndef _ELM_H
#define _ELM_H

typedef struct Symbol Symbol;
typedef struct Tree Tree;
typedef struct Code Code;

struct Symbol {
    int value;
    char *name;
};

struct Tree {
    int    op;
    int    value;
    int    visited;
    Symbol *symbol;
    Tree   *left;
    Tree   *right;
};

struct Code {
    int    iop;
    union {
        int    value;       // value if number
        Symbol symbol;     // symbol entry if variable
    } u;
};

enum {
    NUMBER,
    VARIABLE,
    ADD,
    DIVIDE,
    MAX,
    ASSIGN,
    INVALID
        
};

char *get_op(Tree *t)
{
    switch (t->op) {
        case NUMBER:    return "num";
        case VARIABLE:  return "var";
        case ADD:       return "add";
        case DIVIDE:    return "div";
        case MAX:       return "max";
        case ASSIGN:    return "asn";
    }
    return "";
}

int is_op(int iop)
{
    switch (iop) {
        case NUMBER:
        case VARIABLE:
        case ADD:
        case DIVIDE:
        case MAX:
        case ASSIGN:
            return 1;
    }
    return 0;
}

#endif // _ELM_H_
