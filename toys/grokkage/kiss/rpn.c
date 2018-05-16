#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>

/*
    Next: internal functions

 */

#ifdef _WIN32
#include <string.h>

/* Fake getline function */
size_t getline(char** line, size_t *len, FILE *h) {
    char *pline = *line;
    fgets(pline, *len-1, h);
    return *len;
}

/* Fake add_history function */
void add_history(char* unused) {
}

/* Otherwise include the editline headers */
#else
#include <editline/readline.h>
//#include <editline/history.h>
#endif

typedef enum { OPERAND, UNARYOP, BINARYOP, SYMOP, NOP, ENDEXPR } KindType; // ENDEXPR is '\n'

typedef struct {
    union {
        int i;
        float f;
        char c;
    };
    char sym[8];
} value_t;

typedef struct {
    int head;
    value_t s[256];
} sstack_t;

typedef struct {
    KindType t;
    value_t v;
} token_t;

typedef struct {
    int pos;
    int len;
    char e[256];
} expression_t;

typedef struct {
    int n_expr;
    expression_t p[256];
} program_t;

void ShowPgm(program_t *pgm);
void ShowExp(expression_t *expr);
KindType Kind(token_t *token);
value_t GetValue(token_t *token);
void GetNextToken(token_t *token, expression_t *expr);
value_t DoUnary(token_t *token, value_t x);
value_t DoBinary(token_t *token, value_t x, value_t y);
value_t EvaluatePrefix(expression_t *expr);
value_t EvaluatePostfix(expression_t *expr);
void ReadProgram(program_t *pgm);
void CreateStack(sstack_t *stack);
void Push(value_t x, sstack_t *stack);
void Pop(value_t *x, sstack_t *stack);
int StackEmpty(sstack_t *stack);
void Error(char *msg);

void Error(char *emsg)
{
    printf("error: %s\n", emsg);
}

void CreateStack(sstack_t *stack)
{
    stack->head = 0;
}

int StackEmpty(sstack_t *stack)
{
    return (stack->head == 0);
}

void Push(value_t x, sstack_t *stack)
{
    //printf("pushing: %x\n", x.i);
    stack->s[stack->head++] = x;
}

void Pop(value_t *x, sstack_t *stack)
{
    *x = stack->s[--stack->head];
}

KindType Internal(token_t *token)
{
    // hash lookup
    return OPERAND;
}

value_t GetValue(token_t *token)
{
    return token->v;
}

value_t DoUnary(token_t *token, value_t x)
{
    switch (token->v.c) {
        case '!':
            token->v.i = !x.i;
            break;
    }
    return token->v;
}

value_t DoBinary(token_t *token, value_t x, value_t y)
{
    switch (token->v.c) {
        case '+':
            token->v.i = x.i + y.i;
            break;
        case '-':
            token->v.i = x.i - y.i;
            break;
        case '*':
            token->v.i = x.i * y.i;
            break;
        case '/':
            token->v.i = x.i / y.i;
            break;
        case '^':
            token->v.i = x.i + y.i;
            break;
        case '%':
            token->v.i = x.i % y.i;
            break;
    }
    return (token->v);
}

#define EOL ('\n')
// parse next token, update symtab if necessary
void GetNextToken(token_t *token, expression_t *expr)
{
    value_t v;
    while (expr->e[expr->pos] != EOL && isspace(expr->e[expr->pos])) expr->pos++;
    v.c = expr->e[expr->pos++];
    token->v = v;
    token->t = Kind(token);
    if (token->t == OPERAND) {
        char word[8];
        int i = 0;
        expr->pos--;
        while (isdigit(word[i++] = expr->e[expr->pos++])) ;
        //printf("word: %s\n", word);
        token->v.i = atoi(word);
    }
}


KindType Kind(token_t *token)
{
    //printf("what: %x\n", token->v.c);
    switch(token->v.c)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '%':
            //printf("is binop: %c\n", token->v.c);
            return BINARYOP;
        case '!':
            //printf("is unop: %c\n", token->v.c);
            return UNARYOP;
        case '\n':
            //printf("is end: %c\n", token->v.c);
            return ENDEXPR;
    }
    if (isdigit(token->v.c)) {
        //printf("is digit: %c\n", token->v.c);
        return OPERAND;
    }
    if (isalpha(token->v.c)) {
        //printf("is sym: %x\n", token->v.c);
        return SYMOP;
    }
    //printf("is nop: %x\n", token->v.c);
    return NOP;
}

value_t EvaluatePostfix(expression_t *expr)
{
    KindType type;
    token_t token;
    value_t x, y;
    sstack_t stack;
    CreateStack(&stack);
    do {
        GetNextToken(&token, expr);
        type = token.t;
        //printf("token: %x, type: %x\n", token.v.c, token.t);
        switch (type) {
            case OPERAND:
                //printf("operand: %d\n", token.v.i);
                Push(GetValue(&token), &stack);
                break;
            case UNARYOP:
                //printf("unary:   %c\n", token.v.c);
                Pop(&x, &stack);
                Push(DoUnary(&token, x), &stack);
                break;
            case BINARYOP:
                //printf("binary:  %c\n", token.v.c);
                Pop(&x, &stack);
                Pop(&y, &stack);
                Push(DoBinary(&token, x, y), &stack);
                break;
            case SYMOP:
            case NOP:
                break;
            case ENDEXPR:
                //printf("end:     %d\n", token.v.c);
                Pop(&x, &stack);
                if (!StackEmpty(&stack))
                    Error("Incorrect expression");
                break;
        }
    } while (type != ENDEXPR);
    return x;
}


void ShowExp(expression_t *expr)
{
    int i;
    value_t v;
    printf("expr len %d\n", expr->len);
    for (i = 0; i < expr->len; i++) {
        v.c = expr->e[i];
        printf("%c ", v.c);
    }
    printf("\n");
}

void ShowPgm(program_t *pgm)
{
    int i;
    for (i = 0; i < pgm->n_expr; i++) {
        ShowExp(&pgm->p[i]);
    }
}

/*
test.p

12+
24+

*/

void ReadProgram(program_t *pgm)
{
    int line_no = 0;
    FILE *p = fopen("test.p", "rt");
    if (p) {
        ssize_t read;
        size_t len = 256;
        char line[256];
        char *pline = line;
        while((read = getline(&pline, &len, p)) != -1) {
            strcpy(pgm->p[line_no].e, line);
            pgm->p[line_no].len = strlen(pgm->p[line_no].e);
            pgm->p[line_no].pos = 0;
            line_no++;
        }
    }
    pgm->n_expr = line_no;

}

void repl()
{
    int line_no = 0;
    program_t pgm;
    ssize_t read;
    size_t len = 256;
    char line[256];
    char *pline = line;
    printf("> ");
    while((read = getline(&pline, &len, stdin)) != -1) {
        if (strstr(pline, "quit")) {
            return;
        }
        strcpy(pgm.p[line_no].e, line);
        pgm.p[line_no].len = strlen(line);
        pgm.p[line_no].pos = 0;
        ShowExp(&pgm.p[line_no]);
        value_t v = EvaluatePostfix(&pgm.p[line_no]);
        printf("> %d\n", v.i);
        printf("> ");
        line_no++;
    }
}

void pgm()
{
    program_t pgm;
    ReadProgram(&pgm);
    for (int i = 0; i < pgm.n_expr; i++) {
        ShowExp(&pgm.p[i]);
        value_t v = EvaluatePostfix(&pgm.p[i]);
        printf("=> %d\n", v.i);
    }
}

int main()
{
    //pgm();
    repl();
}

