#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// http://aquamentus.com/flex_bison.html

// code.f
#define TYPE_OP         (1)
#define TYPE_STRING     (2)
#define TYPE_STRING_VAL (3)
#define TYPE_INT        (4)
#define TYPE_INT_NUM    (5)
#define TYPE_FLOAT      (6)
#define TYPE_FLOAT_NUM  (7)
#define TYPE_EVAL       (8)
#define TYPE_FUNC       (9)
#define TYPE_TERMINATE  (10)

typedef struct {
    uint32_t key;
    int type; // char, int, string, double
    char name[256]; // variable name
    char value[256]; // current value
} symbol;

#define dprint(...) //printf
#define TABLE_SIZE (256)
symbol symtab[TABLE_SIZE];

char* get_line(FILE* f, int maxchar)
{
    char* string = (char*)malloc(sizeof(f));
    int c;
    int i;
    while ((c = fgetc(f)) != EOF && c != '\n') {
        fgets(string,maxchar,f);
    }
    return string;          
}

uint32_t hash_string(const char * s)
{
    uint32_t hash = 0;
    for(; *s; ++s)
    {
        hash += *s;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    dprint("hash -> %u\n", hash % TABLE_SIZE);
    return hash % TABLE_SIZE;
}

uint32_t fetch(char *s)
{
    uint32_t hash = hash_string(s);
    dprint("sym: %s\n", symtab[hash].value);
    if (strcmp(s, symtab[hash].value) == 0) {
        dprint("found: %s\n", s);
        return hash;
    } else {
        dprint("not found: %s\n", s);
        return TABLE_SIZE;
    }
}

void insert(char *s)
{
    uint32_t hash = hash_string(s);
    dprint("hash of %s is %d\n", s, hash);
    if (strcmp(s, symtab[hash].value) != 0) {
        strcpy(symtab[hash].value, s);
        dprint("created new value %s\n", s);
    } else {
        dprint("value %s already exists\n", s);
    }
}

enum {
    ADD,
    SUB,
    MUL,
    DIV,
    EQU,
    NUM_OPS
};

int Add(int a, int b) {
    int c = a + b;
    dprint("add: %d+%d=%d\n", a, b, c);
    return c;
}
int Sub(int a, int b) {
    int c = a - b;
    dprint("sub: %d-%d=%d\n", a, b, c);
    return c;
}
int Mul(int a, int b) {
    int c = a * b;
    dprint("mul: %dx%d=%d\n", a, b, c);
    return c;
}
int Div(int a, int b) {
    int c = a / b;
    dprint("div: %d\\%d=%d\n", a, b, c);
    return c;
}
int Equ(int a, int b) {
    int c = (a == b);
    dprint("eq: %d==%d?%d\n", a, b, c);
    return c;
}

typedef int (*op)(int a, int b);
op ops[NUM_OPS] = 
{
    Add, Sub, Mul, Div, Equ
};

char stack[TABLE_SIZE];
int stack_ptr = 0;
int values[TABLE_SIZE];
int value_ptr = 0;

void push_op(char op)
{
    stack[stack_ptr++] = op;
}

char pop_op()
{
    return stack[--stack_ptr];
}

char peek_op()
{
    return stack[stack_ptr-1];
}

int get_op()
{
    char o = pop_op(); dprint("op: %c\n", o);
    switch (o) {
        case '+': dprint("+\n"); return ADD;
        case '-': dprint("-\n"); return SUB;
        case '*': dprint("*\n"); return MUL;
        case '/': dprint("/\n"); return DIV;
        case '=': dprint("=\n"); return EQU;
        default: return -1;
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
    dprint("eval op: %d\n", cop);
    int v1 = pop_val();
    int v2 = pop_val();
    int v3 = ops[cop](v1, v2); printf("%d\n", v3);
    push_val(v3);    
}

void test_stack()
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

void test_hash()
{
    insert("bart");
    insert("cindy");
    insert("mac");
    insert("claire");
    insert("grant");
    insert("chad");
    uint32_t h = fetch("bart");
    if (h < TABLE_SIZE) {
        printf("value exists\n");
    }
}

bool is_num(char *s, int len)
{
    int i;
    for (i = 0; i < len; i++) {
        if (!isdigit(s[i])) {
            return 0;
        }
    }
    return 1;
}

bool is_float(char *s, int len)
{
    int i;
    int one_dot = 0;
    for (i = 0; i < len; i++) {
        if (!isdigit(s[i])) {
            if (!one_dot && s[i] == '.') {
                one_dot = 1;
                continue;
            }
            return 0;
        }
    }
    return 1;
}

int parse_token(char *s, int len)
{
    //printf("token: %s len %d\n", s, len);
    if (len == 1) {
        switch (*s) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '=':
                return TYPE_OP;
            case '.':
                return TYPE_EVAL;
        }
    }
    if (is_num(s, len)) {
        return TYPE_INT_NUM;
    }
    if (is_float(s, len)) {
        return TYPE_FLOAT_NUM;
    }
    if (strstr(s, "fvar")) {
        return TYPE_FLOAT;
    }
    if (strstr(s, "ivar")) {
        return TYPE_INT;
    }
    if (strstr(s, "$")) {
        return TYPE_STRING;
    }
    if (strstr(s, "fun")) {
        return TYPE_FUNC;
    }
    if (strstr(s, "exit")) {
        return TYPE_TERMINATE;
    }
    return TYPE_STRING_VAL;
}

void repl()
{
    char *buffer = malloc(256);
    char *line = buffer;
    int num;
    float fnum;
    printf("$ ");
    while (fgets(buffer, 256, stdin) != NULL) {
        int len = strlen(buffer);
        line[len-1] = '\0';
        printf("%s\n", line);
        // now parse tokens
        char *token = strtok(line, " ");
        while (token != NULL) {
            len = strlen(token);
            int type = parse_token(token, len);
            dprint("%s => type %d\n", token, type);
            switch (type) {
                case TYPE_OP:
                    dprint("got an op code: %c\n", *token);
                    push_op(*token);
                    break;
                case TYPE_INT_NUM:
                    num = atoi(token);
                    dprint("got an integer: %s => %d\n", token, num);
                    push_val(num);
                    break;
                case TYPE_FLOAT_NUM:
                    fnum = atof(token);
                    dprint("got a float: %s => %f\n", token, fnum);
                    break;
                case TYPE_FUNC:
                    dprint("got a function: %s\n", token);
                    break;
                case TYPE_STRING:
                    dprint("got a string type: %s\n", token);
                    break;
                case TYPE_STRING_VAL:
                    dprint("got a string: %s\n", token);
                    break;
                case TYPE_INT:
                    dprint("got an int type: %s\n", token);
                    break;
                case TYPE_FLOAT:
                    dprint("got a float type: %s\n", token);
                    break;
                case TYPE_EVAL:
                    dprint("got an eval command: %s\n", token);
                    eval();
                    break;
                case TYPE_TERMINATE:
                    dprint("terminating repl\n");
                    return;
            }
            token = strtok(NULL, " ");
        }
        printf("$ ");
    }
}

int main()
{
    //parse();
    repl();
}


