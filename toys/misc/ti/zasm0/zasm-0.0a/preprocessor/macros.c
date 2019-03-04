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

#define MACROS_C
#include <config.h>

#ifdef HAVE_STRING_H
#include <string.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#include "preprocessor.h"

#include "macros/macros.h"
#include "macros/search.c"
#include "macros/subs.c"
#include "macros/token.c"

static struct macro_t *macro_make_macro(char *name, int argc, char **args, char *text)
{
  struct macro_t *retval;
  int i;

  ALLOCATE(struct macro_t, retval, 1);
  if (!(retval->name = str_cpy_alloc(name)))
    return NULL;
  if (text)
    {
      if (!(retval->text = str_cpy_alloc(text)))
	return NULL;
    }
  else
    retval->text = NULL;
  if (argc)
    {
      ALLOCATE(char *, retval->args, argc);
      for (i = 0; i < argc; i++)
	if (!(retval->args[i] = str_cpy_alloc(args[i])))
	  return NULL;
    }
  else
    retval->args = NULL;
  retval->argc = argc;
  return retval;
}


static void macro_free(struct macro_t *macro)
{
  int c;
  for (c = 0; c < macro->argc; c++)
    free(macro->args[c]);
  if (macro->args)
    free(macro->args);
  free(macro->name);
  if (macro->text)
    free(macro->text);
  free(macro);
}

char *macro_def_get_args(char *str, char ***args_p, int *argc_p, char end_c)
{
  char **args;
  char *end_arg;
  int argc = 1,i;

  end_arg = token_begin_lit(str, " \t");
  if (*end_arg == end_c)
    {
      *args_p = NULL;
      *argc_p = 0;
      return end_arg+1;
    }
  
  for (i = 0; str[i] != end_c; i++)
    {
      if (!str[i]) return NULL;
      else if (str[i] == ',') argc++;
    }
  ALLOCATE(char *, args, argc);
  for (i = 0; i < argc; i++)
    {
      str = token_begin(str, " \t");
      args[i] = str;
      str = macro_token_end(str);
      if (args[i] == str)
	return NULL; // empty arg name
      end_arg = str;
      str = token_begin(str, " \t");
      if (!str && !end_c)
	break;
      if ((*str != end_c) && (*str != ','))
	return NULL;
      if (end_arg)
	*end_arg = 0;
      str++;
    }
  if (!str)
    str = "";
  *args_p = args;
  *argc_p = argc;
  return str;
}

int macro_del(char *name)
{
  struct macro_search_t *tree;

  tree = macro_search_find(macro_tree, name);
  if (!tree)
    {
      WARNING("deleting nonexistant macro: \"%s\"\n", name);
      return 0;
    }
  if (macro_search_child_count(tree) != 1)
    {
      macro_free(tree->macro);
      tree->macro = NULL;
    }
  else
    {
      macro_search_del_intern(tree);
    }
  return 0;
}

int macro_add(char *name, int argc, char **args, char *text)
{
  struct macro_t *macro;
  int val;
  
  if (!(macro = macro_make_macro(name, argc, args, text)))
    ERROR("internal error\n");
  if ((val = macro_add_intern(macro, macro_tree, name)))
    {
      if (val != -2)
	ERROR("internal error\n");
      WARNING("defining an earlier defined macro: \"%s\"\n", name);
      return 0;
    }
  return 0;
}

int macro_defined(char *name)
{
  if (macro_search_find(macro_tree, name))
    return 1;
  return 0;
}

int macro_print()
{
  if (macro_print_intern(macro_tree, 0))
    ERROR("internal error\n");
  return 0;
}
