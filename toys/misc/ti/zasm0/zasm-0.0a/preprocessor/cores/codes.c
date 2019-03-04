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

#define CODES_C
#include <config.h>

#ifdef STDC_HEADERS
#include <stdio.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "cores.h"
#include "../preprocessor.h"

char *code_macro(char *name, char *code, char *args_s)
{
  char *name_end;
  char **args;
  int argc, i;

  name_end = macro_token_end(name);
  if (name_end == name)
    ERROR("defining macro without a name\n");
  if ((*name_end != ' ') && (*name_end != '\t') && (*name_end != ':'))
    ERROR("invalid macro name\n");
  *name_end = 0;
  if (!args_s)
    {
      args = NULL;
      argc = 0;
    }
  else
    if (!macro_def_get_args(args_s, &args, &argc, 0))
      ERROR("syntax error in argument list\n");
  if (core_activate(&core_macro)<0)
    ERROR("internal error\n");
  for (i = 0; i < argc; i++)
    if (!(args[i] = str_cpy_alloc(args[i])))  // make the args last longer than this line
      ERROR("internal error\n");
  code_macro_text = NULL;
  code_macro_args = args;
  code_macro_argc = argc;
  code_macro_name = str_cpy_alloc(name);
  code_macro_depth = 0;
  return "";
}

char *code_equ(char *name, char *code, char *text)
{
  char *name_end;
  
  name_end = macro_token_end(name);
  if (name_end == name)
    ERROR("no name in equate\n");
  if ((*name_end != ' ') && (*name_end != '\t') && (*name_end != ':'))
    ERROR("invalid name in equate\n");
  *name_end = 0;
  if (macro_add(name, 0, NULL, text) < 0)
    ERROR("internal error\n");
  return "";
}

char *code_db(char *label, char *code, char *text)
{
  char *label_end;
  
  label_end = token_end(label, " \t:");
  *label_end = 0;
  
  if (!(text = dir_db(text)))
    ERROR("internal error\n");
  if (!(label = strcat2(label, text)))
    ERROR("internal error\n");    
  if (l_add(label)<0)
    ERROR("internal error\n");
  return label;
}

char *code_dw(char *label, char *code, char *text)
{
  char *label_end;
  
  label_end = token_end(label, " \t:");
  *label_end = 0;
  
  if (!(text = dir_dw(text)))
    ERROR("internal error\n");
  if (!(label = strcat2(label,text)))
    ERROR("internal error\n");
  if (l_add(label)<0)
    ERROR("internal error\n");
  return label;
}

static char *prefix_expr_end(char *expr)
{
  char *expr_end;
  
  if (instr(*expr, "+-*/&|<>"))
    {
      expr_end = prefix_expr_end(expr+1);
      return prefix_expr_end(expr_end+1);
    }
  if (*expr == '^')
    return prefix_expr_end(expr+1);
  return token_end(expr, ":");
}

static char *code_opcode_get_arg_indir(char *expr)
{
  char *expr_end;
  char *retval;

  if ((expr[0] == '+') || (expr[0] == '-'))
    {
      expr_end = prefix_expr_end(expr+1);
      if (*expr_end != ':')
	ERROR("internal error\n"); // wrong output from expr_print
      if (((expr[1] == 'i') || (expr[1] == 'I')) &&
	  ((expr[2] == 'x') || (expr[2] == 'X') || (expr[2] == 'y') || (expr[2] == 'Y')) &&
	  (expr[3] == ':'))
	{
	  if (expr[0] == '+')
	    {
	      if (asprintf(&retval, "(%c%c+%s)", expr[1], expr[2], expr_end+1)<0)
		ERROR("asprintf returned an error\n");
	    }
	  else
	    {
	      if (asprintf(&retval, "(%c%c+-0:%s)", expr[1], expr[2], expr_end+1)<0)
		ERROR("asprintf returned an error\n");
	    }
	  return retval;
	}
      if (((expr_end[1] == 'i') || (expr_end[1] == 'I')) &&
	  ((expr_end[2] == 'x') || (expr_end[2] == 'X') || (expr_end[2] == 'y') || (expr_end[2] == 'Y')) &&
	  (!expr_end[3]) &&
	  (expr[0] == '+'))
	{
	  *expr_end = 0;
	  if (asprintf(&retval, "(%c%c+%s)", expr_end[1], expr_end[2], expr+1)<0)
	    ERROR("asprintf returned an error\n");
	  return retval;
	}
    }
  else if (((expr[0] == 'i') || (expr[0] == 'I')) &&
	   ((expr[1] == 'x') || (expr[1] == 'X') || (expr[1] == 'y') || (expr[1] == 'Y')) &&
	   (!expr[2]))
    {
      if ((expr[1] == 'x') || (expr[1] == 'X'))
	return str_cpy_alloc("(ix+0)");
      else
	return str_cpy_alloc("(iy+0)");
    }
  return strcat3("(", expr, ")");
}

