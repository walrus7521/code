#include <stdio.h>
#include "clist.h"

//#define E_EXIT      (-1)
#define E_EOF       (1)
#define E_SPACE     (2)
#define E_SYNTAX    (3)
#define E_EVAL      (4)
#define E_EXIT      (5)

#if 0
    clist *head = clist_create(SENTINEL);
    int i;
    for (i = 0; i < 8; i++) {
        clist_insert(head, (void *) i);
    }
    clist_dump(head);
#endif

typedef enum {LIST, ATOM} lisp_type;
typedef clist lisp_list;
typedef char *lisp_atom;

typedef struct lisp_node {
    lisp_type type;
    union {
        lisp_list list;
        lisp_atom atom;
    } value;
} lisp_node, *lisp_expression;

typedef int (*p_func_f)(lisp_expression expression);

#define LISP_TYPE(x)  (((lisp_expression) x)->type)
#define ATOM_VALUE(x) (((lisp_expression) x)->value.atom)
#define LIST_VALUE(x) (((lisp_expression) x)->value.list)

#define T_VALUE     "T"
#define NIL_VALUE   "NIL"
#define QUOTE_VALUE "QUOTE"

void printerror(int errnum);
int read_expression(lisp_expression *p_expression);
int eval_expression(lisp_expression p_expression, lisp_expression *p_value);
int print_expression(lisp_expression expression);
int circ_traverse(lisp_list L, p_func_f);

int main()
{
    lisp_expression expression, value;
    int rc;

    do {
        printf("lisp: ");
        rc = read_expression(&expression);
        if (rc) {
            printerror(rc);
            continue;
        }
        rc = eval_expression(expression, &value);
        if (rc != E_EXIT) {
            if (rc) {
                printerror(rc);
                continue;
            }
            print_expression(value);
            printf("\n");
        }

    } while (rc != E_EXIT);
    printf("normal termination\n");
}

void printerror(int errnum)
{
#define MAXERROR (4)
    static char *errmsg[] = {
        "unexpected end of file",
        "out of memory",
        "syntax error",
        "error evaluating expression"
    };
    if (errnum < 0 || errnum > MAXERROR) {
        printf("system error: invalid errnum %d\n", errnum);
        return;
    }
    printf("%s\n", errmsg[errnum-1]);
}

int read_expression(lisp_expression *p_expression)
{
    return 0;
}

int eval_expression(lisp_expression p_expression, lisp_expression *p_value)
{
    return 0;
}

int print_expression(lisp_expression expression)
{
    if (LISP_TYPE(expression) == ATOM) {
        printf("%s ", ATOM_VALUE(expression));
    } else {
        printf("(");
        circ_traverse(LIST_VALUE(expression), print_expression);
        printf(")");
    }
    return 0;
}

int circ_traverse(lisp_list L, p_func_f f)
{
    return 0;
}

