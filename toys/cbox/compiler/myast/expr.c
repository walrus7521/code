#include "expr.h"
#include "stack.h"
#include "tree.h"
#include "lexer.h"

exprnode *allocate_constexpr(int value)
{
    exprnode *p_expr = (exprnode *) malloc(sizeof(exprnode));
    if (p_expr != NULL) {
        TYPE(p_expr) = CONSTANT;
        CON_VALUE(p_expr) = value;
    }
    return p_expr;
}

exprnode *allocate_symbolexpr(char value)
{
    exprnode *p_expr = (exprnode *) malloc(sizeof(exprnode));
    if (p_expr != NULL) {
        TYPE(p_expr) = VARIABLE;
        SYM_VALUE(p_expr) = value;
    }
    return p_expr;
}

exprnode *allocate_operatorexpr(Operator value)
{
    exprnode *p_expr = (exprnode *) malloc(sizeof(exprnode));
    if (p_expr != NULL) {
        TYPE(p_expr) = OPERATOR;
        OP_VALUE(p_expr) = value;
    }
    return p_expr;
}

status read_expr(tree *p_T)
{
    stack S;
    tree tmptree, rightchild, leftchild;
    exprnode *p_expr;
    status rc;
    tokendata *p_token;

    init_stack(&S);

    while (true) {
        p_token = gettoken();
        switch (p_token->tokentype) {
            case EOL_T:
                //printf("expr: EOL\n");
                rc = pop_tree(&S, p_T);
                ERROR_CHECK(rc);
                return OK;

            case CONSTANT_T:
            case VARIABLE_T:
                //printf("expr: CONST/VAR\n");
                if (p_token->tokentype == CONSTANT_T) {
                    char buffer[2];
                    buffer[0] = (char) p_token->tokenvalue;
                    buffer[1] = '\0';
                    p_expr = allocate_constexpr(atoi(buffer));
                } else {
                    p_expr = allocate_symbolexpr(p_token->tokenvalue);
                }
                if (p_expr == NULL) {
                    return ERROR;
                }
                rc = init_tree(&tmptree);
                ERROR_CHECK(rc);
                rc = make_root(&tmptree, (void *) p_expr, NULL, NULL);
                ERROR_CHECK(rc);
                rc = push_tree(&S, tmptree);
                ERROR_CHECK(rc);
                break;

            case OPERATOR_T:
                //printf("expr: OPERATOR\n");
                switch (p_token->tokenvalue) {
                    case '+': p_expr = allocate_operatorexpr(PLUS); break;
                    case '-': p_expr = allocate_operatorexpr(MINUS); break;
                    case '*': p_expr = allocate_operatorexpr(TIMES); break;
                    case '/': p_expr = allocate_operatorexpr(DIVIDE); break;
                    default: return ERROR;
                }
                if (p_expr == NULL) {
                    return ERROR;
                }
                rc = pop_tree(&S, &rightchild);
                ERROR_CHECK(rc);
                rc = pop_tree(&S, &leftchild);
                ERROR_CHECK(rc);
                rc = init_tree(&tmptree);
                ERROR_CHECK(rc);
                rc = make_root(&tmptree, (void *) p_expr, leftchild, rightchild);
                ERROR_CHECK(rc);
                rc = push_tree(&S, tmptree);
                ERROR_CHECK(rc);
                break;

            default:
                return ERROR;
        }
    }
    // can't get here
    return OK;
}

status print_exprnode(exprnode *p_expr)
{
    char c;
    switch (TYPE(p_expr)) {
        case OPERATOR:
            switch (OP_VALUE(p_expr)) {
                case PLUS:   c = '+'; break;
                case MINUS:  c = '-'; break; 
                case TIMES:  c = '*'; break; 
                case DIVIDE: c = '/'; break; 
            }
            printf("%c ", c);
            break;
        case CONSTANT:
            printf("%d ", CON_VALUE(p_expr));
            break;
        case VARIABLE:
            printf("%c ", SYM_VALUE(p_expr));
            break;
    }
    return OK;
}

status eval_expr(tree T, symbol_table symtab, int *p_value)
{
    return OK;
}

status print_expr(tree T)
{
    traverse_tree(T, print_exprnode, POSTORDER);
    putchar('\n');
    return OK;
}


