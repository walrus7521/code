#ifndef _EXPR_H_
#define _EXPR_H_

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



#endif // _EXPR_H_
