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

#define DIRECTIVES_C
#include <config.h>
#ifdef STDC_HEADERS
#include <stdio.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "../preprocessor.h"
#include "cores.h"

static int dir_page_nr = 0;

char *dir_org(char *arg)
{
  int val;
  char *retval;

  if (!(arg = macro_substitute_all(arg)))
    ERROR("internal error\n");
  if ((val = expr_calculate(arg)) == 0x7fffffff)
    ERROR("syntax error in expression\n");
  
  if (asprintf(&retval, "#org %i", val) < 0)
    ERROR("asprintf returned an error\n");
  if (!retval)
    ERROR("asprintf returned an error\n");    
  if (l_add(retval)<0)
    ERROR("internal error\n");
  return retval;
}

char *dir_file(char *arg)
{
  char instring = 0;
  char *retval;

  if (!(arg = macro_substitute_all(arg)))
    ERROR("internal error\n");
  if (!(arg = token_begin(arg, " \t")))
    ERROR("no filename given\n");
  switch (*arg)
    {
    case '"':
    case '\'':
      instring = *arg;
      break;
    case '<':
      instring = '>';
      break;
    case '[':
      instring = ']';
      break;
    case '{':
      instring = '}';
      break;
    case '(':
      instring = ')';
      break;
    default:
      return NULL;
    }
  arg++;
  if (!(string_interpolate(arg, instring, NULL)))
    ERROR("syntax error in string\n");
  retval = strcat2("#file ", arg);
  if (!retval)
    ERROR("internal error\n");
  if (l_add(retval)<0)
    ERROR("internal error\n");
  return retval;
}

char *dir_line(char *arg)
{
  int val;
  char *retval;

  if (!(arg = macro_substitute_all(arg)))
    ERROR("internal error\n");
  if ((val = expr_calculate(arg)) == 0x7fffffff)
    ERROR("syntax error in expression\n");
  
  if (asprintf(&retval, "#line %i", val) < 0)
    ERROR("asprintf returned an error\n");
  if (!retval)
    ERROR("asprintf returned an error\n");
  if (l_add(retval)<0)
    ERROR("internal error\n");
  return retval;
}

char *dir_page(char *arg)
{
  int val;
  char *retval;

  if (!(arg = macro_substitute_all(arg)))
    ERROR("internal error\n");
  if ((val = expr_calculate(arg)) == 0x7fffffff)
    ERROR("syntax error in expression\n");
  dir_page_nr = val;
  if (asprintf(&retval, "#page %i", val) < 0)
    ERROR("asprintf returned an error\n");
  if (!retval)
    ERROR("asprintf returned an error\n");
  if (l_add(retval)<0)
    ERROR("internal error\n");
  return retval;
}

char *dir_newpage(char *arg)
{
  char *retval;

  dir_page_nr++;
  if (asprintf(&retval, "#org %i\n#page %i", 0x4000, dir_page_nr) < 0)
    ERROR("asprintf returned an error\n");
  if (!retval)
    ERROR("asprintf returned an error\n");
  if (l_add(retval)<0)
    ERROR("internal error\n");
  return retval;
}

static char *dir_db_arg(char **arg_p)
{
  char *arg = *arg_p;
  char *retval = NULL;
  char *expr;
  char tmp[4];
  char *temp;
  int i,cc;

  if ((*arg == '"') || (*arg == '\''))
    {
      expr = arg + 1;
      if (!(arg = string_interpolate(expr, *arg, &cc)))
	ERROR("syntax error in string\n");
      for (i = 0; i < cc; i++)
	{
	  if (snprintf(tmp, 4, "%i", expr[i]) < 0)
	    ERROR("asprintf returned an error\n");
	  retval = strcat3_realloc(retval, "\n db ", tmp);
	}
      arg = token_begin(arg, " \t");
    }
  else if (*arg == '[')
    {
      temp = arg + 1;
      if ((cc = expr_calculate_begin(&temp)) < 0)
	goto normal_expr;
      if (*temp != ']')
	goto normal_expr;
      temp++;
      if (!(expr = expr_print_begin(&temp)))
	{
	  free(expr);
	  goto normal_expr;
	}
      for (i = 0; i < cc; i++)
	retval = strcat3_realloc(retval, "\n db ", expr);
      arg = temp;
      free(expr);
    }
  else
    {
    normal_expr:
      if (!(expr = expr_print_begin(&arg)))
	ERROR("syntax error in expression\n");
      retval = strcat3_realloc(retval, "\n db ", expr);
      free(expr);
    }
  *arg_p = arg;
  return retval;
}

