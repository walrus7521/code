#ifndef _ELM_H
#define _ELM_H

typedef struct Symbol {
    int value;
    char *name;
} Symbol;

typedef struct Tree {
    int    op;
    int    value;
    int    visited;
    Symbol *symbol;
    struct Tree   *left;
    struct Tree   *right;
} Tree;

typedef struct Code {
    int    iop;
    union {
        int    value;       // value if number
        Symbol symbol;     // symbol entry if variable
    } u;
} Code;

typedef enum Token {
    NUMBER,
    VARIABLE,
    ADD,
    DIVIDE,
    MAX,
    ASSIGN,
    INVALID
} Token;

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

#endif // _ELM_H_