static char *code_opcode_get_arg(char **str_p)
{
  char *expr;
  char *str = *str_p;
  char *expr_end;
  
  if (!(str = token_begin(str, " \t")))
    return NULL; // no arg
  if (*str == '(')
    {
      expr_end = str+1;
      if (!(expr = expr_print_begin(&expr_end)))
	ERROR("syntax error in expression\n");
      if (*expr_end == ')')
	if ((!(expr_end = token_begin(expr_end + 1, " \t"))) || (*expr_end == ','))
	  {
	    *str_p = expr_end;
	    return code_opcode_get_arg_indir(expr);
	  }
      free(expr);
    }
  *str_p = str;
  return expr_print_begin(str_p);
}

char *code_opcode(char *label, char *code, char *text)
{
  char *label_end;
  char *retval;
  char *arg1 = NULL;
  char *arg2 = NULL;
  int l;

  label_end = token_end(label, " \t:");
  *label_end = 0;
  label_end = token_end(code, " \t");
  if (label_end)
    *label_end = 0;

  if (text)
    text = macro_substitute_all(text);
  text = token_begin(text, "\t ");

  if (text)
    if (!(arg1 = code_opcode_get_arg(&text)))
      ERROR("internal error\n");
  if (text)
    {
      if (*text != ',')
	ERROR("syntax error in argument list of an opcode\n");
      text++;
      if (!(arg2 = code_opcode_get_arg(&text)))
	ERROR("internal error\n");
    }
  if (text)
    return NULL;

  if (arg2)
    {
      l = asprintf(&retval, "%s\n %s %s,%s", label, code, arg1, arg2);
      free(arg1);
      free(arg2);
    }
  else if (arg1)
    {
      l = asprintf(&retval, "%s\n %s %s", label, code, arg1);
      free(arg1);
    }
  else
    l = asprintf(&retval, "%s\n %s", label, code);

  if (l<0)
    ERROR("asprintf returned an error\n");
  if (l_add(retval)<0)
    ERROR("internal error\n");
  return retval; // TODO
}

char *code_zbit(char *label, char *code, char *text)
{
  char *label_end;
  char *arg2;
  char *retval;
  int bit;

  label_end = token_end(label, " \t:");
  *label_end = 0;
  label_end = token_end(code, " \t");
  *label_end = 0;

  if (!(text = macro_substitute_all(text)))
    return NULL;

  if (((bit = expr_calculate_begin(&text)) < 0) || (bit > 7))
    ERROR("syntax error in expression\n");
  if (*text != ',')
    ERROR("syntax error in argument list of an opcode\n");
  text++;
  if (!(arg2 = code_opcode_get_arg(&text)))
    ERROR("syntax error in expression\n");
  if (asprintf(&retval, "%s\n %s %i,%s", label, code, bit, arg2)<0)
    ERROR("asprintf returned an error\n");
  free(arg2);
  if (l_add(retval)<0)
    ERROR("internal error\n");
  return retval;
}

char *code_empty(char *label, char *code, char *text)
{
  char *label_end;
  
  label_end = token_end(label, " \t:");
  if (label_end)
    *label_end = 0;
  if (!(label_end = str_cpy_alloc(label)))
    ERROR("internal error\n");
  if (l_add(label_end)<0)
    ERROR("internal error\n");    
  return label_end;
}
