#include <stdio.h>
#include "lexer.h"
#include "expr.h"
#include "symtab.h"
#include "tree.h"

int main()
{
    int result;
    tree T;
    symbol_table symtab;
    char yn;

    printf("enter expression:\n");
    if (read_expr(&T) == ERROR) {
        fprintf(stderr, "error reading expression\n");
        exit(-1);
    }

    printf("Expression is: ");
    print_expr(T);
    return 0;

    do {
        read_symbols(&symtab, 1, 2, 3);
        eval_expr(T, symtab, &result);
        printf("Expression value is %d\n", result);
        printf("Are there more expressions (y orn n)? ");
        scanf(" %c", &yn);
    } while (yn == 'y' || yn == 'Y');


    tokendata *token = gettoken();
    printf("token: %d '%c'\n", token->tokentype, token->tokenvalue);
}

