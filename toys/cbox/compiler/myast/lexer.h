#ifndef _LEXER_H_
#define _LEXER_H_

#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "common.h"

typedef enum { EOF_T, EOL_T, CONSTANT_T, OPERATOR_T, VARIABLE_T, RIGHTPAREN_T } inputtype;
typedef struct {
    inputtype tokentype;
    char tokenvalue;
} tokendata;

bool isoperator(char c);
tokendata *gettoken();


#endif // _LEXER_H_
