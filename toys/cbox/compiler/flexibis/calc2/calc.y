
%{

#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

%}

%union {
    struct ast *a;
    double d;
}

%token <d> NUMBER
%token EOL

%left '+' '-'
%left '*' '/' /* higher precedence than +- */
%nonassoc '|' UMINUS

%type <a> exp

%%

calclist:   /* nothing */
        |   calclist exp EOL {
                printf("=%4.4g\n", eval($2));
                treefree($2);
                printf("> ");
            }
        |   calclist EOL { printf("> "); } /* blank line or comment */
        ;

exp     :   exp '+' exp { $$ = newast('+', $1, $3); }
        |   exp '-' exp { $$ = newast('-', $1, $3); }
        |   exp '*' exp { $$ = newast('*', $1, $3); }
        |   exp '/' exp { $$ = newast('/', $1, $3); }
        |   '|' exp     { $$ = newast('|', $2, NULL); }
        |   '(' exp ')' { $$ = $2; }
        |   '-' exp %prec UMINUS { $$ = newast('M', NULL, $2); }
        |   NUMBER { $$ = newnum($1); }
        ;

%%




