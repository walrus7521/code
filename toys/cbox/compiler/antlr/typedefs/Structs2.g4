grammar Structs ;

typeDecl : 'typedef struct' '{' (fields)+ '}' typeName ';' ;
typeName : ID ;
fields : fieldType fieldName ';' ;
fieldType : ID ;
fieldName : ID ;

ID : [a-zA-Z0-9]+ ;
WS : [ \t\n\r]+ -> skip ;
Comment1 : '//' ~[\r\n]* -> skip ;
Comment2 : '#' ~[\r\n]* -> skip ;
INVALID4 : . -> skip ;

