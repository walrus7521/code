#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node {
   char op;
   int val;
   struct node *left;
   struct node *right;
};

typedef struct node Tree;

int generate(int codep, Tree *t);
int generate_rpn(int codep, Tree *t);

enum {
    NUMBER,
    VARIABLE,
    ADD,
    SUBTRACT,
    DIVIDE,
    MULTIPLY,
    MAX,
    ASSIGN,
    ENUM_SZ
};

typedef struct Symbol Symbol;
struct Symbol {
    int value;
    char *name;
};

typedef union Code Code;
union Code {
    void (*op)(void);
    int value;
    Symbol *symbol;
};


#define NCODE   (32)
#define NSTACK  (32)
Code code[NCODE];
int stack[NSTACK];
int pc = 0;
int codep = 0;
int stackp = 0;


void pushop() { 
    int val = code[codep++].value;
    printf("pushop %d\n", val);
    stack[stackp++] = val;
}

void pushsymop() {
    printf("pushsymop\n");
}

void addop() { 
    int v1 = stack[--stackp];
    int v2 = stack[--stackp];
    int v3 = v1 + v2;
    printf("addop: %d + %d = %d\n", v1, v2, v3);
    stack[stackp++] = v3;
}

void subop() { 
    int v1 = stack[--stackp];
    int v2 = stack[--stackp];
    int v3 = v2 - v1;
    printf("subop: %d - %d = %d\n", v2, v1, v3);
    stack[stackp++] = v3;
}

void multop() { 
    int v1 = stack[--stackp];
    int v2 = stack[--stackp];
    int v3 = v1 * v2;
    printf("multop: %d x %d = %d\n", v1, v2, v3);
    stack[stackp++] = v3;
}

void divop() { 
    int v1 = stack[--stackp];
    int v2 = stack[--stackp];
    int v3 = v2 / v1;
    printf("divop: %d / %d = %d\n", v2, v1, v3);
    if (v1 == 0) {
        printf("divide by zero: %d\n", v1);
    }
    stack[stackp++] = v3;
}

void maxop() { 
    printf("maxop\n");
}

void asnop() {
    printf("asnop\n");
}


char *get_token(char **p) {
    while(**p && isspace(**p)){//skip spaces
        ++*p;
    }
    char *ret = *p;
    if(!*ret){//empty
        return NULL;
    }
    while(**p && !isspace(**p)){
        ++*p;
    }
    if(!**p){
        **p = 0;
        ++*p;
    }
    return ret;
}

Tree *make_tree(char **p) {
    char *token = get_token(p);
    printf("token: %s\n", token);

    if(token){
        Tree *tree = malloc(sizeof(*tree));

        switch(*token){//token[1] == '\0' ??
        case '*':
        case '/':
        case '+':
        case '-':
            tree->op = *token;
            tree->val = 0;
            tree->left = make_tree(p);
            tree->right = make_tree(p);
            break;
        default:
            tree->op = 'N';
            tree->val = atoi(token);
            tree->left = tree->right = NULL;
            break;
        }
        return tree;
    }
    return NULL;
}

#define SIZE_STAK 32
typedef int e_v;
#include "..\phd\stak.inc"
Tree *make_tree_rpn(char **p) {
    char *token = get_token(p);
    int v1, v2;
    printf("token: %s\n", token);

    if (token) {
        Tree *tree = malloc(sizeof(*tree));

        switch (*token) {//token[1] == '\0' ??
        case '*':
        case '/':
        case '+':
        case '-':
            tree->op = *token;
            tree->val = 0;
            v1 = stkpop();
            v2 = stkpop();
            tree->left  = malloc(sizeof(*tree));
            tree->right = malloc(sizeof(*tree));
            tree->left->val = v1;
            tree->right->val = v2;
            printf("op: %d %c %d\n", v1, tree->op, v2);
            break;
        default:
            tree->op = 'N';
            tree->val = atoi(token);
            tree->left = tree->right = NULL;
            printf("pushing: %d\n", tree->val);
            stkpush(tree->val);
            make_tree_rpn(p);
            //tree->left = make_tree_rpn(p);
            //tree->right = make_tree_rpn(p);
            break;
        }
        return tree;
    }
    return NULL;
}


void release(Tree *tree) {
    if (tree) {
        release(tree->left);
        release(tree->right);
        free(tree);
    }
}