static char *dir_dw_arg(char **arg_p)
{
  char *arg = *arg_p;
  char *retval = NULL;
  char *expr;
  char *temp;
  int i,cc;

  if (*arg == '[')
    {
      temp = arg + 1;
      if ((cc = expr_calculate_begin(&temp)) < 0)
	goto normal_expr;
      if (*temp != ']')
	goto normal_expr;
      temp++;
      if (!(expr = expr_print_begin(&temp)))
	{
	  free(expr);
	  goto normal_expr;
	}
      for (i = 0; i < cc; i++)
	retval = strcat3_realloc(retval, "\n dw ", expr);
      arg = temp;
      free(expr);
    }
  else
    {
    normal_expr:
      if (!(expr = expr_print_begin(&arg)))
	ERROR("syntax error in expression\n");
      retval = strcat3_realloc(retval, "\n dw ", expr);
      free(expr);
    }
  *arg_p = arg;
  return retval;
}

char *dir_db(char *arg)
{
  char *retval = NULL;

  if (!(arg = macro_substitute_all(arg)))
    ERROR("internal error\n");
  if (!(token_begin(arg, " \t")))
    return ""; // no args given
  retval = dir_db_arg(&arg);
  while (arg)
    {
      if (*arg != ',')
	ERROR("syntax error in argument list of db\n");
      if (!retval)
	ERROR("internal error\n");
      arg++;
      if (!(arg = token_begin(arg, " \t")))
	ERROR("syntax error in argument list of db\n"); // nothing specified atfer a ','
      retval = strcat2_realloc(retval, dir_db_arg(&arg));
    }
  if (!retval)
    ERROR("internal error\n");
  if (l_add(retval)<0)
    ERROR("internal error\n");
  return retval;
}

char *dir_dw(char *arg)
{
  char *retval = NULL;

  if (!(arg = macro_substitute_all(arg)))
    ERROR("internal error\n");
  if (!(token_begin(arg, " \t")))
    return ""; // no args given
  retval = dir_dw_arg(&arg);
  while (arg)
    {
      if (*arg != ',')
	ERROR("syntax error in argument list of dw\n");
      if (!retval)
	ERROR("internal error\n");
      arg++;
      if (!(arg = token_begin(arg, " \t")))
	ERROR("syntax error in argument list of dw\n"); // nothing specified atfer a ','
      retval = strcat2_realloc(retval, dir_dw_arg(&arg));
    }
  if (!retval)
    ERROR("internal error\n");
  if (l_add(retval)<0)
    ERROR("internal error\n");
  return retval;
}

// assume output is always to outfile
char *dir_include(char *file)
{
  char *file_end;
  char instring;
  char *path = current_path;
  FILE *infile;

  char *l_file;
  int l_line_begin;
  int l_line_end;

  switch (*file)
    {
    case '"':
    case '\'':
      instring = *file;
      break;
    case '<':
      instring = '>';
      break;
    case '[':
      instring = ']';
      break;
    case '{':
      instring = '}';
      break;
    case '(':
      instring = ')';
      break;
    default:
      return NULL;
    }

  file++;
  if (!(file_end = string_interpolate(file, instring, NULL)))
    ERROR("syntax error in string\n");
  if ((instring == '"') || (instring == '\''))
    file = strcat2(current_path, file);
  else
    file = find_in_path(include_path, file);
  if (!file)
    ERROR("couldn't find file to include\n");
  current_path = get_path(file);
  if (!(infile = fopen(file, "r")))
    ERROR("couldn't open file \"%s\"\n", file);
  l_file = pos_file;
  l_line_begin = pos_line_begin;
  l_line_end = pos_line_end;
  pos_file = file;
  pos_line_begin = 0;
  pos_line_end = 0;
  if (preprocess_file(infile) < 0)
    ERROR("internal error\n");
  pos_file = l_file;
  pos_line_begin = l_line_begin;
  pos_line_end = l_line_end;
  if (0 != fclose(infile))
    ERROR("I/O error\n");
  free(file);
  free(current_path);
  current_path = path;
  return "";
}

