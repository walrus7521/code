#ifndef _ELM_H
#define _ELM_H

typedef enum TOKEN {
    NUMBER, // number as extra info
    ID,     // symbol as extra info
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

typedef struct Tree {
    int     op;
    int     value;
    int     visited;
    char    *name;
    struct  Tree *left;
    struct  Tree *right;
} Tree;

typedef struct Code {
    int    iop;
    struct {
        int  value; // value if number
        char *name; // symbol entry if ID
    } u;
} Code;


char *get_op(Tree *t)
{
    switch (t->op) {
        case NUMBER:    return "num";
        case ID:        return "id";
        case ADD:       return "add";
        case DIVIDE:    return "div";
        case MAX:       return "max";
        case ASSIGN:    return "asn";
    }
    return "";
}

void pushop2();
void pushsymop2();
void addop2();
void divop2();
void maxop2();
void storesymop2();

void (*optab[])() = {
    pushop2,     // NUMBER
    pushsymop2,  // ID
    addop2,      // ADD
    divop2,      // DIVIDE
    maxop2,      // MAX
    storesymop2  // ASSIGN
};


#endif // _ELM_H_
