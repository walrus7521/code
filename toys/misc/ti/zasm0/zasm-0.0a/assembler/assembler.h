/***********************************************************************************\
 * Copyright (C) 2004 Steven Deprez                                                *
 *                                                                                 *
 * This file is part of zasm                                                       *
 *                                                                                 *
 * zasm is free software; you can redistribute it and/or modify                    *
 * it under the terms of the GNU General Public License as published by            *
 * the Free Software Foundation; either version 2 of the License, or               *
 * (at your option) any later version.                                             *
 *                                                                                 *
 * This program is distributed in the hope that it will be useful,                 *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                  *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                   *
 * GNU General Public License for more details.                                    *
 *                                                                                 *
 * You should have received a copy of the GNU General Public License               *
 * along with this program; if not, write to the Free Software                     *
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.     *
 *                                                                                 *
 * In addition, as a special exception, Peter-Martijn Kuipers gives permission     *
 * to link the code of this program with the appsign library, and distribute       *
 * linked combinations including the two. If you modify this file, you may extend  *
 * this exception to your version of the file, but you are not obligated to do so. *
 * If you do not wish to do so, delete this exception statement form your version. *
\***********************************************************************************/

#ifndef ASSEMBLER_H
#define ASSEMBLER_H 1

#ifdef STDC_HEADERS
#include <stdio.h>
#endif

#define INT_HEX(X) (((X)<10)?((X)+'0'):((X)-10+'A'))
#define chr_upcase(C) ((((C)>='a')&&((C)<='z'))?C-'a'+'A':C)
#define chr_case_eq(C1,C2) ((chr_upcase(C1)==chr_upcase(C2))?1:0)
#define DECIMAL(C) (((C)>='0')&&((C)<='9'))
#define LOWER_HEX(C) (((C)>='a')&&((C)<='f'))
#define UPPER_HEX(C) (((C)>='A')&&((C)<='F'))
#define hex_char(H) ((DECIMAL(H))?((H)-'0'):((LOWER_HEX(H))?((H)-'a'+10):((UPPER_HEX(H))?((H)-'A'+10):0)))
#define hex_byte(H1,H2) ((hex_char(H1)*16)+hex_char(H2))

//#define DEBUG(format, args...) {fprintf(stderr, format, ## args);}
#define DEBUG(format, args...) 

#define ERROR(format, args...) {fprintf(stderr, "in file \"%s\" at line %i: ", pos_file, pos_line);\
                                fprintf(stderr, format, ## args);}

struct opcode_t
{
  struct opcode_t *next;
  int type;                   // argument class
  char size;                  // size of compiled opcode
  char *code;                 // compiled opcode (hex)
  char *arg1;                 // expr for first non-register argument 
  char *arg2;                 // expr for second non-register argument
  unsigned short int address; // address of the first byte of this opcode 
  char *pos_file;
  int pos_line;
};

struct new_page_t
{
  struct new_page_t *next;
  int type; // always Z80_TYPE_NEW_PAGE
  char page;
};

struct label_t
{
  struct label_t *next;
  char *name;                 // name of the label
  unsigned short int address; // address in code where the label is found
  unsigned char page;
};

struct opcode_table_t{
  char *name;
  char *arg1;
  char *arg2;
  int size;
  char *code;
  int type;
};

enum{
  Z80_OPCODES_TYPE_NOP = 0,
  Z80_OPCODES_TYPE_WORD,
  Z80_OPCODES_TYPE_BYTE,
  Z80_OPCODES_TYPE_REL,
  Z80_OPCODES_TYPE_COMBINE,
  Z80_OPCODES_TYPE_COUNT
};

#define Z80_TYPE_NEW_PAGE Z80_OPCODES_TYPE_COUNT

//intel_hex.c
int intel_hex_end(FILE *dest);
int intel_hex_page(FILE *dest, char page);
int intel_hex_write(FILE *dest, char *data, int dest_addr);
// label.c
struct label_t *make_label(char *name, unsigned short int address, char page); // ToDo: add page support
struct label_t *resolve_label(char *name);
// string.c
int eval_expr(char *expr, int addr);
char *str_cpy_alloc(char *str);
char *fgetline(FILE *stream);
// opcode.c
struct opcode_t *make_opcode(char size, char *code, int type, char *arg1, char *arg2, unsigned short int addr);
struct new_page_t *make_new_page(char page);
// pattern.c
int patcasetest(char *str, char *pat);
char *patcasecapture(char *str, char *pat);
// z80.c
#ifndef Z80_C
extern struct opcode_table_t z80_opcodes[];
extern char *(*z80_types_functions[Z80_OPCODES_TYPE_COUNT])(struct opcode_t *opcode, int arg1, int arg2);
#endif
struct opcode_t *z80_asm_opcode(char *inst, unsigned short int addr);
// assembler.c
#ifndef ASSEMBLER_C
extern struct opcode_t *opcodes;
extern struct label_t *symtable;
extern char *pos_file;
extern int pos_line;
#endif
int pass1(FILE *infile);
int pass2(FILE *destfile);
int main(int argc, char *argv[]);
#endif
