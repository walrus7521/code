/* this is only for scanner, not link with parser yet */
%{
int lineNum = 0;
%}
%%
"(" { printf("(\n"); }
")" { printf(")\n"); }
"+" { printf("+\n"); }
"*" { printf("*\n"); }
\n { lineNum++; }
[ \t]+ { }
[0-9]+ { printf("%s\n", yytext); }
%%
int yywrap() {
 return 1;
}
int main () {
 yylex();
 return 0;
}

