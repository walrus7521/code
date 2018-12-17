grammar PUMA;

puma    : MODE scenario_list;

scenario_list
        : ( scenario )*
        ;

scenario: 'SCENARIO' '(' scenario_params ')' stmt_list 'END' ;

stmt_list
        :   ( stmt )* 
        ;

stmt    :   activate
        |   associate
        |   sparse
        |   wait_on
        |   if_op
        |   log
        ;

activate:   'ACTIVATE' '(' NUM ')' ;

associate
        :   'ASSOCIATE' '(' NUM ',' NUM ')'
        |   'UNASSOCIATE' '(' NUM ',' NUM ')'
        ;

sparse  :   'SEND_SPARSE' '(' sparse_params ')'
        |   'RING_SPARSE' '(' ring_params ')'
        ;

wait_on :   'WAIT_ON_SIGNAL' '(' NUM ',' NUM ')' ;

log     :   'LOG' '(' ID ',' ('Y'|'N') ',' NUM ',' NUM ')' ;

if_op   :   'IF' '(' expr_list ')' ;

expr_list
        :   ( expr )*
        ;

expr    :   (ID)+ ;

scenario_params
        :   NUM ',' ID ',' NUM
        ;

sparse_params
        :   NUM ',' ('IN'|'OUT') ',' NUM ',' NUM ',' NUM ',' ('NCQ'|'NONNCQ') ',' NUM ',' NUM ',' NUM ',' ('Y'|'N')
        ;

ring_params
        :   NUM ',' NUM ',' ('NCQ'|'NONNCQ') ',' ('SAFE'|'UNSAFE')
        ;


MODE    : 'TRANSPORT_MODE' '(' MODE_ID ')' ;
MODE_ID :   ('AHCI'|'NVME') ;
NUM     :   [0-9]+ ;
ID  :   LETTER (LETTER | [0-9])* ;

fragment
LETTER : [a-zA-Z_=] ;

WS  :   [ \t\n\r]+ -> skip ;

SL_COMMENT
    :   '//' .*? '\n' -> skip
    ;

NL      :   '\r'? '\n' -> skip ;

