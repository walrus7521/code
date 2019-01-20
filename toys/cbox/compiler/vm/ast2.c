#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast.h"

// http://lambda-the-ultimate.org/node/2884
// https://webkit.org/blog/189/announcing-squirrelfish/

Code code[256];
int pc;
int stack[256];
int stackp;

Tree troot;
Tree tvara;
Tree tmax;
Tree tvarb;
Tree tdiv;
Tree tvarc;
Tree tval2;
Symbol symA;

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
    sym = code[pc++].u.symbol;
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

void dump_gen()
{
    pc = 0;
    while (code[pc].u.op != NULL) {
        if (code[pc].type == VARIABLE) {
            Symbol *sym = code[pc].u.symbol;
            printf("sym [%d] => %s = %d\n", pc, sym->name, sym->value);
        } else
        if (code[pc].type == NUMBER) {
            printf("num [%d] => %d\n", pc, code[pc].u.value);
        } else
        if (code[pc].type == OPERAND) {
            printf("op  [%d] => %p\n", pc, code[pc].u.op);
        }
        pc++;
    }
}

int generate(int codep, Tree *t)
{
    //printf("gen: %d => %s\n", codep, get_text(t));
    switch (t->op) {
        case NUMBER:
            code[codep].type = OPERAND; code[codep++].u.op    = pushop2;
            code[codep].type = NUMBER; code[codep++].u.value = t->value;
            return codep;
        case VARIABLE:
            code[codep].type = OPERAND; code[codep++].u.op    = pushsymop2;
            printf("var[%d]: %p: %s = %d\n", codep, t->symbol, t->symbol->name, t->symbol->value);
            code[codep].type = VARIABLE; code[codep++].u.symbol = t->symbol;
            return codep;
        case ADD:
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            code[codep].type = OPERAND; code[codep++].u.op    = addop2;
            return codep;
        case DIVIDE:
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            code[codep].type = OPERAND; code[codep++].u.op    = divop2;
            return codep;
        case MAX:
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            code[codep].type = OPERAND; code[codep++].u.op    = maxop2;
            return codep;
        case ASSIGN:
            codep = generate(codep, t->right);
            code[codep].type = OPERAND; code[codep++].u.op = storesymop2;
            return codep;
    }
    return codep;
}

int eval2(Tree *t)
{
//    pc = generate(0, t);
//    code[pc].u.op = NULL;

    stackp = 0;
    pc = 0;
    while (code[pc].u.op != NULL) {
        printf("exec[%d] : ", pc);
        (code[pc++].u.op)();
    }
    return stack[0];// final value
}


void init()
{
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
    
    tvarb.op = NUMBER;
    tvarb.value = 43;
    
    tdiv.op  = DIVIDE;
    tdiv.left = &tvarc;
    tdiv.right = &tval2;
    
    tvarc.op = NUMBER;
    tvarc.value = 8;
    
    tval2.op = NUMBER;
    tval2.value = 2;
}

void walk_and_gen(Tree *t)
{
    if (t == NULL) return;
    printf("walk[%d]: %s\n", pc, get_text(t));
    pc = generate(pc++, t); // visitor
    if (t->left) walk_and_gen(t->left);
    if (t->right) walk_and_gen(t->right);
}

void do_gen()
{
    // walk the AST and call generate on each node
    pc = 0;
    walk_and_gen(&troot);
    printf("last pc: %d\n", pc);
    code[pc].u.op = NULL;

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

