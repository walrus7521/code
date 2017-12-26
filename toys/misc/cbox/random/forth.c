#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

/*
    Add internal functions: sin, cos, tan
    Add load <file> function

 */

// code.f

typedef enum {
    TYPE_OP,        // binary operator
    TYPE_NAME,      // $ prefixed variable
    TYPE_INT,       // integer
    TYPE_FLOAT,     // float
    TYPE_STRING,    // string
    TYPE_EVAL,      // dot command to evaluate
    TYPE_FUNC,      // fun prefixed name
    TYPE_TERMINATE, // 'quit' command
    TYPE_NUM_TYPES  
} op_type_t;

typedef enum {
    OP_ADD,            // '+'
    OP_SUB,            // '-'
    OP_MUL,            // '*'
    OP_DIV,            // '/'
    OP_EQU,            // '='
    OP_MOD,            // '%'
    OP_UDF,            // user defined
    OP_NUM_OPS
} op_verb_t;

typedef struct {
    uint32_t key; // hash value
    int type; // char, int, string, double
    char name[256]; // variable name
    char value[256]; // current value
} symbol;

#define dprint(...) //printf
#define TABLE_SIZE (256)
symbol symtab[TABLE_SIZE];

void push_raw(char *op);
char *pop_raw();
int get_op();

void reverse(char *s)
{
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i]; // swap
        s[i] = s[j];
        s[j] = c;
    }
}

void Itoa(int n, char *s)
{
    int i, sign;
    if ((sign = n) < 0) {
        n = -n;
    }
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}

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

// hack Adder
int Add() {
    char *sa = pop_raw();
    char *sb = pop_raw();
    //printf("add: %s %s\n", sa, sb);
    // for now assume they are ints
    int a = atoi(sa);
    int b = atoi(sb);
    int c = a + b;
    char sc[32];
    Itoa(c, sc);
    push_raw(sc);
    printf("add: %d+%d=%d\n", a, b, c);
    return c;
}
int Sub() {
    char *sa = pop_raw();
    char *sb = pop_raw();
    // for now assume they are ints
    int a = atoi(sa);
    int b = atoi(sb);
    int c = a - b;
    char sc[32];
    Itoa(c, sc);
    push_raw(sc);
    printf("sub: %d-%d=%d\n", a, b, c);
    return c;
}
int Mul() {
    char *sa = pop_raw();
    char *sb = pop_raw();
    // for now assume they are ints
    int a = atoi(sa);
    int b = atoi(sb);
    int c = a * b;
    char sc[32];
    Itoa(c, sc);
    push_raw(sc);
    printf("mul: %dx%d=%d\n", a, b, c);
    return c;
}
int Div() {
    char *sa = pop_raw();
    char *sb = pop_raw();
    // for now assume they are ints
    int a = atoi(sa);
    int b = atoi(sb);
    int c = a / b;
    char sc[32];
    Itoa(c, sc);
    push_raw(sc);
    printf("div: %d/%d=%d\n", a, b, c);
    return c;
}
int Equ() {
    char *sa = pop_raw();
    char *sb = pop_raw();
    // for now assume they are ints
    int a = atoi(sa);
    int b = atoi(sb);
    int c = a == b;
    char sc[32];
    Itoa(c, sc);
    push_raw(sc);
    printf("eq: %d==%d?%d\n", a, b, c);
    return c;
}
int Mod() {
    char *sa = pop_raw();
    char *sb = pop_raw();
    // for now assume they are ints
    int a = atoi(sa);
    int b = atoi(sb);
    int c = a % b;
    char sc[32];
    Itoa(c, sc);
    push_raw(sc);
    printf("eq: %d%%%d=%d\n", a, b, c);
    return c;
}
int Udf() {
    int a = 42;
    printf("udf: %d\n", a);
    return a;
}

//typedef int (*op)(int a, int b);
typedef int (*op)();
op ops[OP_NUM_OPS] = 
{
    Add, Sub, Mul, Div, Equ, Mod, Udf
};

typedef struct {
    char n[256];
} raw;

char stack[TABLE_SIZE];
int stack_ptr = 0;
int values[TABLE_SIZE];
int value_ptr = 0;
raw raw_stack[TABLE_SIZE];
int raw_ptr = 0;

