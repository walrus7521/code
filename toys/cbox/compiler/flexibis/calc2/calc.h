#ifndef _CALC_H_
#define _CALC_H_

// interface to lexer
extern int yylineno;
void yyerror(char *s, ...);

// AST nodes
struct ast {
    int nodetype;
    struct ast *l;
    struct ast *r;
};

struct numval {
    int nodetype;
    double number;
};

struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newnum(double d);
double eval(struct ast *);
void treefree(struct ast *);


#endif // _CALC_H_
