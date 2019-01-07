
%{

#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

extern FILE *yyin;
extern int yylex();
extern char *yytext;
extern struct ast *root;

%}

%union {
    struct ast *a;
    double d;
    struct symbol *s;   /* which symbol */
    struct symlist *sl;
    int fn;             /* which function */
}

/* declare tokens */
%token <d>  NUMBER
%token <s>  NAME
%token <fn> FUNC
%token EOL
%token _EOF

%token IF THEN ELSE WHILE DO LET

%nonassoc <fn> CMP
%right '='
%left '+' '-'
%left '*' '/' /* higher precedence than +- */
%nonassoc '|' UMINUS

%type <a>  exp stmt list explist
%type <sl> symlist

%start calclist

%%

stmt    :   IF exp THEN list           { $$ = newflow('I', $2, $4, NULL); }
        |   IF exp THEN list ELSE list { $$ = newflow('I', $2, $4, $6); } 
        |   WHILE exp DO list          { $$ = newflow('W', $2, $4, NULL); } 
        |   exp
        ;

list    :   /* nothing */ { $$ = NULL }
        |   stmt ';' list { if ($3 == NULL) $$ = $1;
                            else $$ = newast('L', $1, $3);
                          }
        ;

exp     :   exp CMP exp             { $$ = newcmp($2, $1, $3); }
        |   exp '+' exp             { $$ = newast('+', $1, $3); }
        |   exp '-' exp             { $$ = newast('-', $1, $3); }
        |   exp '*' exp             { $$ = newast('*', $1, $3); }
        |   exp '/' exp             { $$ = newast('/', $1, $3); }
        |   '|' exp                 { $$ = newast('|', $2, NULL); }
        |   '(' exp ')'             { $$ = $2; }
        |   '-' exp %prec UMINUS    { $$ = newast('M', $2, NULL); }
        |   NUMBER                  { $$ = newnum($1); }
        |   NAME                    { $$ = newref($1); }
        |   NAME '=' exp            { $$ = newasgn($1, $3); }
        |   FUNC '(' explist ')'    { $$ = newfunc($1, $3); }
        |   NAME '(' explist ')'    { $$ = newcall($1, $3); }
        ;

explist : exp
        | exp ',' explist           { $$ = newast('L', $1, $3); }
        ;

symlist : NAME                      { $$ = newsymlist($1, NULL); }
        | NAME ',' symlist          { $$ = newsymlist($1, $3); } 
        ;

calclist:   /* nothing */
//      |   calclist stmt EOL {
        |   calclist list EOL {
                if (root == NULL) root = $2;
                else if (root->nodetype != 'L') {
                    root = newast('L', root, $2);
                } else {
                    struct ast *tmp = root;
                    struct ast *prev_tmp = NULL;
                    while (tmp->nodetype == 'L') {
                        prev_tmp = tmp;
                        tmp = tmp->r;
                    }
                    prev_tmp->r = newast('L', tmp, $2);
                }
                //printf("=%4.4g\n", eval($2));
                //treefree($2);
                if (yyin == stdin) {
                    printf("> ");
                }
            }
        |   calclist LET NAME '(' symlist ')' '=' list EOL { 
                dodef($3, $5, $8);
                printf("defined %s\n> ", $3->name); }
        |   calclist error EOL { yyerrok; if (yyin == stdin) { printf("> "); } }
        |   calclist _EOF      { return 0; }
        ;

%%




