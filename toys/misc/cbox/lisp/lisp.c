#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpc.h"

// linux
// gcc -std=c99 -Wall lisp.c mpc.c -ledit -lreadline -o lisp
// windows
// gcc -std=c99 -Wall lisp.c mpc.c -o lisp

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

struct lval;
struct lenv;
typedef struct lval lval;
typedef struct lenv lenv;

typedef lval* (*lbuiltin)(lenv*, lval*);

struct lval {
    int type;

    // basic
    long num;
    char *err;
    char *sym;

    // function
    lbuiltin builtin;
    lenv *env;
    lval *formals;
    lval *body;

    // expression
    int count;
    lval** cell;

};

struct lenv {
    lenv *par;
    int count;
    char** syms;
    lval** vals;
};

enum { LVAL_ERR, LVAL_NUM, LVAL_SYM, LVAL_FUN, LVAL_SEXPR, LVAL_QEXPR };
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

char *ltype_name(int t)
{
    switch (t) {
        case LVAL_ERR:   return "Error";
        case LVAL_NUM:   return "Number";
        case LVAL_SYM:   return "Symbol";
        case LVAL_FUN:   return "Function";
        case LVAL_SEXPR: return "S-Expression";
        case LVAL_QEXPR: return "Q-Expression";
        default:         return "Unknown";
    }
}

lval *lval_num(long x)
{
    lval *v = malloc(sizeof(lval));
    v->type = LVAL_NUM;
    v->num = x;
    return v;
}

// prototypes
lval *lval_take(lval *v, int i);
lval *lval_eval(lenv* e, lval *v);
lval *lval_eval_sexpr(lenv* e, lval *v);
lval *lval_pop(lval *v, int i);
lval *builtin_list(lenv *e, lval *a);
lval *builtin_eval(lenv *e, lval *a);
lval *builtin_head(lenv *e, lval *a);
lval *builtin_tail(lenv *e, lval *a);
lval *builtin_join(lenv *e, lval *a);
lval *builtin_lambda(lenv *e, lval *a);
void lval_del(lval *v);
lval* lval_copy(lval* v);
lenv *lenv_copy(lenv *e);
void lenv_put(lenv* e, lval* k, lval* v);


lval *lval_err(char *fmt, ...)
{
    lval *v = malloc(sizeof(lval));
    v->type = LVAL_ERR;

    va_list va;
    va_start(va, fmt);

    v->err = malloc(512);

    vsnprintf(v->err, 511, fmt, va);

    v->err = realloc(v->err, strlen(v->err)+1);

    va_end(va);

    return v;
}

lenv* lenv_new(void)
{
    lenv* e = malloc(sizeof(lenv));
    e->par = NULL;
    e->count = 0;
    e->syms = NULL;
    e->vals = NULL;
    return e;
}

void lenv_del(lenv* e)
{
    for (int i = 0; i < e->count; i++) {
        free(e->syms[i]);
        lval_del(e->vals[i]);
    }
    free(e->syms);
    free(e->vals);
    free(e);
}

lval* lenv_get(lenv* e, lval* k)
{
    for (int i = 0; i < e->count; i++) {
        // check if stored string matches env
        if (strcmp(e->syms[i], k->sym) == 0) {
            return lval_copy(e->vals[i]);
        }
    }

    // if no symbol, check parent, else error
    if (e->par) {
        return lenv_get(e->par, k);
    } {
    // no match
        return lval_err("unbound symbols");
    }
}

// used to put definitions in the global env
void lenv_def(lenv *e, lval *k, lval *v)
{
    // iterate till e has no parent
    while (e->par) { e = e->par; }
    // put value in e
    lenv_put(e, k, v);
}

// used to put definitions in the local env
void lenv_put(lenv* e, lval* k, lval* v)
{
    // iterate over all items in env to see if exists
    for (int i = 0; i < e->count; i++) {
        // if found, del item and replace with v 
        if (strcmp(e->syms[i], k->sym) == 0) {
            lval_del(e->vals[i]);
            e->vals[i] = lval_copy(v);
            return;
        }
    }
    // no existing item found
    e->count++;
    e->vals = realloc(e->vals, sizeof(lval*) * e->count);
    e->syms = realloc(e->syms, sizeof(char*) * e->count);

    // copy contents f lval and sym string to new location
    e->vals[e->count-1] = lval_copy(v);
    e->syms[e->count-1] = malloc(strlen(k->sym)+1);
    strcpy(e->syms[e->count-1], k->sym);
}

