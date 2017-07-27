#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

// code.f

typedef struct {
    uint32_t key;
    char value[256];
} symbol;

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
    printf("hash -> %u\n", hash % TABLE_SIZE);
    return hash % TABLE_SIZE;
}

uint32_t fetch(char *s)
{
    uint32_t hash = hash_string(s);
    printf("sym: %s\n", symtab[hash].value);
    if (strcmp(s, symtab[hash].value) == 0) {
        printf("found: %s\n", s);
        return hash;
    } else {
        printf("not found: %s\n", s);
        return TABLE_SIZE;
    }
}

int insert(char *s)
{
    uint32_t hash = hash_string(s);
    printf("hash of %s is %d\n", s, hash);
    if (strcmp(s, symtab[hash].value) != 0) {
        strcpy(symtab[hash].value, s);
        printf("created new value %s\n", s);
    } else {
        printf("value %s already exists\n", s);
    }
}

enum {
    ADD,
    SUB,
    DIV,
    MUL,
    NUM_OPS
};

int Add(int a, int b) {
    printf("add: %d, %d\n", a, b);
    return a+b;
}
int Sub(int a, int b) {
    printf("sub: %d, %d\n", a, b);
    return a-b;
}
int Mul(int a, int b) {
    printf("mul: %d, %d\n", a, b);
    return a*b;
}
int Div(int a, int b) {
    printf("div: %d, %d\n", a, b);
    return a/b;
}

typedef int (*op)(int a, int b);
op ops[NUM_OPS] = 
{
    Add, Sub, Mul, Div
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

int parse(char *s)
{
    int token = 0; // type of token, VAR, OP, NAME
    return token;
}

void test_parse()
{
    char *buffer = malloc(256);
    char *line = buffer;
    while (fgets(buffer, 256, stdin) != NULL) {
        int len = strlen(buffer);
        line[len-1] = '\0';
        printf("$ %s\n", line);
        // now parse tokens
        char *token = strtok(line, " ");
        while (token != NULL) {
            int type = parse(token);
            printf("%s => type %d\n", token, type);
            token = strtok(NULL, " ");
        }
    }
}

int main()
{
    test_parse();
}
