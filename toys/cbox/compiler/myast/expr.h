#ifndef _EXPR_H_
#define _EXPR_H_

#include "common.h"
#include "tree.h"
#include "symtab.h"


typedef enum { OPERATOR, CONSTANT, VARIABLE } NodeType;
typedef enum { PLUS, MINUS, TIME, DIVIDE } Operator;
typedef struct exprnode {
    NodeType nodetype;
    union {
        Operator optype;
        char symbolname;
        int constvalue;
    } nodevalue;
} exprnode;

#define TYPE(n)      ((n)->nodetype)
#define OP_VALUE(n)  ((n)->nodevalue.optype)
#define SYM_VALUE(n) ((n)->nodevalue.symbolname)
#define CON_VALUE(n) ((n)->nodevalue.constvalue)

status read_expr(tree *p_T);
status eval_expr(tree T, symbol_table symtab, int *p_value);
status print_expr(tree T);


#endif // _EXPR_H_
