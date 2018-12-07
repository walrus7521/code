#include <stdio.h>
#include <stdlib.h>
#include "../common/util.h"
#include "straight.h"

A_stm A_CompoundStm(A_stm stm1, A_stm stm2)
{
    A_stm s = checked_malloc(sizeof *s);
    return s;
}

A_stm A_AssignStm(string id, A_exp exp)
{
    A_stm s = checked_malloc(sizeof *s);
    return s;
}

A_stm A_PrintStm(A_expList exps)
{
    A_stm s = checked_malloc(sizeof *s);
    return s;
}

A_exp A_IdExp(string id)
{
    A_exp e = checked_malloc(sizeof *e);    
    return e;
}

A_exp A_NumExp(int num)
{
    A_exp e = checked_malloc(sizeof *e);    
    return e;
}

A_exp A_OpExp(A_exp left, A_binop oper, A_exp right)
{
    A_exp e = checked_malloc(sizeof *e);    
    return e;
}

A_exp A_EseqExp(A_stm stm, A_exp exp)
{
    A_exp e = checked_malloc(sizeof *e);    
    return e;
}

A_expList A_PairExpList(A_exp head, A_expList tail)
{
    A_expList e = checked_malloc(sizeof *e);
    return e;
}

A_expList A_LastExpList(A_exp last)
{
    A_expList e = checked_malloc(sizeof *e);
    return e;
}


