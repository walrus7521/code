%{
#include <cstdio>
#include <iostream>
using namespace std;

extern int linenum;
int read = 0;
int write = 0;
int queue[8];
char *save_string = NULL;
void put(int x) { queue[write++] = x; }
int get() { return queue[read++]; }

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
%token PUMA TYPE MODE
%token LPAREN RPAREN END ENDL COMMA
%token ACTIVATE ASSOCIATE UNASSOCIATE WAIT_ON_SIGNAL LOG

// define the terminal symbol token types
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING

%%
// define the grammar
puma:
        header mode template body_section footer { printf("file done\n"); }
        ;
header:
        PUMA FLOAT ENDLS { printf("ver: %f\n", $2); }
        ;

mode:
        MODE LPAREN STRING RPAREN ENDLS { printf("mode: %s\n", $3); }
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
        ;

body_section:
        body_lines
        ;
       
body_lines:
        body_lines body_line
        | body_line
        ;

body_line:
        dude
        | associate
        | unassociate
        | activate
        | wait_on_signal
        | log
        ;

associate:
        ASSOCIATE LPAREN exps RPAREN ENDLS { printf("assoc: %d %d\n", get(), get()); }
        ;

unassociate:
        UNASSOCIATE LPAREN exps RPAREN ENDLS { printf("unassoc: %d %d\n", get(), get()); }
        ;

wait_on_signal:
        WAIT_ON_SIGNAL LPAREN exps RPAREN ENDLS { printf("wait: %d %d\n", get(), get()); }
        ;

activate:
        ACTIVATE LPAREN exps RPAREN ENDLS { printf("act: %d\n", get()); }
        ;

log:
        LOG LPAREN exps RPAREN ENDLS { printf("log: %d %d %d\n", get(), get(), get()); }
        ;

dude:   INT INT INT INT STRING ENDLS { printf("dude: %d %d %d %d %s\n", $1, $2, $3, $4, $5); }
        ;

exps: 
        exp
        | exp COMMA exps
        ;

exp:
        INT                 { put($1); /*printf("%d\n", $1);*/ }
        | STRING            { save_string = strdup($1); printf("st: %s\n", save_string); }
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

