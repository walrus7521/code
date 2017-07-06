#include <stdio.h>
#include <stdlib.h>

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

int lptr = 0;
char line[256];
int token;
int nptr;
char number[32];
void strip()
{
    while (line[lptr] == ' ') {
        lptr++;
    }
}

int is_num(char n)
{
    if (n >= '0' && n <= '9') return 1;
    return 0;
}

int get_num()
{
    memset(number, 0, 32);
    nptr = 0;
    while (is_num(line[lptr++])) {
        *number++ = *line++;
    }
    int num = atol(number);
    return num;
}

int get_token()
{
    //printf("line %d: %s\n", lptr, &line[lptr]);
    strip();
    //printf("line2 %d: %s\n", lptr, &line[lptr]);
    switch (line[lptr]) {
        case '+':
        case '-':
        case '*':
        case '\\':
            return line[lptr++];
        case '\n':
            return 0;
    }
    if (is_num(line[lptr])) {
        int n = get_num();
        return n;
    }
    return 0;
}

int main()
{
    while (gets(line) != NULL) {
        lptr = 0;
        while (token = get_token()) {
            printf("token: %c\n", token);
        }
    }
    return 0;
}

