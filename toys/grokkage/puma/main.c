#include "util.h"
#include "puma.h"

int maxargs(A_stm stm)
{
    return 0;
}

void interp(A_stm stm)
{
    switch (stm->kind)
    {
        case A_compoundStm:
            interp(stm->u.compound.stm1);
            interp(stm->u.compound.stm2);
            break;
        case A_assignStm:
            printf("assign: %s ", stm->u.assign.id);
            printf("exp: %d\n", stm->u.assign.exp->kind);
            break;
        case A_printStm:
            printf("exps: %d\n", stm->u.print.exps->kind);
            break;
    }
}



int main()
{
    A_stm prog = 
        A_CompoundStm( A_AssignStm("a", 
                    A_OpExp(A_NumExp(5), A_plus, A_NumExp(3))),
            A_CompoundStm(A_AssignStm("b",
                A_EseqExp(A_PrintStm(A_PairExpList(A_IdExp("a"),
                    A_LastExpList(A_OpExp(A_IdExp("a"), A_minus,
                                    A_NumExp(1))))),
                            A_OpExp(A_NumExp(10), A_times, A_IdExp("a")))),
                    A_PrintStm(A_LastExpList(A_IdExp("b"))))); 

    interp(prog);
}