char *dir_if(char *args)
{
  int val;
  dir_if_depth++;
  if (!(args = macro_substitute_all(args)))
    ERROR("internal error\n");
  if ((val = expr_calculate(args)) == 0x7fffffff)
    ERROR("syntax error in expression\n");
  if (val)
    return "";
  if (core_activate(&core_iffalse)<0)
    ERROR("internal error\n");
  dir_if_false_depth = dir_if_depth;
  return "";
}

char *dir_ifdef(char *args)
{
  char *name_end;
  dir_if_depth++;
  if ((name_end = macro_token_end(args)))
    *name_end = 0;
  if (macro_defined(args))
    return "";
  if (core_activate(&core_iffalse)<0)
    ERROR("internal error\n");
  dir_if_false_depth = dir_if_depth;
  return "";
}

char *dir_ifndef(char *args)
{
  char *name_end;
  dir_if_depth++;
  if ((name_end = macro_token_end(args)))
    *name_end = 0;
  if (!macro_defined(args))
    return "";
  if (core_activate(&core_iffalse)<0)
    ERROR("internal error\n");
  dir_if_false_depth = dir_if_depth;
  return "";
}

char *dir_else(char *args)
{
  if (core_activate(&core_elsiffalse)<0)
    ERROR("internal error\n");
  dir_if_false_depth = dir_if_depth;
  return "";
}

char *dir_endif(char *args)
{
  dir_if_depth--;
  if (dir_if_depth < 0)
    ERROR("unmatched #if ... #endif directives\n");
  return "";
}

char *dir_define(char *name)
{
  char **args;
  char *definition;
  char *name_end;
  char instring = 0;
  int argc, si, di;

  definition = name_end = macro_token_end(name);
  if (!name_end)
    {
      if (macro_add(name, 0, NULL, NULL) < 0)
	ERROR("internal error\n");
      return "";
    }
  if (*name_end == '(')
    {
      if (!(definition = macro_def_get_args(name_end+1, &args, &argc, ')')))
	ERROR("syntax error in argument list of a macro\n");
    }
  else
    {
      args = NULL;
      argc = 0;
    }


  if ((*definition != ' ') && (*definition != '\t') && *definition)
    ERROR("syntax error in macro definition\n");
  if (*definition)
    definition++;
  *name_end = 0;
  
  for (si = 0, di = 0; definition[si]; si++, di++)
    {
      if ((definition[si] == '\'') || (definition[si] == '"'))
	{
	  if (!instring) instring = definition[si];
	  else if (instring == definition[si]) instring = 0;
	}
      else if (definition[si] == '\\')
	{
	  if (instring)
	    {
	      if  (definition[si+1])
		{
		  definition[di] = definition[si];
		  di++;
		  si++;
		}
	    }
	  else
	    {
	      if (definition[si+1] == '\\') si++;
	      else definition[si] = '\n';
	    }
	}
      definition[di] = definition[si];
    }
  if (definition[di])
    definition[di] = 0;
  if (macro_add(name, argc, args, definition)<0)
    ERROR("internal error\n");
  return "";
}

char *dir_undef(char *args)
{
  char *name_end;
  
  if ((name_end = macro_token_end(args)))
    *name_end = 0;
  if (macro_del(args) < 0)
    ERROR("internal error\n");
  return "";
}

char *dir_ignore(char *args){return "";}
