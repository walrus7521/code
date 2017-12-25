#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>

/*
    Next: add spaces in input

 */

typedef enum { OPERAND, UNARYOP, BINARYOP, SYMOP, NOP, ENDEXPR } KindType; // ENDEXPR is '\n'

typedef struct {
    union {
        int i;
        float f;
        char c;
    };
    char sym[8];
} Value;

typedef struct {
    int head;
    Value s[256];
} Stack;

typedef struct {
    KindType t;
    Value v;
} Token;

typedef struct {
    int pos;
    int len;
    char e[256];
} Expression;

typedef struct {
    int n_expr;
    Expression p[256];
} Program;

void ShowPgm(Program *pgm);
void ShowExp(Expression *expr);
KindType Kind(Token *token);
Value GetValue(Token *token);
void GetNextToken(Token *token, Expression *expr);
Value DoUnary(Token *token, Value x);
Value DoBinary(Token *token, Value x, Value y);
Value EvaluatePrefix(Expression *expr);
Value EvaluatePostfix(Expression *expr);
void ReadProgram(Program *pgm);
void CreateStack(Stack *stack);
void Push(Value x, Stack *stack);
void Pop(Value *x, Stack *stack);
int StackEmpty(Stack *stack);
void Error(char *msg);

void Error(char *emsg)
{
    printf("error: %s\n", emsg);
}

void CreateStack(Stack *stack)
{
    stack->head = 0;
}

int StackEmpty(Stack *stack)
{
    return (stack->head == 0);
}

void Push(Value x, Stack *stack)
{
    //printf("pushing: %x\n", x.i);
    stack->s[stack->head++] = x;
}

void Pop(Value *x, Stack *stack)
{
    *x = stack->s[--stack->head];
}

KindType Internal(Token *token)
{
    // hash lookup
    return OPERAND;
}

Value GetValue(Token *token)
{
    return token->v;
}

Value DoUnary(Token *token, Value x)
{
    switch (token->v.c) {
        case '!':
            token->v.i = !x.i;
            break;
    }
    return token->v;
}

Value DoBinary(Token *token, Value x, Value y)
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

// parse next token, update symtab if necessary
void GetNextToken(Token *token, Expression *expr)
{
    Value v;
    //while (isspace(expr->e[expr->pos])) expr->pos++;
    //while (expr->e[expr->pos] == 0) expr->pos++;
    v.c = expr->e[expr->pos++];
    //printf("got token: %c\n", v.c);
    token->v = v;
    token->t = Kind(token);
    // BUGBUG if OPERAND get all the bytes for the number
    if (token->t == OPERAND) token->v.i -= '0';
    //while (isspace(expr->e[expr->pos++])) ;
    //while (expr->e[expr->pos] == 0) expr->pos++;
}


KindType Kind(Token *token)
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

Value EvaluatePostfix(Expression *expr)
{
    KindType type;
    Token token;
    Value x, y;
    Stack stack;
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

#if 0
Value EvaluatePrefix(Expression expr)
{
    Token token;
    Value x, y;
    GetNextToken(token, expr);
    switch (Kind(token)) {
        case OPERAND:
            return GetValue(token);
        case UNARYOP:
            x = EvaluatePrefix(expr);
            return DoUnary(token, x);
        case BINARYOP:
            x = EvaluatePrefix(expr);
            y = EvaluatePrefix(expr);
            return DoBinary(token, x, y);
    }
}
#endif

void ShowExp(Expression *expr)
{
    int i;
    Value v;
    for (i = 0; i < expr->len; i++) {
        v.c = expr->e[i];
        printf("%c ", v.c);
    }
    printf("\n");
}

void ShowPgm(Program *pgm)
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

void ReadProgram(Program *pgm)
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

int main()
{
    Program pgm;
    ReadProgram(&pgm);
    for (int i = 0; i < pgm.n_expr; i++) {
        ShowExp(&pgm.p[i]);
        Value v = EvaluatePostfix(&pgm.p[i]);
        printf("=> %d\n", v.i);
    }
}

