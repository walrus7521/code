#ifndef _SYMTAB_H_
#define _SYMTAB_H_

typedef struct symbol_table {
    int A, B, C;
} symbol_table;

void set_symbol(symbol_table *p_symtab, char sym, int value);
int get_symbol(symbol_table symtab, char sym);

#endif // _SYMTAB_H_
