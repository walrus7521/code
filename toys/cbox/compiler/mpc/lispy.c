#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpc.h"

#define LASSERT(args, cond, err) \
    if (!(cond)) { lval_del(args); return lval_err(err); }

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

// fwd declarations
struct lval;
struct lenv;
typedef struct lval lval;
typedef struct lenv lenv;

enum { LVAL_ERR, LVAL_NUM, LVAL_SYM, 
       LVAL_FUN, LVAL_SEXPR, LVAL_QEXPR };

enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

typedef lval*(*lbuiltin)(lenv*, lval*);

typedef struct lval {
    int type;

    long num;
    char *err;
    char *sym;
    lbuiltin fun;

    int count;
    struct lval** cell;
} lval;

// symtab
struct lenv {
    int count;
    char **syms;
    lval **vals;
};

// fwd declarations
void lval_print(lval *v);
void lval_expr_print(lval *v, char open, char close);
lval *lval_eval_sexpr(lenv *e, lval *v);
lval *lval_eval(lenv *e, lval *v);
lval *builtin(lval *a, char *func);
lval *lval_join(lval *x, lval *y);
lval *builtin_op(lenv *e, lval *a, char *op);
lval *builtin_add(lenv *e, lval *a);
lval *builtin_sub(lenv *e, lval *a);
lval *builtin_mul(lenv *e, lval *a);
lval *builtin_div(lenv *e, lval *a);
lval *builtin_eval(lenv *e, lval *a);
lval *builtin_list(lenv *e, lval *a);
lval *builtin_head(lenv *e, lval *a);
lval *builtin_tail(lenv *e, lval *a);
lval *builtin_eval(lenv *e, lval *a);
lval *builtin_join(lenv *e, lval *a);
lval *builtin_def(lenv *e, lval *a);

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

// constructors
lval *lval_num(long x)
{
    lval *v = malloc(sizeof(lval));
    v->type = LVAL_NUM;
    v->num = x;
    return v;
}

lval *lval_err(char *m)
{
    lval *v = malloc(sizeof(lval));
    v->type = LVAL_ERR;
    v->err = malloc(strlen(m)+1);
    strcpy(v->err, m);
    return v;
}

lval *lval_sym(char *s)
{
    lval *v = malloc(sizeof(lval));
    v->type = LVAL_SYM;
    v->sym = malloc(strlen(s)+1);
    strcpy(v->sym, s);
    return v;
}

lval *lval_sexpr(void)
{
    lval *v = malloc(sizeof(lval));
    v->type = LVAL_SEXPR;
    v->count = 0;
    v->cell = NULL;
    return v;
}

lval *lval_qexpr(void)
{
    lval *v = malloc(sizeof(lval));
    v->type = LVAL_QEXPR;
    v->count = 0;
    v->cell = NULL;
    return v;
}

lval *lval_fun(lbuiltin func)
{
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_FUN;
    v->fun = func;
    return v;
}

// copy constructor
lval *lval_copy(lval *v)
{
    lval *x = malloc(sizeof(lval));
    x->type = v->type;

    switch (v->type) {
    // copy numbers and functions directly
    case LVAL_NUM: x->num = v->num; break;
    case LVAL_FUN: x->fun = v->fun; break;

    case LVAL_ERR: 
        x->err = malloc(strlen(v->err)+1);
        strcpy(x->err, v->err);
        break;

    case LVAL_SYM: 
        x->sym = malloc(strlen(v->sym)+1);
        strcpy(x->sym, v->sym);
        break;

    case LVAL_QEXPR:
    case LVAL_SEXPR:
        x->count = v->count;
        x->cell = malloc(sizeof(lval*) * x->count);
        for (int i = 0; i < x->count; i++) {
            x->cell[i] = lval_copy(x->cell[i]);
        }
        break;
    }
    return x;
}

// lval destructor
void lval_del(lval *v)
{
    switch (v->type) {
    case LVAL_NUM: break;
    case LVAL_ERR: free(v->err); break;
    case LVAL_SYM: free(v->sym); break;
    case LVAL_QEXPR:
    case LVAL_SEXPR:
        for (int i = 0; i < v->count; i++) {
            lval_del(v->cell[i]);
        }
        free(v->cell);
        break;
    case LVAL_FUN: break;
    }
    free(v);
}

// lenv constructor
lenv *lenv_new(void)
{
    lenv *e = malloc(sizeof(lenv));
    e->count = 0;
    e->syms = NULL;
    e->vals = NULL;
    return e;
}

