#include <stdio.h>
#include "lexer.h"
#include "symtab.h"
#include "tree.h"

int main()
{
    int result;
    tree T;
    symbol_table symtab;
    char yn;

    printf("enter expression:\n");


    tokendata *token = gettoken();
    printf("token: %d '%c'\n", token->tokentype, token->tokenvalue);
}

