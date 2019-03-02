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

#define OPTIONS_C 1
#include <config.h>
#include "preprocessor.h"
#ifdef HAVE_STRING_H
#include <string.h>
#endif

struct option_t
{
  char *ID;
  int argc;
  int (*function)(void);
  int (*function_arg)(char *arg);
};

static int options_argc = 0;

static int (*parse_arg)(char *arg) = NULL;

static int f_ignore(){return 0;}
static int f_debug(){debug_file = stderr; return 0;}
static int f_warning(){warning_file = stderr; return 0;}
static int f_error(){error_file = stderr; return 0;}
static int f_nodebug(){debug_file = NULL; return 0;}
static int f_nowarning(){warning_file = NULL; return 0;}
static int f_noerror(){error_file = NULL; return 0;}

static int D_arg(char *name)
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
      return 0;
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
  if ((*definition != '=') && (*definition))
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
  return 0;
}

static int i_arg(char *file)
{
  FILE *infile;

  file = find_in_path(include_path, file);
  if (!file)
    ERROR("couldn't find file to include\n");
  free(current_path);
  current_path = get_path(file);
  if (!(infile = fopen(file, "r")))
    ERROR("couldn't open file \"%s\"\n", file);
  pos_file = file;
  pos_line_begin = 0;
  pos_line_end = 0;
  if (preprocess_file(infile) < 0)
    ERROR("internal error\n");
  if (0 != fclose(infile))
    ERROR("I/O error\n");
  free(file);
  return 0;
}

static int o_arg(char *op)
{
  if ((op[0] == '-') && (!op[1]))
    outfile = stdout;
  else
    if (!(outfile = fopen(op, "w")))
      ERROR("couldn't open file \"%s\"\n", op);
  return 0;
}

static int debug_arg(char *op)
{
  if ((op[0] == '-') && (!op[1]))
    debug_file = stdout;
  else
    if (!(debug_file = fopen(op, "w")))
      ERROR("couldn't open file \"%s\"\n", op);
  return 0;
}

static int error_arg(char *op)
{
  if ((op[0] == '-') && (!op[1]))
    error_file = stdout;
  else
    if (!(error_file = fopen(op, "w")))
      ERROR("couldn't open file \"%s\"\n", op);
  return 0;
}

static int warning_arg(char *op)
{
  if ((op[0] == '-') && (!op[1]))
    warning_file = stdout;
  else
    if (!(warning_file = fopen(op, "w")))
      ERROR("couldn't open file \"%s\"\n", op);
  return 0;
}

static int U_arg(char *op)
{
  if (macro_del(op)<0)
    ERROR("internal error\n");
  return 0;
}

static int I_arg(char *op)
{
  int i;

  for (i = 0; include_path[i]; i++);
  i++;
  if (include_path == include_path_default)
    {
      ALLOCATE(char *, include_path, i+1);
      for (i = 0; include_path_default[i]; i++)
	{
	  include_path[i] = include_path_default[i];
	}
      i++;
    }
  else
    REALLOCATE(char *, include_path, i+1);
  
  include_path[i-1] = op;
  include_path[i] = NULL;
  return 0;
}

static struct option_t options[] = 
  {
    {"-D", 1, f_ignore, D_arg},
    {"--define", 1, f_ignore, D_arg},
    {"--macro", 1, f_ignore, D_arg},
    {"--equ", 1, f_ignore, D_arg},
    {"-I", 1, f_ignore, I_arg},
    {"--add-include-path", 1, f_ignore, I_arg},
    {"-o", 1, f_ignore, o_arg},
    {"--out", 1, f_ignore, o_arg},
    {"-i", 1, f_ignore, i_arg},
    {"--include", 1, f_ignore, i_arg},
    {"-U", 1, f_ignore, U_arg},
    {"--undef", 1, f_ignore, U_arg},

    {"--debug", 0, f_debug, NULL},
    {"--debug-file", 1, f_ignore, debug_arg},
    {"--nodebug", 0, f_nodebug, NULL},
    {"--warning", 0, f_warning, NULL},
    {"--warning-file", 1, f_ignore, warning_arg},
    {"--nowarning", 0, f_nowarning, NULL},
    {"--error", 0, f_error, NULL},
    {"--error-file", 1, f_ignore, error_arg},
    {"--noerror", 0, f_noerror, NULL},

    {NULL, 0, NULL, NULL}
  };

int parse_option(char *op)
{
  int i;
  FILE *file;

  if (options_argc != 0)
    {
      options_argc--;
      return parse_arg(op);
    }

  for (i = 0; options[i].ID; i++)
    {
      if (strcmp(options[i].ID, op))
	continue;
      parse_arg = options[i].function_arg;
      options_argc = options[i].argc;
      return options[i].function();
    }

  if ((op[0] == '-') && (!op[1]))
    file = stdin;
  else
    if (!(file = fopen(op, "r")))
      ERROR("couldn't open file \"%s\"\n", op);
  
  pos_file = op;
  pos_line_begin = pos_line_end = 0;

  free(current_path);
  current_path = get_path(op);

  if (preprocess_file(file) < 0)
    ERROR("internal error\n");
  if (fclose(file))
    ERROR("I/O error\n");
  return 0;
}