// lval destructor
void lenv_del(lenv *e)
{
    for (int i = 0; i < e->count; i++) {
        free(e->syms[i]);
        lval_del(e->vals[i]);
    }
    free(e->syms);
    free(e->vals);
    free(e);
}

// symbol getter
lval *lenv_get(lenv *e, lval *k)
{
    for (int i = 0; i < e->count; i++) {
        // see if there's a match
        if (strcmp(e->syms[i], k->sym) == 0) {
            return lval_copy(e->vals[i]);
        }
    }
    // no symbol found
    return lval_err("unbound symbol.");
}

// symbol putter, no dups, replacer
void lenv_put(lenv *e, lval *k, lval *v)
{
    // check for existing
    for (int i = 0; i < e->count; i++) {
        // if found, delete old, replace new
        if (strcmp(e->syms[i], k->sym) == 0) {
            lval_del(e->vals[i]);
            e->vals[i] = lval_copy(v);
            return;
        }
    }
    
    // no existing entry found
    e->vals = realloc(e->vals, sizeof(lval*) * e->count+1);
    e->syms = realloc(e->syms, sizeof(char*) * e->count+1);

    // copy lval and sym to new location
    e->vals[e->count] = lval_copy(v);
    e->syms[e->count] = malloc(strlen(k->sym)+1);
    strcpy(e->syms[e->count], k->sym);
    e->count++;
}

// lenv helpers
void lenv_add_builtin(lenv *e, char *name, lbuiltin func)
{
    lval *k = lval_sym(name);
    lval *v = lval_fun(func);
    lenv_put(e,k,v);
    lval_del(k); lval_del(v);
}

void lenv_add_builtins(lenv *e)
{
    // variable functions
    lenv_add_builtin(e, "def", builtin_def);

    // list functions
    lenv_add_builtin(e, "list", builtin_list);
    lenv_add_builtin(e, "head", builtin_head);
    lenv_add_builtin(e, "tail", builtin_tail);
    lenv_add_builtin(e, "eval", builtin_eval);
    lenv_add_builtin(e, "join", builtin_join);

    // math functions
    lenv_add_builtin(e, "+", builtin_add);
    lenv_add_builtin(e, "-", builtin_sub);
    lenv_add_builtin(e, "*", builtin_mul);
    lenv_add_builtin(e, "/", builtin_div);
}

lval* lval_read_num(mpc_ast_t *t)
{
    errno = 0;
    long x = strtol(t->contents, NULL, 10);
    return errno != ERANGE ?
        lval_num(x) : lval_err("invalid number");
}

lval* lval_add(lval *v, lval *x)
{
    v->count++;
    v->cell = realloc(v->cell, sizeof(lval*) * v->count);
    v->cell[v->count-1] = x;
    return v;
}

lval* lval_read(mpc_ast_t *t)
{
    // sym or num return conversion to that type
    if (strstr(t->tag, "number")) { return lval_read_num(t); }
    if (strstr(t->tag, "symbol")) { return lval_sym(t->contents); }

    // if root (>) or sexpr then create empty list
    lval *x = NULL;
    if (strcmp(t->tag, ">") == 0) { x = lval_sexpr(); }
    if (strstr(t->tag, "sexpr"))  { x = lval_sexpr(); }
    if (strstr(t->tag, "qexpr"))  { x = lval_qexpr(); }

    // fill this list with any valid expression contained within
    for (int i = 0; i < t->children_num; i++) {
        if (strcmp(t->children[i]->contents, "(") == 0) { continue; }
        if (strcmp(t->children[i]->contents, ")") == 0) { continue; }
        if (strcmp(t->children[i]->contents, "{") == 0) { continue; }
        if (strcmp(t->children[i]->contents, "}") == 0) { continue; }
        if (strcmp(t->children[i]->tag,  "regex") == 0) { continue; }
        x = lval_add(x, lval_read(t->children[i]));
    }

    return x;
}

void lval_print(lval *v)
{
    switch (v->type) {
    case LVAL_NUM:   printf("%li", v->num); break;
    case LVAL_ERR:   printf("Error: %s", v->err); break;
    case LVAL_SYM:   printf("%s", v->sym); break;
    case LVAL_SEXPR: lval_expr_print(v, '(', ')'); break;
    case LVAL_QEXPR: lval_expr_print(v, '{', '}'); break;
    case LVAL_FUN:   printf("<function>"); break;
    }
}

