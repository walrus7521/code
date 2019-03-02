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

#define ASSEMBLER_C 1
#include <config.h>
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef STDC_HEADERS
#include <stdio.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include "assembler.h"

struct opcode_t *opcodes = NULL;
struct label_t *symtable = NULL;

char *pos_file;
int pos_line;

// this function reads the file, converts each opcode to its hex form,
// and creates the symbol table for labels
//
// infile should be a file, open for reading
//
int pass1(FILE *infile)
{
  char *line = NULL;
  unsigned short int address = 0;
  char page = 0;
  struct opcode_t *opcode = opcodes;
  struct label_t *label = symtable;

  while (!feof(infile))
    {
      if (!(line = fgetline(infile)))
	{
	  if (feof(infile))
	    return 0;
	  else
	    return -1;
	}
      pos_line++;
      switch (line[0])
	{
	case 0:
	  // empty line
	  break;
	  // I assume the file is preprocessed and tidied up completely (possibly by a preprocessor)
	case '.':
	case '#':
	  // directive
	  if (0 == strncasecmp(line+1, "org ", 4))
	    address = atoi(line+5);
	  else if (0 == strncasecmp(line+1, "file ", 5)) // from preprocessor: this comes out of file <arg>
	    {
	      pos_file = str_cpy_alloc(line+6);
	      pos_line = 0;
	    }
	  else if (0 == strncasecmp(line+1, "line ", 5)) // form preprocessor: this was line nr <arg>
	    pos_line = atoi(line+6);
	  else if (0 == strncasecmp(line+1, "page ", 5)) // form preprocessor: this was line nr <arg>
	    if (page != atoi(line+6))
	      {
		page = atoi(line+6);
		if (opcode == NULL)
		  opcodes = opcode = (struct opcode_t *)make_new_page(page);
		else
		  {
		    opcode->next = (struct opcode_t *)make_new_page(page);
		    opcode = opcode->next;
		  }
		if (!opcode)
		  return -1;
		opcode->next = NULL;
	      }
	  free(line);
	  break;
	case ' ':
	  // opcode
	  if (opcode == NULL)
	    opcodes = opcode = z80_asm_opcode(line+1, address);
	  else
	    {
	      opcode->next = z80_asm_opcode(line+1, address);
	      opcode = opcode->next;
	    }
	  if (!opcode)
	    return -1;
	  opcode->next = NULL;
	  address += opcode->size;
	  free(line); // needed parts are copied
	  break;
	default:
	  // label
	  if (label == NULL)
	    symtable = label = make_label(line, address, page);
	  else
	    {
	      label->next = make_label(line, address, page);
	      label = label->next;
	    }
	  if (!label)
	    return -1;
	  label->next = NULL;
	  // no free(line): line is used in label
	}
    }
  return 0;
}

// creates an intel hex file out of the code assembled in pass1
// This intel hex file can then be used to make asm progs or apps
//
// destfile should be a file open for writing
//
int pass2(FILE *destfile)
{
  struct opcode_t *c;
  char *code;
  int arg1, arg2;

  for (c = opcodes; c; c = c->next)
    {
      if (c->type == Z80_TYPE_NEW_PAGE)
	intel_hex_page(destfile, ((struct new_page_t *)(c))->page);
      else
	{
	  pos_line = c->pos_line;
	  pos_file = c->pos_file;
	  DEBUG("pass2: loop\n");
	  if (c->arg1)
	    arg1 = eval_expr(c->arg1, c->address);
	  DEBUG("pass2: arg1 evaluated\n");
	  if (c->arg2)
	    arg2 = eval_expr(c->arg2, c->address);
	  DEBUG("pass2: arg2 evaluated\n");
	  code = z80_types_functions[c->type](c,arg1,arg2);
	  if (!code)
	    return -1;
	  DEBUG("pass2: code formed\n");
	  if (intel_hex_write(destfile, code, c->address) < 0)
	    return -1;
	  DEBUG("pass2: written\n");
	}
    }
  if (intel_hex_write(destfile, NULL, 0) < 0)
    return -1;
  DEBUG("pass2: flushed\n");
  if (intel_hex_end(destfile) < 0)
    return -1;
  DEBUG("pass2: ended\n");
  return 0;
}

int main(int argc, char *argv[])
{
  FILE *infile, *outfile;
  if (argc != 3)
    fprintf(stderr, "Usage: assembler infile outfile\n");
  pos_file = argv[1];
  pos_line = 0;
  infile = fopen(argv[1], "r");
  if (pass1(infile)<0)
    {
      ERROR("error in pass 1\n");
      return 1;
    }
  fclose(infile);
  outfile = fopen(argv[2], "w");
  if (pass2(outfile)<0)
    {
      ERROR("error in pass 2\n");
      return 1;
    }
  fclose(outfile);
  return 0;
}
