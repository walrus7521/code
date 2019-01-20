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
    Symbol *symbol;
    Tree   *left;
    Tree   *right;
};

struct Code {
    int    type;
    union {
        void   (*op)(void); // function if operator
        int    value;       // value if number
        Symbol *symbol;     // symbol entry if variable
    } u;
};

enum {
    NUMBER,
    VARIABLE,
    ADD,
    DIVIDE,
    MAX,
    ASSIGN,
    OPERAND,
    INVALID = -1
};

char *get_text(Tree *t)
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

int pushop(Tree *t);
int pushsymop(Tree *t);
int addop(Tree *t);
int divop(Tree *t);
int maxop(Tree *t);
int assnop(Tree *t);
int eval(Tree *t);

#endif // _ELM_H_