void lval_expr_print(lval *v, char open, char close)
{
    putchar(open);
    for (int i = 0; i < v->count; i++) {
        // print value
        lval_print(v->cell[i]);

        // don't print trailing space if last element
        if (i != (v->count-1)) {
            putchar(' ');
        }
    }
    putchar(close);
}

void lval_println(lval *v) { lval_print(v); putchar('\n'); }

lval *lval_pop(lval *v, int i)
{
    // fine the item at "i"
    lval *x = v->cell[i];

    // shift memory after the item i over the top
    memmove(&v->cell[i], &v->cell[i+1],
            sizeof(lval*) * (v->count-i-1));

    // decrease count of items on list
    v->count--;

    // reallocate memory used
    v->cell = realloc(v->cell, sizeof(lval*) * v->count);
    return x;
}

lval *lval_take(lval *v, int i)
{
    lval *x = lval_pop(v, i);
    lval_del(v);
    return x;
}

lval *lval_eval_sexpr(lenv *e, lval *v)
{
    // evaluate children
    for (int i = 0; i < v->count; i++) {
        v->cell[i] = lval_eval(e, v->cell[i]);
    }
    // error checking
    for (int i = 0; i < v->count; i++) {
        if (v->cell[i]->type == LVAL_ERR) { return lval_take(v, i); }
    }

    // empty expression
    if (v->count == 0) { return v; }
    // single expression
    if (v->count == 1) { return lval_take(v, 0); }

    // ensure first element is a symbol
    lval *f = lval_pop(v, 0);
    if (f->type != LVAL_FUN) {
        lval_del(v); lval_del(f);
        return lval_err("first element is not a function.");
    }

    // call built-in with operator
    lval *result = f->fun(e,v);
    lval_del(f);
    return result;
}

lval *lval_eval(lenv *e, lval *v)
{
    // evaluate sexpressions
    if (v->type == LVAL_SYM) {
        lval *x = lenv_get(e,v);
        lval_del(v);
        return x;
    }

    if (v->type == LVAL_SEXPR) { return lval_eval_sexpr(e,v); }
    // all other lval types remain the same
    return v;
}

// math builtins
lval *builtin_add(lenv *e, lval *a)
{
    return builtin_op(e,a,"+");
}

lval *builtin_sub(lenv *e, lval *a)
{
    return builtin_op(e,a,"-");
}

lval *builtin_mul(lenv *e, lval *a)
{
    return builtin_op(e,a,"*");
}

lval *builtin_div(lenv *e, lval *a)
{
    return builtin_op(e,a,"/");
}

lval *builtin_head(lenv *e, lval *a)
{
    LASSERT(a, a->count == 1,
            "Funcion head passed too many args.");
    LASSERT(a, a->cell[0]->type == LVAL_QEXPR,
            "Function head passed incorrect type.");
    LASSERT(a, a->cell[0]->count != 0,
            "Function head passed [].");
    lval *v = lval_take(a, 0);
    while (v->count > 1) { lval_del(lval_pop(v, 1)); }
    return v;
}

lval *builtin_tail(lenv *e, lval *a)
{
    LASSERT(a, a->count == 1,
            "Funcion tail passed too many args.");
    LASSERT(a, a->cell[0]->type == LVAL_QEXPR,
            "Function tail passed incorrect type.");
    LASSERT(a, a->cell[0]->count != 0,
            "Function tail passed [].");
    lval *v = lval_take(a, 0);
    lval_del(lval_pop(v, 0));
    return v;
}

lval *builtin_list(lenv *e, lval *a)
{
    a->type = LVAL_QEXPR;
    return a;
}

lval *builtin_eval(lenv *e, lval *a)
{
    LASSERT(a, a->count == 1,
            "Funcion eval passed too many args.");
    LASSERT(a, a->cell[0]->type == LVAL_QEXPR,
            "Function eval passed incorrect type.");
    lval *x = lval_take(a, 0);
    x->type = LVAL_SEXPR;
    return lval_eval(e,x);

}

lval *builtin_join(lenv *e, lval *a)
{
    for (int i = 0; i < a->count; i++) {
        LASSERT(a, a->cell[i]->type == LVAL_QEXPR,
                "Function join passed incorrect type.");
    }
    lval *x = lval_pop(a, 0);

    while (a->count) {
        x = lval_join(x, lval_pop(a, 0));
    }
    lval_del(a);
    return x;
}