void push_raw(char *op)
{
    dprint("push raw: %d\n", raw_ptr);
    strcpy(raw_stack[raw_ptr++].n, op);
}

char *pop_raw()
{
    dprint("pop raw: %d\n", raw_ptr);
    return raw_stack[--raw_ptr].n;
}

void push_op(char op)
{
    stack[stack_ptr++] = op;
}

char pop_op()
{
    //printf("pop_op ptr: %d\n", stack_ptr);
    return stack[--stack_ptr];
}

char peek_op()
{
    return stack[stack_ptr-1];
}

void push_val(int val)
{
    values[value_ptr++] = val;
}

int pop_val()
{
    return values[--value_ptr];
}

void dump()
{
    int i;
    printf("ops: %d\n", stack_ptr);
    for (i = stack_ptr-1; i >=0; i--) {
        printf("%c\n", stack[i]);
    }
    //printf("vals: %d\n", value_ptr);
    //for (i = value_ptr; i >=0; i--) {
    //    printf("%d\n", values[i]);
    //}
    printf("raw: %d\n", raw_ptr);
    for (i = raw_ptr-1; i >=0; i--) {
        printf("%s\n", raw_stack[i].n);
    }
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

bool is_hex(char *s, int len)
{
    int i;
    for (i = 0; i < len; i++) {
        if (!isxdigit(s[i])) {
            return false;
        }
    }
    return true;
//    int num;
//    num = strtol (s,NULL,16);
//    printf ("hex: %lx is %ld.\n", num, num);
//    return true;
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

op_type_t parse_token(char *s, int len)
{
    //printf("token: %s len %d\n", s, len);
    if (len == 1) {
        switch (*s) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '=':
            case '%':
                return TYPE_OP;
            case '.':
                return TYPE_EVAL;
        }
    }
    if (is_num(s, len)) {
        return TYPE_INT;
    }
    if (is_float(s, len)) {
        return TYPE_FLOAT;
    }
    if (strstr(s, "0x")) {
        if (is_hex(&s[2], len-2)) {
            return TYPE_INT;
        }
    }
    if (strstr(s, "$")) {
        return TYPE_NAME;
    }
    if (strstr(s, "fun")) { // user-defined function
        return TYPE_FUNC;
    }
    // need to do lookup of internal functions
    if (strstr(s, "quit")) {
        return TYPE_TERMINATE;
    }
    return TYPE_STRING;
}

int get_op()
{
    char o = pop_op(); dprint("op: %c\n", o);
    switch (o) {
        case '+': dprint("+\n"); return OP_ADD;
        case '-': dprint("-\n"); return OP_SUB;
        case '*': dprint("*\n"); return OP_MUL;
        case '/': dprint("/\n"); return OP_DIV;
        case '=': dprint("=\n"); return OP_EQU;
        case '%': dprint("=\n"); return OP_MOD;
        default: return -1;
    }
}

int get_func(char *func)
{
    return OP_UDF;
}

void repl()
{
    char *buffer = malloc(256);
    char *line = buffer;
    int cop;
    int fop; // needs to be a function pointer
    int num;
    float fnum;
    printf("> ");
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
                    cop = get_op();
                    ops[cop]();
                    break;
                case TYPE_INT:
                    num = atoi(token);
                    dprint("got an integer: %s => %d\n", token, num);
                    push_raw(token);
                    break;
                case TYPE_FLOAT:
                    fnum = atof(token);
                    dprint("got a float: %s => %f\n", token, fnum);
                    push_raw(token);
                    break;
                case TYPE_FUNC:
                    dprint("got a function: %s\n", token);
                    fop = get_func(token);
                    ops[fop]();
                    break;
                case TYPE_STRING:
                    dprint("got a string: %s\n", token);
                    break;
                case TYPE_EVAL:
                    dprint("got an eval command: %s\n", token);
                    // just do a dump the stack
                    dump();
                    //eval();
                    break;
                case TYPE_TERMINATE:
                    dprint("terminating repl\n");
                    return;
            }
            token = strtok(NULL, " ");
        }
        printf("> ");
    }
    free(buffer);
}

int main()
{
    repl();
}


