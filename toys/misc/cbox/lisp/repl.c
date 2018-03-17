#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpc.h"

// linux
// gcc -std=c99 -Wall repl.c mpc.c -ledit -lreadline -o repl
// windows
// gcc -std=c99 -Wall repl.c mpc.c -o repl

/* If we are compiling on Windows compile these functions */
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

/* Fake readline function */
char* readline(char* prompt) {
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char* cpy = malloc(strlen(buffer)+1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy)-1] = '\0';
    return cpy;
}

/* Fake add_history function */
void add_history(char* unused) {
}

/* Otherwise include the editline headers */
#else
#include <editline/readline.h>
//#include <editline/history.h>
#endif

long eval_op(long x, char *op, long y)
{
    if (strcmp(op, "+") == 0) { return x + y; }
    if (strcmp(op, "-") == 0) { return x - y; }
    if (strcmp(op, "*") == 0) { return x * y; }
    if (strcmp(op, "/") == 0) { return x / y; }
    return 0;
}

long eval(mpc_ast_t *t)
{
    if (strstr(t->tag, "number")) {
        return atoi(t->contents);
    }

    // the operator is always 2nd
    char *op = t->children[1]->contents;

    // store the 3rd child in x
    long x = eval(t->children[2]);

    // iterate remaining children
    int i = 3;
    while (strstr(t->children[i]->tag, "expr")) {
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }

    return x;
}

int main(int argc, char** argv) {

    puts("Polish Version 0.0.0.0.1");
    puts("Press Ctrl+c to Exit\n");

    mpc_parser_t* Number    = mpc_new("number");
    mpc_parser_t* Operator  = mpc_new("operator");
    mpc_parser_t* Expr      = mpc_new("expr");
    mpc_parser_t* Lispy     = mpc_new("lispy");

    mpca_lang(MPCA_LANG_DEFAULT,
        "                                                           \
            number      : /-?[0-9]+/ ;                              \
            operator    : '+' | '-' | '*' | '/' ;                   \
            expr        : <number> | '(' <operator> <expr>+ ')' ;   \
            lispy       : /^/ <operator> <expr>+ /$/ ;              \
        ",
        Number, Operator, Expr, Lispy);

    while (1) {

        /* Now in either case readline will be correctly defined */
        char* input = readline("polish> ");

        add_history(input);

        //printf("%s\n", input);
        if (strcmp(input, "quit") == 0) {
            free(input);
            break;
        }

        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r)) {
            // on success print the ast
            long result = eval(r.output);
            printf("%li\n", result);
            //mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        } else {
            // on error print the error
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);

    }

    mpc_cleanup(4, Number, Operator, Expr, Lispy);

    return 0;
}