lenv *lenv_copy(lenv *e)
{
    lenv *n = malloc(sizeof(lenv));
    n->par = e->par;
    n->count = e->count;
    n->syms = malloc(sizeof(char*) * n->count);
    n->vals = malloc(sizeof(lval*) * n->count);
    for (int i = 0; i < e->count; i++) {
        n->syms[i] = malloc(strlen(e->syms[i])+1);
        strcpy(n->syms[i], e->syms[i]);
        n->vals[i] = lval_copy(e->vals[i]);
    }
    return n;
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
    v->builtin = func;
    return v;
}

lval *lval_lambda(lval *formals, lval *body)
{
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_FUN;

    v->builtin = NULL;

    v->env = lenv_new();

    v->formals = formals;
    v->body = body;

    return v;
}

void lval_del(lval *v)
{
    switch (v->type) {
        case LVAL_FUN:
            if (!v->builtin) {
                lenv_del(v->env);
                lval_del(v->formals);
                lval_del(v->body);
            }
            break;
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
    }
    free(v);
}

lval* lval_eval(lenv* e, lval* v)
{
    if (v->type == LVAL_SYM) {
        lval* x = lenv_get(e, v);
        lval_del(v);
        return x;
    }
    if (v->type == LVAL_SEXPR) { return lval_eval_sexpr(e, v); }
    return v;
}

lval *lval_read_num(mpc_ast_t *t)
{
    errno = 0;
    long x = strtol(t->contents, NULL, 10);
    return errno != ERANGE ?
        lval_num(x) : lval_err("invalid number");
}

lval *lval_add(lval *v, lval *x)
{
    v->count++;
    v->cell = realloc(v->cell, sizeof(lval*) * v->count);
    v->cell[v->count-1] = x;
    return v;
}

lval *lval_join(lval *x, lval *y)
{
    while (y->count) {
        x = lval_add(x, lval_pop(y, 0));
    }

    // delete empty y and return x
    lval_del(y);
    return x;
}

