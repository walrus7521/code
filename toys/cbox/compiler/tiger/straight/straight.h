#ifndef _STRAIGHT_H_
#define _STRAIGHT_H_

typedef char *string;
typedef struct A_stm_ *A_stm;
typedef struct A_exp_ *A_exp;
typedef struct A_expList_ *A_expList;
typedef enum {A_plus, A_minus, A_times, A_div} A_binop;

typedef struct A_stm_ {
    enum {A_compoundStm, A_assignStm, A_printStm} kind;
    union {
        struct {A_stm stm1, stm2;} compound;
        struct {string id; A_exp exp;} assign;
        struct {A_expList exps;} print;
    } u;
};

A_stm A_CompoundStm(A_stm stm1, A_stm stm2);
A_stm A_AssignStm(string id, A_exp exp);
A_stm A_PrintStm(A_expList exps);



#endif // _STRAIGHT_H_
