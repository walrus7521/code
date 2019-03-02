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

#define DEFAULT_C
#include <config.h>
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef STDC_HEADERS
#include <stdio.h>
#endif
#include "../preprocessor.h"
#include "cores.h"

char *core_pp_line_default(char *line)
{
  char *label;
  char *pp_label;
  char *retval = NULL;
  int i;

  line = comments_remove(line);
  if (!(label = token_begin(line, " \t")))
    return ""; // empty line
  if ((*label == '.') || (*label == '#'))
    label++;
  if ((retval = directives(label)) != label)
    return retval;
  retval = NULL;
  if ((label = defines(line)) != line)
    return label;
  if (!(label = macro_substitute_all_once(line)))
    ERROR("internal error\n");
  if (label == line)
    ERROR("unknown directive or code");

  for (i = 0; label[i]; i++)
    {
      if (label[i] != '\n')
	continue;
      label[i] = 0;
      if (!(pp_label = preprocess(label)))
	ERROR("internal error\n");
      if (!(retval = strcat3_realloc(retval, "\n", pp_label)))
	ERROR("internal error\n");
      label = label+i+1;
      i = -1;
    }
  if (!(pp_label = preprocess(label)))
    ERROR("internal error\n");    
  if (!(retval = strcat3_realloc(retval, "\n", pp_label)))
    ERROR("internal error\n");
  return retval;
}

struct directives_t core_dir_default[] =
  {
    {"if", dir_if},
    {"ifdef", dir_ifdef},
    {"ifndef", dir_ifndef},
    {"endif", dir_endif},
    {"else", dir_else},
    {"elsif", dir_else},
    {"elseif", dir_else},
    {"elsifdef", dir_else},
    {"elseifdef", dir_else},
    {"elsifndef", dir_else},
    {"elseifndef", dir_else},

    {"define", dir_define},
    {"declare", dir_define},
    {"macro", dir_define},
    {"equ", dir_define},
    {"const", dir_define},
    {"undef", dir_undef},

    {"include", dir_include},
    {"input", dir_include},

    {"dw", dir_dw},
    {"db", dir_db},

    {"org", dir_org},
    {"file", dir_file},
    {"line", dir_line},
    {"page", dir_page},
    
    {"newpage", dir_newpage},

    {"end", dir_ignore},
    {NULL, NULL}
  };

struct codes_t core_defines_default[] = 
  {
    {"macro", code_macro},
    {".macro", code_macro},
    {"#macro", code_macro},

    {"equ", code_equ},
    {"=", code_equ},
    {".equ", code_equ},
    {"#equ", code_equ},
    
    {"db", code_db},
    {".db", code_db},
    {"#db", code_db},
    {"dw", code_dw},
    {".dw", code_dw},
    {"#dw", code_dw},

    {"bit", code_zbit},
    {"res", code_zbit},
    {"set", code_zbit},

    {"adc", code_opcode},
    {"add", code_opcode},
    {"and", code_opcode},
    {"call", code_opcode},
    {"ccf", code_opcode},
    {"cp", code_opcode},
    {"cpd", code_opcode},
    {"cpi", code_opcode},
    {"cpdr", code_opcode},
    {"cpir", code_opcode},
    {"cpl", code_opcode},
    {"daa", code_opcode},
    {"dec", code_opcode},
    {"di", code_opcode},
    {"djnz", code_opcode},
    {"ei", code_opcode},
    {"ex", code_opcode},
    {"exx", code_opcode},
    {"halt", code_opcode},
    {"im", code_opcode},
    {"in", code_opcode},
    {"inc", code_opcode},
    {"ind", code_opcode},
    {"indr", code_opcode},
    {"ini", code_opcode},
    {"inir", code_opcode},
    {"jp", code_opcode},
    {"jr", code_opcode},
    {"ld", code_opcode},
    {"ldd", code_opcode},
    {"lddr", code_opcode},
    {"ldi", code_opcode},
    {"ldir", code_opcode},
    {"neg", code_opcode},
    {"nop", code_opcode},
    {"or", code_opcode},
    {"otdr", code_opcode},
    {"otir", code_opcode},
    {"out", code_opcode},
    {"outi", code_opcode},
    {"outd", code_opcode},
    {"pop", code_opcode},
    {"push", code_opcode},
    {"ret", code_opcode},
    {"reti", code_opcode},
    {"retn", code_opcode},
    {"rl", code_opcode},
    {"rla", code_opcode},
    {"rlc", code_opcode},
    {"rlca", code_opcode},
    {"rld", code_opcode},
    {"rr", code_opcode},
    {"rra", code_opcode},
    {"rrc", code_opcode},
    {"rrca", code_opcode},
    {"rrd", code_opcode},
    {"rst", code_opcode},
    {"sbc", code_opcode},
    {"scf", code_opcode},
    {"sla", code_opcode},
    {"sra", code_opcode},
    {"srl", code_opcode},
    {"sub", code_opcode},
    {"xor", code_opcode},

    {"",code_empty},
    {"end", code_ignore},
    {NULL, NULL}
  };

struct core_t core_default = {core_pp_line_default, core_dir_default, core_defines_default, NULL};
