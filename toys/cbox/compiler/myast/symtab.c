#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "symtab.h"

void set_symbol(symbol_table *p_symtab, char sym, int value)
{
    switch (sym) {
        case 'A': p_symtab->A = value; break;
        case 'B': p_symtab->B = value; break;
        case 'C': p_symtab->C = value; break;
        default: break;
    }
}

int get_symbol(symbol_table symtab, char sym)
{
    int value = -1;
    switch (sym) {
        case 'A': value = symtab.A; break;
        case 'B': value = symtab.B; break;
        case 'C': value = symtab.C; break;
        default: break;
    }
    return value;
}

status read_symbols(symbol_table *p_symtab,int A, int B, int C)
{
    // get symbols for user input
    p_symtab->A = A;
    p_symtab->B = B;
    p_symtab->C = C;
    return OK;
}

