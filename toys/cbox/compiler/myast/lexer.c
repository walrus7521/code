#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"


bool isoperator(char c)
{
    return (c == '*' || c == '/' || c == '+' || c == '-');
}

void show_token(tokendata token)
{
    switch (token.tokentype) {
        case EOF_T:         printf("EOF:          "); break;
        case EOL_T:         printf("EOL:          "); break;
        case CONSTANT_T:    printf("CONSTANT:   %c", token.tokenvalue); break;
        case OPERATOR_T:    printf("OPERATOR:   %c", token.tokenvalue); break;
        case VARIABLE_T:    printf("VARIABLE:   %c", token.tokenvalue); break;
        case RIGHTPAREN_T:  printf("RIGHTPAREN    "); break;
    }
    printf("\n");
}

tokendata *gettoken()
{
    static tokendata token;
    static char buffer[BUFSIZ], *bufptr;

    if (bufptr == NULL) {
        if ((bufptr = fgets(buffer, sizeof(buffer), stdin)) == NULL) {
            buffer[0] = '\0';
            bufptr = buffer;
        }
    }

    while (*bufptr != '\0' && isspace(*bufptr)) bufptr++;
    if (*bufptr == '\0')
        token.tokentype = EOL_T;
    else if (isdigit(*bufptr))
        token.tokentype = CONSTANT_T;
    else if (isoperator(*bufptr))
        token.tokentype = OPERATOR_T;
    else
        token.tokentype = VARIABLE_T;
    token.tokenvalue = toupper(*bufptr);
    bufptr++;

    //show_token(token);
    return &token;
}


