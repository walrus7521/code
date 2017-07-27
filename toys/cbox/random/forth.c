#include <stdio.h>

enum {
    ADD,
    SUB,
    DIV,
    MUL,
    NUM_OPS
};

int add(int a, int b) {
    printf("add: %d, %d\n", a, b);
    return a+b;
}
int sub(int a, int b) {
    printf("sub: %d, %d\n", a, b);
    return a-b;
}
int mul(int a, int b) {
    printf("mul: %d, %d\n", a, b);
    return a*b;
}
int div(int a, int b) {
    printf("div: %d, %d\n", a, b);
    return a/b;
}

typedef int (*op)(int a, int b);
op ops[NUM_OPS] = 
{
    add, sub, mul, div
};

char stack[256];
int stack_ptr = 0;
int values[256];
int value_ptr = 0;

void push_op(char op)
{
    stack[stack_ptr++] = op;
}

char pop_op()
{
    return stack[--stack_ptr];
}

int get_op()
{
    char o = pop_op(); //printf("op: %c\n", o);
    switch (o) {
        case '+': return ADD;
        case '-': return SUB;
        case '*': return MUL;
        case '/': return DIV;
    }
}

void push_val(int val)
{
    values[value_ptr++] = val;
}

int pop_val()
{
    return values[--value_ptr];
}

void eval()
{
    int cop = get_op();
    int v1 = pop_val();
    int v2 = pop_val();
    int v3 = ops[cop](v1, v2); printf("%d\n", v3);
}

int main()
{
    push_val(1);
    push_val(2);
    push_op('+');
    eval();

    push_val(3);
    push_val(4);
    push_op('*');
    eval();

    push_val(5);
    push_val(6);
    push_op('-');
    eval();
    
    push_val(7);
    push_val(8);
    push_op('/');
    eval();
}
