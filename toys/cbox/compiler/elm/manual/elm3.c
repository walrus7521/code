#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elm.h"

// http://lambda-the-ultimate.org/node/2884
// https://webkit.org/blog/189/announcing-squirrelfish/

Code code[256];
int pc;
int stack[256];
int stackp;

Tree troot = {0};
Tree tvara = {0};
Tree tmax = {0};
Tree tvarb = {0};
Tree tdiv = {0};
Tree tvarc = {0};
Tree tval2 = {0};
Symbol symA = {0};

void pushop2()
{
    //printf("pushop\n"); return;
    int val = code[pc].u.value;
    printf("pushop2: %d\n", val);
    stack[stackp++] = code[pc++].u.value;
}

void pushsymop2()
{
    Symbol *sym;
    int pcounter = pc;
    sym = &code[pc++].u.symbol;
    printf("pushsymop2[%d]: %p : %s = %d\n", pcounter, sym, sym->name, sym->value);
}

void addop2()
{
    int val;
    int left, right;
    //printf("addop\n"); return;
    right = stack[--stackp];
    left  = stack[--stackp];
    val = right + left;
    printf("addop2(%d + %d) = %d\n", left, right, val);
    stack[stackp++] = left + right;
}

void divop2()
{
    int val;
    int left, right;
    //printf("divop\n"); return;
    right = stack[--stackp];
    left  = stack[--stackp];
    if (right == 0) {
        printf("divide by zero\n");
        return;
    }
    val = left / right;
    printf("divop2: %d/%d = %d\n", left, right, val);
    stack[stackp++] = val;
}

void maxop2()
{
    int val;
    int left, right;
    //printf("maxop\n"); return;
    right = stack[--stackp];
    left  = stack[--stackp];
    val = left > right ? left : right;
    printf("maxop2(%d, %d) = %d\n", left, right, val);
    stack[stackp++] = left > right ? left : right;
}

void storesymop2()
{
    int val  = stack[--stackp];
    //printf("storesymop\n"); return;
    printf("storesymop2: %d\n", val);
    stack[stackp++] = val;
}

void dump_gen(int raw)
{
    pc = 0;
    int iop = code[pc].iop;
    while (iop != -1) {
        if (raw) {
            printf("%x %x\n", code[pc].iop, code[pc].u.value);
        } else {
        //printf("[%02d] => [%02d]\n", pc, iop);
            switch (iop) {
            case VARIABLE:
                {
                Symbol *sym = &code[pc].u.symbol;
                printf("[%02d] sym => %s = %d\n", pc, sym->name, sym->value);
                }
                break;
            case NUMBER:
                printf("[%02d] num => %d\n", pc, code[pc].u.value);
                break;
            default:
                if (is_op(iop)) {
                    printf("[%02d] op  => %d\n", pc, code[pc].iop);
                }
                break;
            }
        }
        iop = code[++pc].iop;
    }
}


void (*optab[])() = {
    pushop2,     // NUMBER
    pushsymop2,  // VARIABLE
    addop2,      // ADD
    divop2,      // DIVIDE
    maxop2,      // MAX
    storesymop2  // ASSIGN
};

int generate(int codep, Tree *t)
{
    if (t == NULL || t->visited == 1) return codep;
    printf("gen[%d]:", codep);
    t->visited = 1;
    switch (t->op) {
        case NUMBER:
            printf("num ");
            code[codep++].iop = PUSHOP;
            code[codep].iop = NUMBER; code[codep++].u.value = t->value;
            return codep;
        case VARIABLE:
            printf("var ");
            code[codep++].iop = PUSHSYMOP;
            code[codep].iop = VARIABLE; code[codep++].u.symbol = *t->symbol;
            return codep;
        case ADD:
            printf("add ");
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            code[codep++].iop = ADDOP;
            return codep;
        case DIVIDE:
            printf("div ");
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            code[codep++].iop = DIVOP;
            return codep;
        case MAX:
            printf("max ");
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            code[codep++].iop = MAXOP;
            return codep;
        case ASSIGN:
            printf("asn ");
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            code[codep++].iop = STORESYMOP;
            return codep;
    }
    return codep;
}

int eval2(Tree *t)
{
//  pc = generate(0, t);

    stackp = 0;
    pc = 0;
    while (code[pc].iop != -1) {
        int iop = code[pc++].iop;
        printf("exec[%02d] : ", pc);
        optab[iop]();
    }
    return stack[0];// final value
}


void init()
{
    troot.left = troot.right = NULL;
    tvara.left = tvara.right = NULL;
    tmax.left = tmax.right = NULL;
    tvarb.left = tvarb.right = NULL;
    tdiv.left = tdiv.right = NULL;
    tvarc.left = tvarc.right = NULL;
    tval2.left = tval2.right = NULL;
    troot.visited = 0;
    tvara.visited = 0;
    tmax.visited  = 0;
    tvarb.visited = 0;
    tdiv.visited  = 0;
    tvarc.visited = 0;
    tval2.visited = 0;

    troot.op = ASSIGN;
    troot.left = &tvara;
    troot.right = &tmax;

    tvara.op = VARIABLE;
    tvara.symbol = &symA;
    tvara.symbol->name = strdup("dude");
    tvara.symbol->value = 42;

    tmax.op  = MAX;
    tmax.left = &tvarb;
    tmax.right = &tdiv;
    
    tdiv.op  = DIVIDE;
    tdiv.left = &tvarc;
    tdiv.right = &tval2;
    
    tvarb.op = NUMBER;
    tvarb.value = 43;

    tvarc.op = NUMBER;
    tvarc.value = 8;
    
    tval2.op = NUMBER;
    tval2.value = 2;
}

void walk_and_gen(Tree *t, int lvl)
{
    if (t == NULL) return;
    printf("\nwalk[%02d]:lvl(%02d)\n", pc, lvl);
    pc = generate(pc, t); // visitor
    if (t->left != NULL) walk_and_gen(t->left, lvl+1);
    if (t->right != NULL) walk_and_gen(t->right, lvl+1);
}

void do_gen()
{
    // walk the AST and call generate on each node
    pc = 0;
    walk_and_gen(&troot, 0);
    printf("last pc: %d\n", pc);
    code[pc].iop = -1;

    printf("dump code\n");
    dump_gen(0);

    printf("start evaluation\n");
    printf("eval2 = %d\n", eval2(&troot));
}

int main(int argc, char **argv)
{
    memset(&code, 0, sizeof(code));
    init();
    do_gen();
}

