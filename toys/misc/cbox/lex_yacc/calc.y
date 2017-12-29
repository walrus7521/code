/* calc.y - a four function calculator */
%{
#define YYSTYPE double      /* yyparse() stack type */
#include <stdlib.h>
%}
/* BISON Declarations */
%token NEWLINE NUMBER PLUS MINUS SLASH ASTERISK LPAREN RPAREN

/* Grammar follows */
%%
input:              /* empty string */
    | input line
    ;
line: NEWLINE
    | expr NEWLINE           { printf("\t%.10g\n",$1); }
    ;
expr: expr PLUS term         { $$ = $1 + $3; }
    | expr MINUS term        { $$ = $1 - $3; }
    | term
    ;
term: term ASTERISK factor   { $$ = $1 * $3; }
    | term SLASH factor      { $$ = $1 / $3; }
    | factor
    ;
factor:  LPAREN expr RPAREN  { $$ = $2; }
      | NUMBER
      ;
%%
/*--------------------------------------------------------*/
/* Additional C code */
/* Error processor for yyparse */
#include <stdio.h>
int yyerror(char *s)        /* called by yyparse on error */
{
    printf("%s\n",s);
    return(0);
}

/*--------------------------------------------------------*/
/* The controlling function */
int main(void)
{
    yyparse();
    exit(0);
}

