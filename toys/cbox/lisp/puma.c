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

lval eval_func(mpc_ast_t* t, int d)
{
    lval x;
    printf("func tag: %s, contents: %s, num: %d\n", t->tag, t->contents, t->children_num);
    for (int i = 0; i < t->children_num; i++) {
        if (strstr(t->children[i]->tag, "params")) {
            printf("got a param\n");
        }
        eval_func(t->children[i], d+1);
        //printf("tag: %s, child: %s\n", t->children[i]->tag, t->children[i]->contents);
    }
    return x;
}

lval eval(mpc_ast_t* t, int d)
{
    lval x;    
    for (int i = 0; i < d; i++) {
        printf("  ");
    }
    printf("tag: %s, contents: %s, num: %d\n", t->tag, t->contents, t->children_num);
    if (strstr(t->tag, "function")) {
        eval_func(t, d);
        //printf("%s(", t->contents);
        //mpc_ast_t *
        //for (int i = 0; i < t->childre
        //printf("%s(", t->contents);
    }
    /* if tagged as number return it directly - base case */
    //("operator");
    //("params");
    //("function");
    //("expr");
    //("puma");
    //if (strstr(t->tag, "number")) {
    //    /* chk if error in conversion */
    //    errno = 0;
    //    long x = strtol(t->contents, NULL, 10);
    //    return errno != ERANGE ? lval_num(x) : lval_err(LERR_BAD_NUM);
    //}

    /* the operator is always the 2nd child, first is ( */
    //char *op = t->children[1]->contents;

    /* iterate remaining children and combine */
    for (int i = 0; i < t->children_num; i++) {
    //    if (strstr(t->children[i]->tag, "params")) {
    //        printf("got a param\n");
    //    }
        eval(t->children[i], d+1);
    //    //printf("tag: %s, child: %s\n", t->children[i]->tag, t->children[i]->contents);
    }

    return x;
}

static mpc_val_t *callback(mpc_val_t *x)
{
    printf("callback\n"); //number: %s\n", (char *) x);
    return x;
}

int main(int argc, char** argv) {

    mpc_parser_t* Number   = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Params   = mpc_new("params");
    mpc_parser_t* Function = mpc_new("function");
    mpc_parser_t* Expr     = mpc_new("expr");
    mpc_parser_t* Puma     = mpc_new("puma");

    mpc_apply(Number, callback);
    mpc_apply(Operator, callback);
    mpc_apply(Params, callback);
    mpc_apply(Function, callback);
    mpc_apply(Expr, callback);
    mpc_apply(Puma, callback);

    mpca_lang(MPCA_LANG_DEFAULT,
            "                                           \
            number    : /-?[0-9]+/ ;                    \
            operator  : '+' | '-' | '*' | '/' | '%' ;   \
            params    : <number> (',' <number>)* ;      \
            function  : \"mode\"                        \
                      | \"scenario\"                    \
                      | \"activate\"                    \
                      | \"associate\"                   \
                      | \"wait\"                        \
                      | \"send\"                        \
                      | \"ring\"                        \
                      | \"signal\"                      \
                      | \"log\"                         \
                      | \"free\"                        \
                      | \"exec\" ;                      \
            expr      : <function> '(' <params>* ')' ;  \
            puma      : /^/ <expr>+ /$/ ;               \
            ",
        Number, Operator, Params, Function, Expr, Puma);

  puts("Puma Version 0.0.0.0.1");
  puts("Press Ctrl+c to Exit\n");

  while (1) {

    /* Now in either case readline will be correctly defined */
    char* input = readline("puma> ");

    add_history(input);

    if (strncmp(input, "quit", 4) == 0) {
        printf("bye bye\n");
        free(input);
        break;
    } else if (strlen(input) == 0) {
        continue;
    }

    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Puma, &r)) {
        lval result = eval(r.output, 0);
        //lval_println(result);
        mpc_ast_print(r.output);
        mpc_ast_delete(r.output);
    } else {
        mpc_err_print(r.error);
        mpc_err_delete(r.error);
    }
    free(input);
  }

  mpc_cleanup(6, Number, Operator, Params, Function, Expr, Puma);

  return 0;
}

