grammar Structs1 ;

typeDecl : 'typedef struct' '{' (fields)+ '}' typeName ';' ;

fields : field (',' field)* ';' ;
field  : fieldType fieldName ;

fieldType : ID ;
fieldName : ID ;
typeName  : ID ;

ID : [a-zA-Z0-9]+ ;
WS : [ \t\n\r]+ -> skip ;
Comment1 : '//' ~[\r\n]* -> skip ;
Comment2 : '#' ~[\r\n]* -> skip ;
INVALID4 : . -> skip ;

