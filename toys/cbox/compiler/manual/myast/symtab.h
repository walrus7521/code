#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include "common.h"

typedef struct symbol_table {
    int A, B, C;
} symbol_table;

void set_symbol(symbol_table *p_symtab, char sym, int value);
int get_symbol(symbol_table symtab, char sym);
status read_symbols(symbol_table *p_symtab,int A, int B, int C);

#endif // _SYMTAB_H_