void print_infix(Tree *tree) {
    if (tree) {
        switch(tree->op) {
        case '*':
        case '/':
        case '+':
        case '-':
            putchar('(');
            print_infix(tree->left);
            printf(" %c ", tree->op);
            print_infix(tree->right);
            putchar(')');
            break;
        case 'N':
            printf("%d", tree->val);
            break;
        default:
            fprintf(stderr, "\nerror!\n");//this should never be executed
        }
    }
}

void print_postfix(Tree *tree) {
    if(tree) {
        switch(tree->op) {
        case '*':
        case '/':
        case '+':
        case '-':
            putchar('(');
            printf(" %c ", tree->op);
            print_infix(tree->left);
            print_infix(tree->right);
            putchar(')');
            break;
        case 'N':
            printf("%d", tree->val);
            break;
        default:
            fprintf(stderr, "\nerror!\n");//this should never be executed
        }
    }
}

void dump_code()
{
    int i;
    for (i = 0; i < codep; i++) {
        printf("code[%d] = %p\n", i, code[i].op);
    }
}

int eval(Tree *t)
{
    int c = 0;
    codep = generate(0, t);
    printf("codep: %d\n", codep);
    code[codep].op = NULL;
    stackp = 0;
    codep = 0;
    while (code[codep].op != NULL) {
        //printf("codep: %d %p\n", 
        //        codep,
        //        code[codep].op);
        //codep++;
        (*code[codep++].op)();
    }
    return stack[0];
}

int generate(int codep, Tree *t)
{
    printf("generate: %d op %c\n", codep, t->op);
    switch (t->op) {
        case NUMBER:
        case 'N':
            code[codep++].op = pushop;
            code[codep++].value = t->val;
            return codep;
        case VARIABLE:
            code[codep++].op = pushsymop;
            code[codep++].value = t->val;
            return codep;
        case ADD:
        case '+':
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            code[codep++].op = addop;
            return codep;
        case SUBTRACT:
        case '-':
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            code[codep++].op = subop;
            return codep;
        case MULTIPLY:
        case '*':
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            code[codep++].op = multop;
            return codep;
        case DIVIDE:
        case '/':
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            code[codep++].op = divop;
            return codep;
        case MAX:
        case ASSIGN:
            break;
    }
    return codep; //next op
}

int generate_rpn(int codep, Tree *t)
{
    printf("generate: %d op %c\n", codep, t->op);
    switch (t->op) {
        case NUMBER:
        case 'N':
            code[codep++].op = pushop;
            code[codep++].value = t->val;
            return codep;
        case VARIABLE:
            code[codep++].op = pushsymop;
            code[codep++].value = t->val;
            return codep;
        case ADD:
        case '+':
            code[codep++].op = addop;
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            return codep;
        case SUBTRACT:
        case '-':
            code[codep++].op = subop;
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            return codep;
        case MULTIPLY:
        case '*':
            code[codep++].op = multop;
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            return codep;
        case DIVIDE:
        case '/':
            code[codep++].op = divop;
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            return codep;
        case MAX:
        case ASSIGN:
            break;
    }
    return codep; //next op
}


void zero_mem()
{
    int i;
    for (i = 0; i < NCODE; i++) {
        code[i].op = NULL;
        code[i].value = 0;
        code[i].symbol = NULL;
    }
}

void multi_line()
{
    char line[256];

    while(fgets(line, sizeof(line), stdin)){
        printf("line..\n");
        char *s = line;
        Tree *tree = make_tree(&s);
        print_infix(tree);
        putchar('\n');
        release(tree);
    }
}

void one_liners()
{
    char line1[256] = "* + 7 3 - 5 2";
    char line2[256] = "* 3 + 1  2";
    char line3[256] = "/ + 1 + 2 3 5";
    char *s = line1;
    Tree *tree = make_tree(&s);
    print_infix(tree);
    putchar('\n');
    eval(tree);
    release(tree);
}

void do_rpn()
{
    char rline[256] = "1 2 +";
    char *s = rline;
    Tree *tree = make_tree_rpn(&s);
    print_infix(tree);
    //print_postfix(tree);
    //putchar('\n');
    //eval(tree);
    //codep = generate(codep, tree);
    //printf("codep=%d\n", codep);
    //dump_code();
    //release(tree);
}

int main(void){
    //multi_line();
    init_stak();
    do_rpn();
    return 0;
    zero_mem();
    one_liners();
    return 0;
}
#if 0
* + 7 3 - 5 2
((7 + 3) * (5 - 2))
* 3 + 1  2
(3 * (1 + 2))
/ + 1 + 2 3 5
((1 + (2 + 3)) / 5)
^Z
#endif