lval *builtin_def(lenv *e, lval *a)
{
    LASSERT(a, a->cell[0]->type == LVAL_QEXPR,
            "Function def passed incorrect type.");

    // the first element is the symbol list
    lval *syms = a->cell[0];

    // ensure all elements of first list are symbols
    for (int i = 0; i < syms->count; i++) {
        LASSERT(a, syms->cell[i]->type == LVAL_SYM,
                "Function def cannot define non-symbols.");
    }

    // check for correct number of symbols and values
    LASSERT(a, syms->count == a->count-1,
            "Function def cannnot define incorrect"
            "number of values to symbols.");

    printf("here 1 count: %d\n", syms->count);
    // assign copies of values to symbols
    for (int i = 0; i < syms->count; i++) {
        lenv_put(e, syms->cell[i], a->cell[i+1]);
    }
    printf("here 2\n");

    lval_del(a);
    return lval_sexpr();
}

lval *lval_join(lval *x, lval *y)
{
    // for each cell in y, add it to x
    while (y->count) {
        x = lval_add(x, lval_pop(y, 0));
    }
    // delete the empty y and return x
    lval_del(y);
    return x;
}

lval *builtin_op(lenv *e, lval *a, char *op)
{
    // ensure all args are numbers
    for (int i = 0; i < a->count; i++) {
        if (a->cell[i]->type != LVAL_NUM) {
            return lval_err("Cannot operate on non-number.");
        }
    }

    // pop the first element
    lval *x = lval_pop(a, 0);

    // if no args and sub then perform unary negation
    if ((strcmp(op, "-") == 0) && a->count == 0) {
        x->num = -x->num;
    }

    // while there are still elements remaining
    while (a->count > 0) {
        // pop the next element
        lval *y = lval_pop(a, 0);

        if (strcmp(op, "+") == 0) { x->num += y->num; }
        if (strcmp(op, "-") == 0) { x->num -= y->num; }
        if (strcmp(op, "*") == 0) { x->num *= y->num; }
        if (strcmp(op, "/") == 0) { 
            if (y->num == 0) {
                lval_del(x); lval_del(y);
                x = lval_err("divide by zero"); break;
            }
            x->num /= y->num;
        }
        lval_del(y);
    }
    lval_del(a);
    return x;
}

#if 0
lval *builtin(lval *a, char *func)
{
    if (strcmp("list", func) == 0) { return builtin_list(e,a); }
    if (strcmp("head", func) == 0) { return builtin_head(e,a); }
    if (strcmp("tail", func) == 0) { return builtin_tail(e,a); }
    if (strcmp("join", func) == 0) { return builtin_join(e,a); }
    if (strcmp("eval", func) == 0) { return builtin_eval(e,a); }
    if (strstr("+-/*", func))      { return builtin_op(e,a,func); }
    lval_del(a);
    return lval_err("Unknown function.");
}
#endif

int main(int argc, char** argv) 
{
    mpc_parser_t* Number   = mpc_new("number");
    mpc_parser_t* Symbol   = mpc_new("symbol");
    mpc_parser_t* Sexpr    = mpc_new("sexpr");
    mpc_parser_t* Qexpr    = mpc_new("qexpr");
    mpc_parser_t* Expr     = mpc_new("expr");
    mpc_parser_t* Lispy    = mpc_new("lispy");

    mpca_lang(MPCA_LANG_DEFAULT,
            "                                                         \
            number    : /-?[0-9]+/ ;                                  \
            symbol    : /[a-zA-Z0-9_+\\-*\\/\\\\=<>!&]+/ ;            \
            sexpr     : '(' <expr>* ')' ;                             \
            qexpr     : '{' <expr>* '}' ;                             \
            expr      : <number> | <symbol> | <sexpr> | <qexpr> ;     \
            lispy     : /^/ <expr>* /$/ ;                             \
            ",
        Number, Symbol, Sexpr, Qexpr, Expr, Lispy);

    puts("Lispy Version 0.0.0.0.1");
    puts("Press Ctrl+c to Exit\n");

    lenv *e = lenv_new();
    lenv_add_builtins(e);

    while (1) {

        /* Now in either case readline will be correctly defined */
        char* input = readline("lispy> ");
        add_history(input);

        if (strncmp(input, "quit", 4) == 0) {
            printf("bye bye\n");
            exit(0);
        }

        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r)) {
            lval *x = lval_eval(e,lval_read(r.output));
            lval_println(x);
            lval_del(x);
            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);

    }

    lenv_del(e);
    mpc_cleanup(6, Number, Symbol, Sexpr, Qexpr, Expr, Lispy);

    return 0;
}
