#include <stdio.h>
#include <string.h>

typedef enum { OPERAND, UNARYOP, BINARYOP, ENDEXPR } KindType; // ENDEXPR is '\n'

typedef int Value;

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
void GetToken(Token *token, Expression *expr);
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
    stack->s[stack->head++] = x;
}

void Pop(Value *x, Stack *stack)
{
    *x = stack->s[--stack->head];
}

KindType Internal(Token *token)
{
    // hash lookup
}

KindType Kind(Token *token)
{
    switch(token->v)
    {
        case '+':
        case '-':
        case '*':
        case '/':
            return BINARYOP;
        case '\n':
            return ENDEXPR;
    }
    return OPERAND;
}

Value GetValue(Token *token)
{
    return token->v;
}

Value DoUnary(Token *token, Value x)
{
    return token->v;
}

Value DoBinary(Token *token, Value x, Value y)
{
    return (token->v = x + y);
}

void GetToken(Token *token, Expression *expr)
{
    Value v = expr->e[expr->pos++];
    token->v = v;
    token->t = Kind(token);
    if (token->t == OPERAND) token->v -= '0';
}

Value EvaluatePostfix(Expression *expr)
{
    KindType type;
    Token token;
    Value x, y;
    Stack stack;
    CreateStack(&stack);
    do {
        GetToken(&token, expr);
        printf("token: %c\n", token.v);
        switch (type = Kind(&token)) {
            case OPERAND:
                printf("operand: %d\n", token.v);
                Push(GetValue(&token), &stack);
                break;
            case UNARYOP:
                printf("unary:   %c\n", token.v);
                Pop(&x, &stack);
                Push(DoUnary(&token, x), &stack);
                break;
            case BINARYOP:
                printf("binary:  %c\n", token.v);
                Pop(&x, &stack);
                Pop(&y, &stack);
                Push(DoBinary(&token, x, y), &stack);
                break;
            case ENDEXPR:
                printf("end:     %d\n", token.v);
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
    GetToken(token, expr);
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
        v = expr->e[i];
        printf("%c ", v);
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
        printf("value: %d\n", v);
    }
}

