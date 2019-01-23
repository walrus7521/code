#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elm4.h"

// @todo: add print ID
//        create a token stream
//
// http://lambda-the-ultimate.org/node/2884
// https://webkit.org/blog/189/announcing-squirrelfish/

Code code[256];
int pc;
int stack[256];
int stackp;
Tree troot = {0}; Tree tvara = {0}; Tree tmax = {0}; Tree tvalb = {0};
Tree tdiv = {0}; Tree tvalc = {0}; Tree tval2 = {0}; 

void pushop2()
{
    int val = code[pc].u.value;
    printf("pushop2: %d\n", val);
    stack[stackp++] = code[pc++].u.value;
}

void pushsymop2()
{
    int _pc = pc++;
    printf("pushsymop2[%d]: %s = %d\n", _pc, code[_pc].u.name, code[_pc].u.value);
}

void addop2()
{
    int val, left, right;
    right = stack[--stackp];
    left  = stack[--stackp];
    val = right + left;
    printf("addop2(%d + %d) = %d\n", left, right, val);
    stack[stackp++] = left + right;
    pc++;
}

void divop2()
{
    int val, left, right;
    right = stack[--stackp];
    left  = stack[--stackp];
    if (right == 0) {
        printf("divide by zero\n");
        return;
    }
    val = left / right;
    printf("divop2: %d/%d = %d\n", left, right, val);
    stack[stackp++] = val;
    pc++;
}

void maxop2()
{
    int val, left, right;
    right = stack[--stackp];
    left  = stack[--stackp];
    val = left > right ? left : right;
    printf("maxop2(%d, %d) = %d\n", left, right, val);
    stack[stackp++] = left > right ? left : right;
    pc++;
}

void storesymop2()
{
    int val  = stack[--stackp];
    printf("storesymop2: %d\n", val);
    stack[stackp++] = val;
    pc++;
}

void dump_gen(int raw)
{
    pc = 0;
    int iop = code[pc].iop;
    while (iop != -1) {
        if (raw) {
            printf("%x %x\n", code[pc].iop, code[pc].u.value);
        } else {
            switch (iop) {
            case NUMBER:
                printf("[%02d] number => %d\n", pc, code[pc].u.value); break;
            case ID:
                printf("[%02d] pushsymop => %s = %d\n", pc, code[pc].u.name, code[pc].u.value); break;
            case ADD:
                printf("[%02d] addop\n", pc); break;
            case DIVIDE:
                printf("[%02d] divop\n", pc); break;
            case MAX:
                printf("[%02d] maxop\n", pc); break;
            case ASSIGN:
                printf("[%02d] storesymop\n", pc); break;
            default:
                printf("[%02d] unknown iop: %d\n", pc, iop); break;
            }
        }
        iop = code[++pc].iop;
    }
}

int generate(int codep, Tree *t)
{
    if (t == NULL || t->visited == 1) return codep;
    printf("gen[%d]:", codep);
    t->visited = 1;
    switch (t->op) {
        case NUMBER:
            printf("num[%d]\n", codep);
            code[codep].iop = NUMBER; code[codep++].u.value = t->value;
            return codep;
        case ID:
            printf("id[%d]\n", codep);
            code[codep].iop = ID; code[codep].u.name = t->name; code[codep++].u.value = t->value;
            return codep;
        case ADD:
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            printf("add[%d]\n", codep);
            code[codep++].iop = ADD;
            return codep;
        case DIVIDE:
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            printf("div[%d]\n", codep);
            code[codep++].iop = DIVIDE;
            return codep;
        case MAX:
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            printf("max[%d]\n", codep);
            code[codep++].iop = MAX;
            return codep;
        case ASSIGN:
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            printf("asn[%d]\n", codep);
            code[codep++].iop = ASSIGN;
            return codep;
    }
    return codep;
}

int eval2(Tree *t)
{
    stackp = 0;
    pc = 0; // let the operations modify the pc
    while (code[pc].iop != -1) {
        int iop = code[pc].iop;
        printf("exec[%02d] : %d  ", pc, iop);
        optab[iop]();
    }
    return stack[0];// final value
}


void init()
{
    troot.op    = ASSIGN;
    troot.left  = &tvara;
    troot.right = &tmax;

    tvara.op    = ID;
    tvara.name  = strdup("dude");
    tvara.value = 42; // bogus

    tmax.op     = MAX;
    tmax.left   = &tvalb;
    tmax.right  = &tdiv;
    
    tdiv.op     = DIVIDE;
    tdiv.left   = &tvalc;
    tdiv.right  = &tval2;
    
    tvalb.op    = NUMBER;
    tvalb.value = 43;

    tvalc.op    = NUMBER;
    tvalc.value = 8;
    
    tval2.op    = NUMBER;
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

