#include <stdio.h>
#include <string.h>
#include "ast.h"

int (*optab[])(Tree *) = {
    pushop,     // NUMBER
    pushsymop,  // VARIABLE
    addop,      // ADD
    divop,      // DIVIDE
    maxop,      // MAX
    assnop      // ASSIGN
};

int pushop(Tree *t)
{
    //printf("push\n");
    return t->value;
}

int pushsymop(Tree *t)
{
    //printf("sym\n");
    return t->symbol->value;
}

int addop(Tree *t)
{
    //printf("add\n");
    return (eval(t->left) + eval(t->right));
}

int maxop(Tree *t)
{
    //printf("max\n");
    int left, right;
    left = eval(t->left);
    right = eval(t->right);
    return (left > right) ? left : right;
}

int divop(Tree *t)
{
    //printf("div\n");
    int left, right;
    left = eval(t->left);
    right = eval(t->right);
    if (right == 0) {
        printf("error div by zero\n");
        return -1;
    }
    return left / right;
}

int assnop(Tree *t)
{
    //printf("assn\n");
    t->left->value = eval(t->right);
    return t->left->value;
}

int eval(Tree *t)
{
    printf("eval.op[%s]\n", get_text(t));
    int val = (optab[t->op](t));
    return val;
}

Tree tassn;
Tree tvara;
Tree tmax;
Tree tvarb;
Tree tdiv;
Tree tvarc;
Tree tval2;

void init()
{
    tassn.op = ASSIGN;
    tassn.left = &tvara;
    tassn.right = &tmax;
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

void do_ast()
{
    printf("eval = %d\n", eval(&tassn));
}

int main(int argc, char **argv)
{
    init();
    do_ast();
}

