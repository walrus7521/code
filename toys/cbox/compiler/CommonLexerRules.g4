lexer grammar CommonLexerRules;

ID      :   [a-zA-Z]+ ;
INT     :   [0-9]+ ;
NEWLINE :   '\r'? '\n' | '\r';
WS      :   [ \t]+ -> skip ;

MUL : '*' ;
DIV : '/' ;
ADD : '+' ;
SUB : '-' ;

