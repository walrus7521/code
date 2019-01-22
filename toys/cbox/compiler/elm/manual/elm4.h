#ifndef _ELM_H
#define _ELM_H

typedef enum TOKEN {
    NUMBER,
    VARIABLE,
    ADD,
    DIVIDE,
    MAX,
    ASSIGN,
    INVALID
} TOKEN;

typedef struct Token {
    TOKEN token;
    struct {
        int   inum;
        float fnum;
        char *id;
    } u;
} Token;

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
