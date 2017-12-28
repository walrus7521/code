%{
// http://aquamentus.com/flex_bison.html
#include <iostream>
using namespace std;
#define YY_DECL extern "C" int yylex()
%}
%{
    int linenum = 0;
%}
%%
[ \t]           ;
[ \n]           { linenum++; }
[0-9]+\.[0-9]+  { cout << linenum << "] " << "Found a floating-point number:" << yytext << endl; }
[0-9]+          { cout << linenum << "] " << "Found an integer:" << yytext << endl; }
[a-zA-Z0-9]+    { cout << linenum << "] " << "Found a string: " << yytext << endl; }
%%
int main(int, char**) {
	// lex through the input:
	yylex();
}

