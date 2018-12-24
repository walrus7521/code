#include <stdio.h>
#include "myast.h"
#include "symtab.h"

int main()
{
    int result;
    symbol_table symtab;

    tokendata *token = gettoken();
    printf("token: %d '%c'\n", token->tokentype, token->tokenvalue);
}

