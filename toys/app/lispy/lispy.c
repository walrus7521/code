#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpc.h"


// linux
// gcc -std=c99 -Wall lispy.c mpc.c -ledit -lreadline -o lispy
// windows
// gcc -std=c99 -Wall lispy.c mpc.c -o lispy

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

enum { LVAL_NUM, LVAL_ERR };
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

typedef struct {
    int type;
    long num;
    int err;
} lval;


int number_of_nodes(mpc_ast_t *t)
{
    if (t->children_num == 0) { return 1; }
    if (t->children_num >= 1) {
        int total = 1;
        int i;
        for (i = 0; i < t->children_num; i++) {
            total = total + number_of_nodes(t->children[i]);
        }
        return total;
    }
    return 0;
}

long eval_op(long x, char *op, long y)
{
    if (strcmp(op, "+") == 0) { return x + y; }
    if (strcmp(op, "-") == 0) { return x - y; }
    if (strcmp(op, "*") == 0) { return x * y; }
    if (strcmp(op, "/") == 0) { return x / y; }
    return 0;
}

long eval(mpc_ast_t* t)
{
    /* if tagged as number return it directly - base case */
    if (strstr(t->tag, "number")) {
        return (atoi(t->contents));
    }

    /* the operator is always the 2nd child, first is ( */
    char *op = t->children[1]->contents;

    /* store 3rd child in x */
    long x = eval(t->children[2]);

    /* iterate remaining children and combine */
    int i = 3;
    while (strstr(t->children[i]->tag, "expr")) {
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }

    return x;

}

int main(int argc, char** argv) {

    mpc_parser_t* Number   = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr     = mpc_new("expr");
    mpc_parser_t* Lispy    = mpc_new("lispy");

    mpca_lang(MPCA_LANG_DEFAULT,
            "                                                   \
            number    : /-?[0-9]+/ ;                            \
            operator  : '+' | '-' | '*' | '/' | '%' ;           \
            expr      : <number> | '(' <operator> <expr>+ ')' ; \
            lispy     : /^/ <operator> <expr>+ /$/ ;            \
            ",
        Number, Operator, Expr, Lispy);

  puts("Lispy Version 0.0.0.0.1");
  puts("Press Ctrl+c to Exit\n");

  while (1) {

    /* Now in either case readline will be correctly defined */
    char* input = readline("lispy> ");

    add_history(input);

    if (strncmp(input, "quit", 4) == 0) {
        printf("bye bye\n");
        exit(0);
    }

    mpc_result_t r;
    if (mpc_parse("<stdin", input, Lispy, &r)) {
#if 0
        mpc_ast_t* a = r.output;
        printf("Tag: %s\n", a->tag);
        printf("Contents: %s\n", a->contents);
        printf("Num children: %d\n", a->children_num);
        mpc_ast_t* c0 = a->children[0];
        printf("First child tag: %s\n", c0->tag);
        printf("First child contents: %s\n", c0->contents);
        printf("First child Num children: %d\n", c0->children_num);

        printf("number of nodes: %d\n", number_of_nodes(a));

        mpc_ast_print(r.output);
#endif
        long result = eval(r.output);
        printf("%li\n", result);
        mpc_ast_delete(r.output);
    } else {
        mpc_err_print(r.error);
        mpc_err_delete(r.error);
    }

    free(input);

  }

  mpc_cleanup(4, Number, Operator, Expr, Lispy);

  return 0;
}
