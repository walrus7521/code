#include <stdio.h>
#include "straight.h"

A_stm A_CompoundStm(A_stm stm1, A_stm stm2)
{
    return NULL;
}

A_stm A_AssignStm(string id, A_exp exp)
{
    return NULL;
}

A_stm A_PrintStm(A_expList exps)
{
    return NULL;
}

A_exp A_IdExp(string id)
{
    return NULL;
}

A_exp A_NumExp(int num)
{
    return NULL;
}

A_exp A_OpExp(A_exp left, A_binop oper, A_exp right)
{
    return NULL;
}

A_exp A_EseqExp(A_stm stm, A_exp exp)
{
    return NULL;
}

A_expList A_PairExpList(A_exp head, A_expList tail)
{
    return NULL;
}

A_expList A_LastExpList(A_exp last)
{
    return NULL;
}


