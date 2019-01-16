grammar Astrec ;

start       : (decl)*  EOF ;

decl        : typeDecl (fieldDecl)+ attribDecl ;

typeDecl    : NUM '|' fieldType ;
fieldDecl   : NUM '|' fieldType fieldName ;
attribDecl  : '|' '[' attribs ']' ;



fieldType   : ID ;
fieldName   : ID ;
attribs     : ID '=' NUM (',' ID '=' NUM)* ;



NUM     : [0-9]+ ;
ID      : [a-zA-Z]+[a-zA-Z0-9_]* ;
NL      : '\r'? '\n' ;
WS      : [ \t\r\n]+ -> skip ;
COMMENT : '*' ~[\r\n]* -> skip ;
INVALID : . -> skip ;

