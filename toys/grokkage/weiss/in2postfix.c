#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

typedef char e_v;
#define SIZE_STAK 256
#include "stak.inc"

#define BOTTOMMARKER '$'

typedef enum { EOF_T, EOL_T, OPERATOR_T, VARIABLE_T, RIGHTPAREN_T } inputtype;

typedef struct {
    inputtype tokentype;
    char tokenvalue;
} tokendata;

int inputprec(char c);
tokendata *gettoken();
int stackprec();
void skiptoeol();


void skiptoeol()
{
    tokendata *p_token;
    do {
        p_token = gettoken();

    } while (p_token->tokentype != EOL_T &&
             p_token->tokentype != EOF_T);
}

tokendata *gettoken()
{
    static bool eof = false;
    static char buffer[BUFSIZ], *bufptr = NULL;
    static tokendata token;
    char *operators = "+-*/(";

    if (eof == true) {
        token.tokentype = EOF_T;
        return &token;
    }

    if (bufptr == NULL) {
        printf("? ");
        if ((bufptr = gets(buffer)) == NULL || *bufptr == '\0') {
            eof = true;
            token.tokentype = EOF_T;
            return &token;
        }
    }

    while (isspace(*bufptr)) bufptr++;

    if (*bufptr == '\0') 
        token.tokentype = EOL_T;
    else if (*bufptr == ')')
        token.tokentype = RIGHTPAREN_T;
    else if (strchr(operators, *bufptr) != NULL)
        token.tokentype = OPERATOR_T;
    else
        token.tokentype = VARIABLE_T;
    
    token.tokenvalue = *bufptr;

    if (token.tokentype == EOL_T)
        bufptr = NULL;
    else
        bufptr++;

    return &token;
}

int stackprec()
{
    char topsymbol;

    topsymbol = stkpeek();
    switch (topsymbol)
    {
        case '(':
            return 0;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        case '$':
            return -1;
        default:
            printf("unknown sym on stack: %c\n", topsymbol);
            return -1;
    }
    return -1;
}

int inputprec(char c)
{
    switch (c) {
        case '(':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            printf("unknown op\n");
            return -1;
    }
    return -1;
}

int main()
{
    tokendata *p_token;
    char stacksymbol;
    bool eofreached = false;

    init_stak();

    stkpush(BOTTOMMARKER);
    
    do {
        p_token = gettoken();
        switch (p_token->tokentype) {
            case EOF_T:
                eofreached = true;
                break;
            case VARIABLE_T:
                printf("%c ", p_token->tokenvalue);
                break;
            case OPERATOR_T:
                printf("%c ", p_token->tokenvalue);
                while (stackprec() >= inputprec(p_token->tokenvalue)) {
                    stacksymbol = stkpop();
                    printf("%c ", stacksymbol);
                }
                stkpush(p_token->tokenvalue);
                break;
            case RIGHTPAREN_T:
                do {
                    stacksymbol = stkpop();
                    if (stacksymbol == BOTTOMMARKER) {
                        printf("error in expression\n");
                        skiptoeol();
                        init_stak();
                        break;
                    }
                    if (stacksymbol == '(')
                        printf("%c ", stacksymbol);
                } while (stacksymbol != '(');
                break;
            case EOL_T:
                stacksymbol = stkpeek();
                while (stacksymbol != BOTTOMMARKER) {
                    stacksymbol = stkpop();
                    if (stacksymbol == '(') {
                        printf("error in expression\n");
                        init_stak();
                    } else {
                        printf("%c ", stacksymbol);
                    }
                    stacksymbol = stkpeek();
                }
                putchar('\n');
                break;
        }

    } while (eofreached == false);

}

