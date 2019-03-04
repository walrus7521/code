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

#define MACRO_C
#include <config.h>
#include "../preprocessor.h"
#include "cores.h"

char *code_macro_text = NULL;
char **code_macro_args = NULL;
int code_macro_argc = 0;
char *code_macro_name = NULL;
int code_macro_depth = 0;

char *core_pp_line_macro(char *line)
{
  char *code;
  
  if ((code = token_begin(line, " \t")))
    {
      if (token_eq(code, "endm", " \t") || token_eq(code, ".endm", " \t") || token_eq(code, "#endm", " \t"))
	{
	  code_macro_depth--;
	  if (code_macro_depth < 0)
	    {
	      if (macro_add(code_macro_name, code_macro_argc, code_macro_args, code_macro_text)<0)
		ERROR("internal error\n");
	      if (core_deactivate()<0)
		ERROR("internal error\n");
	      return "";
	    }
	}
      else if ((code = token_next(line, " \t")) && 
	       (token_eq(code, "macro", " \t") || token_eq(code, ".macro", " \t") || token_eq(code, "#macro", " \t")))
	code_macro_depth++;
    }
  if (!(code_macro_text = strcat3_realloc(code_macro_text, "\n", line)))
    ERROR("internal error\n");
  return "";
}

struct core_t core_macro = {core_pp_line_macro, NULL, NULL, NULL};
