%{
#include <cstdio>
#include <iostream>
using namespace std;

extern int linenum;

// declare stuff from Flex that Bison needs to know about:
extern int yylex();
extern int yyparse();
extern FILE *yyin;

void yyerror(const char *s);
%}

// tokens can be variant types so use a union
%union {
    int ival;
    float fval;
    char *sval;
}

// define constant-string tokens
%token SNAZZLE TYPE
%token END ENDL

// define the terminal symbol token types
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING

%%
// define the grammar
snazzle:
        header template body_section footer { printf("file done\n"); }
        ;
header:
        SNAZZLE FLOAT ENDLS { printf("ver: %f\n", $2); }
        ;
template:
        typelines
        ;
typelines:
        typelines typeline
        | typeline
        ;
typeline:
        TYPE STRING ENDLS { printf("new type: %s\n", $2); }
body_section:
        body_lines
        ;
body_lines:
        body_lines body_line
        | body_line
        ;
body_line:
        INT INT INT INT STRING ENDLS { printf("new snz: %d %d %d %d %s\n", $1, $2, $3, $4, $5); }
        ;
footer:
        END ENDLS
        ;

ENDLS:
        ENDLS ENDL
        | ENDL
        ;

%%


int main(int argc, char *argv[]) {
    // lex through the input:
    FILE *myfile;
    yyin = stdin;
    if (argc > 1) {
        myfile = fopen(argv[1], "r");
        yyin = myfile;
    }
    yyparse();
    cout << linenum << endl;
}

void yyerror(const char *s)
{
    printf("parse error: %s line: %d\n", s, linenum);
    exit(-1);
}

