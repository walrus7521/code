#include <stdio.h>
#include <string.h>
#include "ast.h"

void pushop2()
{
    printf("pushop2\n");
}

void pushsymop2()
{
    printf("pushsymop2\n");
}

void addop2()
{
    printf("addop2\n");
}

void divop2()
{
    printf("divop2\n");
}

void maxop2()
{
    printf("maxop2\n");
}

void assnop2()
{
    printf("asnop2\n");
}

Code code[256];
int stack[256];
int stackp;
int pc;

void dump_gen()
{
    int i = 0;
    while (code[i].u.op != NULL) {
        int type = code[i].type;
        i++;
        switch (type) {
            case NUMBER:
                printf("num\n"); break;
            case VARIABLE:
                printf("var\n"); break;
            case ADD:
                printf("add\n"); break;
            case DIVIDE:
                printf("div\n"); break;
            case MAX:
                printf("max\n"); break;
            case ASSIGN:
                printf("stor\n"); break;
        }
    }
}

int generate(int codep, Tree *t)
{
    printf("gen: %d => %s\n", codep, get_text(t));
    switch (t->op) {
        case NUMBER:
            code[codep].type = t->op; code[codep++].u.op    = pushop2;
            code[codep].type = t->op; code[codep++].u.value = t->value;
            return codep;
        case VARIABLE:
            code[codep].type = t->op; code[codep++].u.op    = pushsymop2;
            code[codep].type = t->op; code[codep++].u.symbol = t->symbol;
            return codep;
        case ADD:
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            code[codep].type = t->op; code[codep++].u.op    = addop2;
            return codep;
        case DIVIDE:
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            code[codep].type = t->op; code[codep++].u.op    = divop2;
            return codep;
        case MAX:
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            code[codep].type = t->op; code[codep++].u.op    = maxop2;
            return codep;
        case ASSIGN:
            codep = generate(codep, t->right);
            code[codep].type = t->op; code[codep++].u.op    = assnop2;
            return codep;
    }
    return codep;
}

int eval2(Tree *t)
{
#if 1
    pc = generate(0, t);
    code[pc].u.op = NULL;

    stackp = 0;
    pc = 0;
    while (code[pc].u.op != NULL) {
        (code[pc++].u.op)();
    }
    return stack[0];// final value
#endif
    return 0;
}

Tree troot;
Tree tvara;
Tree tmax;
Tree tvarb;
Tree tdiv;
Tree tvarc;
Tree tval2;

void init()
{
    troot.op = ASSIGN;
    troot.left = &tvara;
    troot.right = &tmax;
    tvara.op = VARIABLE;
    tmax.op  = MAX;
    tmax.left = &tvarb;
    tmax.right = &tdiv;
    tvarb.op = NUMBER;
    tvarb.value = 3;
    tdiv.op  = DIVIDE;
    tdiv.left = &tvarc;
    tdiv.right = &tval2;
    tvarc.op = NUMBER;
    tvarc.value = 4;
    tval2.op = NUMBER;
    tval2.value = 2;
}

void walk_and_gen(Tree *t)
{
    if (t == NULL) return;
    generate(pc++, t);
    //printf("op: %s\n", get_text(t));
    if (t->left) walk_and_gen(t->left);
    if (t->right) walk_and_gen(t->right);
}

void do_gen()
{
    // walk the AST and call generate on each node
    pc = 0;
    printf("walk ast\n");
    walk_and_gen(&troot);
    printf("dump code\n");
    dump_gen();
    printf("start evaluation\n");
    printf("eval2 = %d\n", eval2(&troot));
}

int main(int argc, char **argv)
{
    memset(&code, 0, sizeof(code));
    init();
    do_gen();
}

