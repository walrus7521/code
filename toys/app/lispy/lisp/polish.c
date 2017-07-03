#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpc.h"


// linux
// gcc -std=c99 -Wall polish.c mpc.c -ledit -lreadline -o polish
// windows
// gcc -std=c99 -Wall polish.c mpc.c -o polish

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

lval lval_num(long x)
{
    lval v;
    v.type = LVAL_NUM;
    v.num = x;
    return v;
}

lval lval_err(int x)
{
    lval v;
    v.type = LVAL_ERR;
    v.err = x;
    return v;
}

void lval_print(lval v)
{
    switch (v.type) {
    case LVAL_NUM: printf("%li", v.num); break;
    case LVAL_ERR: 
        if (v.err == LERR_DIV_ZERO) {
            printf("Error: Division by zero.");
        } else if (v.err == LERR_BAD_OP) {
            printf("Error: Invalid operand.");
        } else if (v.err == LERR_BAD_NUM) {
            printf("Error: Invalid number.");
        }
        break;
    }
}

void lval_println(lval v) { lval_print(v); putchar('\n'); }

lval eval_op(lval x, char *op, lval y)
{
    if (x.type == LVAL_ERR) { return x; }
    if (y.type == LVAL_ERR) { return y; }

    if (strcmp(op, "+") == 0) { return lval_num(x.num + y.num); }
    if (strcmp(op, "-") == 0) { return lval_num(x.num - y.num); }
    if (strcmp(op, "*") == 0) { return lval_num(x.num * y.num); }
    if (strcmp(op, "/") == 0) { 
        return y.num == 0 
            ? lval_err(LERR_DIV_ZERO)
            : lval_num(x.num / y.num); 
    }

    return lval_err(LERR_BAD_OP);
}

lval eval(mpc_ast_t* t)
{
    /* if tagged as number return it directly - base case */
    if (strstr(t->tag, "number")) {
        /* chk if error in conversion */
        errno = 0;
        long x = strtol(t->contents, NULL, 10);
        return errno != ERANGE ? lval_num(x) : lval_err(LERR_BAD_NUM);
    }

    /* the operator is always the 2nd child, first is ( */
    char *op = t->children[1]->contents;

    /* store 3rd child in x */
    lval x = eval(t->children[2]);

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
    mpc_parser_t* Polish    = mpc_new("polish");

    mpca_lang(MPCA_LANG_DEFAULT,
            "                                                   \
            number    : /-?[0-9]+/ ;                            \
            operator  : '+' | '-' | '*' | '/' | '%' ;           \
            expr      : <number> | '(' <operator> <expr>+ ')' ; \
            polish     : /^/ <operator> <expr>+ /$/ ;            \
            ",
        Number, Operator, Expr, Polish);

  puts("Polish Version 0.0.0.0.1");
  puts("Press Ctrl+c to Exit\n");

  while (1) {

    /* Now in either case readline will be correctly defined */
    char* input = readline("polish> ");

    add_history(input);

    if (strncmp(input, "quit", 4) == 0) {
        printf("bye bye\n");
        exit(0);
    }

    mpc_result_t r;
    if (mpc_parse("<stdin", input, Polish, &r)) {
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
        lval result = eval(r.output);
        lval_println(result);
        mpc_ast_delete(r.output);
    } else {
        mpc_err_print(r.error);
        mpc_err_delete(r.error);
    }

    free(input);

  }

  mpc_cleanup(4, Number, Operator, Expr, Polish);

  return 0;
}
