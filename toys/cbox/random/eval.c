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

void pushop()    { }
void pushsymop() { }
void addop()     { }
void divop()     { }
void maxop()     { }
void asnop()     { }

enum {
    NUMBER,
    VARIABLE,
    ADD,
    DIVIDE,
    MAX,
    ASSIGN,
    ENUM_SZ
};

#if 0
int (*optab[])(Tree *) = {
    pushop,
    pushsymop,
    addop,
    divop,
    maxop,
    asnop
};
#endif

typedef union Code Code;
union Code {
    void (*op)(void);
    int value;
    Symbol *symbol;
};

#define NCODE   (16)
#define NSTACK  (8)
Code code[NCODE];
int stack[NSTACK];
int pc = 0;
int codep = 0;
int stackp = 0;

int generate(int codep, Tree *t)
{
    switch (t->op) {
        case NUMBER:
            code[codep++].op = pushop;
            code[codep++].value = t->value;
            return codep;
        case VARIABLE:
            code[codep++].op = pushsymop;
            code[codep++].value = t->value;
            return codep;
        case ADD:
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            code[codep++].op = addop;
            return codep;
        case DIVIDE:
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            code[codep++].op = divop;
            return codep;
        case MAX:
        case ASSIGN:
            break;
    }
    return 0; //next op
}

int eval(Tree *t)
{
    pc = generate(0, t);
    code[pc].op = NULL;
    stackp = 0;
    pc = 0;
    while (code[pc].op != NULL) {
        (*code[pc++].op)();
    }
    return stack[0];
}

void run()
{
}

void gen()
{
}

int main()
{
    return 0;
}