lval *lval_read(mpc_ast_t *t)
{
    if (strstr(t->tag, "number")) { return lval_read_num(t); }
    if (strstr(t->tag, "symbol")) { return lval_sym(t->contents); }

    // if root (>) or sexpr then create empty list
    lval *x = NULL;
    if (strcmp(t->tag, ">") == 0) { x = lval_sexpr(); }
    if (strstr(t->tag, "sexpr"))  { x = lval_sexpr(); }
    if (strstr(t->tag, "qexpr"))  { x = lval_qexpr(); }

    // fill this list with any valid expressions
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


void lval_expr_print(lval *v, char open, char close);

void lval_print(lval *v)
{
    switch (v->type) {
        case LVAL_NUM: printf("%li", v->num); break;
        case LVAL_FUN: 
            if (v->builtin) {
                printf("<builtin>");
            } else {
                printf("(\\ "); lval_print(v->formals);
                putchar(' '); lval_print(v->body); putchar(')');
            }
            break;
        case LVAL_ERR: printf("Error: %s", v->err); break;
        case LVAL_SYM: printf("%s", v->sym); break;
        case LVAL_SEXPR: lval_expr_print(v, '(', ')'); break;
        case LVAL_QEXPR: lval_expr_print(v, '{', '}'); break;
    }
}

void lval_expr_print(lval *v, char open, char close)
{
    putchar(open);
    for (int i = 0; i < v->count; i++) {
        // print value contained within
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
    // find the item at "i"
    lval *x = v->cell[i];

    // shift memory after the item at i over the top
    memmove(&v->cell[i], &v->cell[i+1], sizeof(lval*) * (v->count-i-1));

    // decrease the item count
    v->count--;
    // reallocate the memory used
    v->cell = realloc(v->cell, sizeof(lval*) * v->count);

    return x;
}

lval* lval_copy(lval* v)
{
    lval* x = malloc(sizeof(lval));
    x->type = v->type;

    switch (v->type) {
        case LVAL_FUN: 
            if (v->builtin) {
                x->builtin = v->builtin;
            } else {
                x->builtin = NULL;
                x->env = lenv_copy(v->env);
                x->formals = lval_copy(v->formals);
                x->body = lval_copy(v->body);
            }
           break;
        case LVAL_NUM: x->num = v->num; break;

        // copy strings
        case LVAL_ERR:
            x->err = malloc(strlen(v->err)+1);
            strcpy(x->err, v->err); break;

        case LVAL_SYM:
            x->sym = malloc(strlen(v->sym)+1);
            strcpy(x->sym, v->sym); break;

        // copy lists
        case LVAL_SEXPR:
        case LVAL_QEXPR:
            x->count = v->count;
            x->cell = malloc(sizeof(lval*) * x->count);
            for (int i = 0; i < x->count; i++) {
                x->cell[i] =lval_copy(v->cell[i]);
            }
            break;
    }

    return x;
}


// macros
#define LASSERT(args, cond, fmt, ...) \
    if (!(cond)) { \
        lval* err = lval_err(fmt, ##__VA_ARGS__); \
        lval_del(args); \
        return err; \
    }

#define LASSERT_TYPE(func, args, index, expect) \
  LASSERT(args, args->cell[index]->type == expect, \
    "Function '%s' passed incorrect type for argument %i. Got %s, Expected %s.", \
    func, index, ltype_name(args->cell[index]->type), ltype_name(expect))

#define LASSERT_NUM(func, args, num) \
  LASSERT(args, args->count == num, \
    "Function '%s' passed incorrect number of arguments. Got %i, Expected %i.", \
    func, args->count, num)


lval *builtin_op(lenv *e, lval *a, char *op)
{
    // ensure all args are numbers
    for (int i = 0; i < a->count; i++) {
        if (a->cell[i]->type != LVAL_NUM) {
            lval_del(a);
            return lval_err("cannot operate on non-number");
        }
    }

    // pop first element
    lval *x = lval_pop(a, 0);

    // if no args and sub then perform unary negation
    if ((strcmp(op, "-") == 0) && a->count == 0) {
        x->num = -x->num;
    }

    // while there are still remaining elements
    while (a->count > 0) {
        // pop next element
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

lval* builtin_add(lenv *e, lval *a)
{
    return builtin_op(e, a, "+");
}

lval* builtin_sub(lenv *e, lval *a)
{
    return builtin_op(e, a, "-");
}

lval* builtin_mul(lenv *e, lval *a)
{
    return builtin_op(e, a, "*");
}

lval* builtin_div(lenv *e, lval *a)
{
    return builtin_op(e, a, "/");
}

lval* builtin_var(lenv *e, lval *a, char *func)
{
    LASSERT_TYPE(func, a, 0, LVAL_QEXPR);

    // first arg is symbol list
    lval *syms = a->cell[0];

    // ensure all elements of first list are symbols
    for (int i = 0; i < syms->count; i++) {
        LASSERT(a, syms->cell[i]->type == LVAL_SYM, 
            "function '%s' cannot define non-symbol."
            "got %s, expected %s", func,
            ltype_name(syms->cell[i]->type),
            ltype_name(LVAL_SYM));
    }

    // check correct number of symbols and values
    LASSERT(a, syms->count == a->count - 1, 
        "function '%s' passed too many args for syms."
        "got %i, expected %i.", func, syms->count, a->count-1);

    // assign copies of values to symbols
    for (int i = 0; i < syms->count; i++) {
        // if 'def' define it globally, if 'put' define locally
        if (strcmp(func, "def") == 0) {
            lenv_def(e, syms->cell[i], a->cell[i+1]);
        }
        if (strcmp(func, "=") == 0) {
            lenv_put(e, syms->cell[i], a->cell[i+1]);
        }
    }

    lval_del(a);
    return lval_sexpr();
}

lval *builtin_def(lenv *e, lval *a)
{
    return builtin_var(e, a, "def");
}

lval *builtin_put(lenv *e, lval *a)
{
    return builtin_var(e, a, "=");
}

lval *builtin_lambda(lenv *e, lval *a)
{
    // check two args, each of which are Q-exprs
    LASSERT_NUM("\\", a, 2);
    LASSERT_TYPE("\\", a, 0, LVAL_QEXPR);
    LASSERT_TYPE("\\", a, 1, LVAL_QEXPR);

    // check first Q-expr contains only symbols
    for (int i = 0; i < a->cell[0]->count; i++) {
        LASSERT(a, (a->cell[0]->cell[i]->type == LVAL_SYM),
                "cannot define non-symbol, got %s, expected %s.",
                ltype_name(a->cell[0]->cell[0]->type), ltype_name(LVAL_SYM));
    }

    // pop first two args and pass to lval_lambda
    lval *formals = lval_pop(a, 0);
    lval *body = lval_pop(a, 0);
    lval_del(a);

    return lval_lambda(formals, body);
}

#if 0
lval *builtin(lval *a, char *func)
{
    if (strcmp("list", func) == 0) { return builtin_list(a); }
    if (strcmp("head", func) == 0) { return builtin_head(a); }
    if (strcmp("tail", func) == 0) { return builtin_tail(a); }
    if (strcmp("join", func) == 0) { return builtin_join(a); }
    if (strcmp("eval", func) == 0) { return builtin_eval(a); }
    if (strstr("+-*/", func))      { return builtin_op(a, func); }
    lval_del(a);
    return lval_err("unknown function");
}
#endif

void lenv_add_builtin(lenv *e, char *name, lbuiltin func)
{
    lval *k = lval_sym(name);
    lval *v = lval_fun(func);
    lenv_put(e, k, v);
    lval_del(k); lval_del(v);
}

void lenv_add_builtins(lenv *e)
{
    lenv_add_builtin(e, "def", builtin_def);

    lenv_add_builtin(e, "list", builtin_list);
    lenv_add_builtin(e, "head", builtin_head);
    lenv_add_builtin(e, "tail", builtin_tail);
    lenv_add_builtin(e, "eval", builtin_eval);
    lenv_add_builtin(e, "join", builtin_join);

    lenv_add_builtin(e, "+", builtin_add);
    lenv_add_builtin(e, "-", builtin_sub);
    lenv_add_builtin(e, "*", builtin_mul);
    lenv_add_builtin(e, "/", builtin_div);

}

lval *builtin_head(lenv *e, lval *a)
{
    LASSERT(a, a->count == 1, "head pass too many args");
    LASSERT(a, a->cell[0]->type == LVAL_QEXPR, "head incorrect type");
    LASSERT(a, a->cell[0]->count != 0, "head passed {}");

    lval *v = lval_take(a, 0);
    while (v->count > 1) { lval_del(lval_pop(v, 1)); }

    return v;

}

lval *builtin_tail(lenv *e, lval *a)
{
    LASSERT(a, a->count == 1, "tail pass too many args");
    LASSERT(a, a->cell[0]->type == LVAL_QEXPR, "tail incorrect type");
    LASSERT(a, a->cell[0]->count != 0, "tail passed {}");

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
    LASSERT(a, a->count == 1, "eval pass too many args");
    LASSERT(a, a->cell[0]->type == LVAL_QEXPR, "eval incorrect type");

    lval *x = lval_take(a, 0);
    x->type = LVAL_SEXPR;

    return lval_eval(e, x);
}

lval *builtin_join(lenv *e, lval *a)
{
    for (int i = 0; i < a->count; i++) {
        LASSERT(a, a->cell[i]->type == LVAL_QEXPR, "join incorrect type");
    }

    lval *x = lval_pop(a, 0);

    while (a->count) {
        x = lval_join(x, lval_pop(a, 0));
    }

    lval_del(a);
    return x;
}

lval *lval_call(lenv *e, lval *f, lval *a)
{
    // if builtin then simply apply that
    if (f->builtin) { return f->builtin(e, a); }

    // record arg counts
    int given = a->count;
    int total = f->formals->count;

    // while args still remain
    while (a->count) {
        // if we've ran out of formal args to bind
        if (f->formals->count == 0) {
            lval_del(a); return lval_err(
                "function passed to many args."
                "got %i, expected %i.", given, total);
        }

        // pop first symbol
        lval *sym = lval_pop(f->formals, 0);

        // pop next arg from list
        lval *val = lval_pop(a, 0);

        // bind a copy into the function's environment
        lenv_put(f->env, sym, val);

        // delete the symbol and value
        lval_del(sym); lval_del(val);
    }

    // arg list is now bound so can be cleaned up
    lval_del(a);

    // if all formals have been bound, evaluate
    if (f->formals->count == 0) {
        // set the env parent to eval environment
        f->env->par = e;

        // evaluate and return
        return builtin_eval(
            f->env, lval_add(lval_sexpr(), lval_copy(f->body)));
    } else {
        // otherwise return partially evaluated function
        return lval_copy(f);
    }

}

lval *lval_eval_sexpr(lenv* e, lval *v); // fwd decl

lval *lval_take(lval *v, int i)
{
    lval *x = lval_pop(v, i);
    lval_del(v);
    return x;
}

lval *lval_eval_sexpr(lenv* e, lval *v)
{
    // evaluate children
    for (int i = 0; i < v->count; i++) {
        v->cell[i] = lval_eval(e, v->cell[i]);
    }

    // error checking
    for (int i = 0; i < v->count; i++) {
        if (v->cell[i]->type == LVAL_ERR) { return lval_take(v, i); }
    }

    // empty expressions
    if (v->count == 0) { return v; }
    // single expression
    if (v->count == 1) { return lval_take(v, 0); }

    // ensure first element is a function after evaluation
    lval *f = lval_pop(v, 0);
    if (f->type != LVAL_FUN) {
        lval_del(v); lval_del(f);
        return lval_err("first element is not a function");
    }

    // if so, call function to get result
    lval *result = f->builtin(e, v);
    lval_del(f);
    return result;

}

void usage()
{
    printf("usage: \n");
}

int main(int argc, char** argv) {

    puts("Lisp Version 0.0.0.0.1");
    puts("Press Ctrl+c to Exit\n");

    mpc_parser_t* Number    = mpc_new("number");
    mpc_parser_t* Symbol    = mpc_new("symbol");
    mpc_parser_t* Sexpr     = mpc_new("sexpr");
    mpc_parser_t* Qexpr     = mpc_new("qexpr");
    mpc_parser_t* Expr      = mpc_new("expr");
    mpc_parser_t* Lispy     = mpc_new("lispy");

    mpca_lang(MPCA_LANG_DEFAULT,
        "                                                           \
            number      : /-?[0-9]+/ ;                              \
            symbol      : /[a-zA-A0-9_+\\-*\\/\\\\=<>!&]+/ ;        \
            sexpr       : '(' <expr>* ')' ;                         \
            qexpr       : '{' <expr>* '}' ;                         \
            expr        : <number> | <symbol> | <sexpr> | <qexpr> ; \
            lispy       : /^/ <expr>* /$/ ;                         \
        ",
        Number, Symbol, Sexpr, Qexpr, Expr, Lispy);

    lenv *e = lenv_new();
    lenv_add_builtins(e);

    while (1) {

        /* Now in either case readline will be correctly defined */
        char* input = readline("lisp> ");

        add_history(input);

        //printf("%s\n", input);
        if (strcmp(input, "help") == 0) {
            usage();
            continue;
        }

        if (strcmp(input, "quit") == 0) {
            free(input);
            break;
        }

        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r)) {

            lval *x = lval_eval(e, lval_read(r.output));
            lval_println(x);
            lval_del(x);
            //mpc_ast_print(r.output);

            mpc_ast_delete(r.output);
        } else {
            // on error print the error
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);

    }

    lenv_del(e);

    mpc_cleanup(6, Number, Symbol, Sexpr, Qexpr, Expr, Lispy);

    return 0;
}

