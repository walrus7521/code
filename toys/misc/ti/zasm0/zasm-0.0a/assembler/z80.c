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

#define Z80_C 1
#include <config.h>

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif
#include "assembler.h"

#include "z80.opcodes"

// translate an opcode
struct opcode_t *z80_asm_opcode(char *inst, unsigned short int addr)
{
  char *name = NULL, *arg1 = NULL, *arg2 = NULL;
  int i;

  name = inst;
  for (i = 0; inst[i]; i++)
    if (inst[i] == ' ')
      {inst[i] = 0;arg1 = inst+i+1;}
    else if (inst[i] == ',')
      {inst[i] = 0;arg2 = inst+i+1;}
  
  for (i = 0; z80_opcodes[i].name; i++)
    {
      if ((strcasecmp(name,z80_opcodes[i].name) == 0) && 
	  patcasetest(arg1,z80_opcodes[i].arg1) && 
	  patcasetest(arg2,z80_opcodes[i].arg2))
	{
	  /*	  DEBUG("z80_asm_opcode:\n  '%s' == '%s'\n  '%s' =~ '%s'\n  '%s' =~ '%s'\n", 
		name, z80_opcodes[i].name,
		arg1, z80_opcodes[i].arg1,
		arg2, z80_opcodes[i].arg2);*/
	  switch (z80_opcodes[i].type)
	    {
	    case Z80_OPCODES_TYPE_NOP: // no operands
	      return make_opcode(z80_opcodes[i].size, z80_opcodes[i].code, z80_opcodes[i].type, NULL, NULL, addr);
	    case Z80_OPCODES_TYPE_COMBINE: // two operands
	      arg1 = patcasecapture(arg1, z80_opcodes[i].arg1);
	      arg2 = patcasecapture(arg2, z80_opcodes[i].arg2);
	      return make_opcode(z80_opcodes[i].size, z80_opcodes[i].code, z80_opcodes[i].type, arg1, arg2, addr);
	    default:
	      // one operand
	      if (strchr(z80_opcodes[i].arg1, '*'))
		arg1 = patcasecapture(arg1, z80_opcodes[i].arg1);
	      else
		arg1 = patcasecapture(arg2, z80_opcodes[i].arg2);
		return make_opcode(z80_opcodes[i].size, z80_opcodes[i].code, z80_opcodes[i].type, arg1, NULL, addr);
	    }
	}
    }
  ERROR("nonexistant instruction: \"%s %s,%s\"\n", name, arg1, arg2);
  return NULL;
}

// functions to assemble each type op opcode
static char *type_nop(struct opcode_t *opcode, int arg1, int arg2){return opcode->code;}
static char *type_word(struct opcode_t *opcode, int arg1, int arg2)
{
  int i;
  char *code = opcode->code;

  if ((arg1 > 65535) || (arg1 < -32768))
    ERROR("argument out of range: %i\n", arg1);

  for (i = 0; code[i]; i++)
    if ((i%2 == 0) && (code[i] == '0') && (code[i+1] == '0') && (code[i+2] == '0') && (code[i+3] == '0'))
      {
	code[i+1] = INT_HEX(arg1 & 0x0f); arg1 >>= 4;
	code[i]   = INT_HEX(arg1 & 0x0f); arg1 >>= 4;
	code[i+3] = INT_HEX(arg1 & 0x0f); arg1 >>= 4;
	code[i+2] = INT_HEX(arg1 & 0x0f);
	break;
      }
  return code;
}
static char *type_byte(struct opcode_t *opcode, int arg1, int arg2)
{
  int i;
  char *code = opcode->code;
  
  if ((arg1 > 255) || (arg1 < -128))
    ERROR("argument out of range: %i\n", arg1);

  for (i = 0; code[i]; i++)
    if ((i%2 == 0) && (code[i] == '0') && (code[i+1] == '0'))
      {
	code[i+1] = INT_HEX(arg1 & 0x0f); arg1 >>= 4;
	code[i]   = INT_HEX(arg1 & 0x0f);
	break;
      }
  return code;
}
static char *type_combine(struct opcode_t *opcode, int arg1, int arg2)
{opcode->code = type_byte(opcode, arg1, 0);return type_byte(opcode, arg2, 0);}
static char *type_rel(struct opcode_t *opcode, int arg1, int arg2)
{return type_byte(opcode, arg1 - opcode->address - 2, 0);}

char *(*z80_types_functions[Z80_OPCODES_TYPE_COUNT])(struct opcode_t *opcode, int arg1, int arg2) = 
{
  type_nop,
  type_word,
  type_byte,
  type_rel,
  type_combine,
};
