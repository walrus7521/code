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

enum
  {
    MACRO_ARGS_CSTYLE,
    MACRO_ARGS_ZDSSTYLE,
  };

static char *macro_arg_end(char *str)
{
  char instring;
  int depth;
 
  depth = 0;
  instring = 0;
  for (; 1 ; str++)
    {
      if (!(*str))
	return str;
      else if ((*str == '\'') || (*str == '"'))
	{
	  if (instring == *str) instring = 0;
	  else if (!instring) instring = *str;
	}
      else if (!instring)
	{
	  if (instr(*str, "([{")) depth++;
	  else if (instr(*str, "}])"))
	    {
	      depth--;
	      if (depth < 0)
		return str;
	    }
	  if ((depth == 0) && (*str == ','))
	    return str;
	}
      else if ((*str == '\\') && str[1])
	str++;
    }  
}

static char *macro_get_args(char *string, char ***args_p, int argc)
{
  char *cbegin, *begin, *end;
  char **args;
  int style;
  int j;

  if (argc == 0)
    {
      *args_p = NULL;
      return string;
    }
  ALLOCATE(char *, args, argc);
  *args_p = args;
  cbegin = token_begin(string, " \t");
  if (!cbegin)
    ERROR("syntax error in argument list of a macro\n")
  if (instr(*cbegin, "({["))
    {
      style = MACRO_ARGS_CSTYLE;
      begin = cbegin+1;
    }
  else if (cbegin != string)
    {
      style = MACRO_ARGS_ZDSSTYLE;
      begin = string+1;
    }
  else
    ERROR("syntax error in argument list of a macro\n");

 find_arguments:
  for (j = 0; j < argc; j++)
    {
      if (!(end = macro_arg_end(begin)))
	ERROR("wrong argument count for macro\n");
      if (instr(*end, "]})") && (style == MACRO_ARGS_CSTYLE) && (j == 0) && (argc != 1) && instr(*string, " \t"))
	{
	  // zdsmacro (arg1),arg2
	  style = MACRO_ARGS_ZDSSTYLE;
	  begin = string+1;
	  goto find_arguments;
	}
      if (((*end == ',') && (j == argc-1)) || ((*end != ',') && (j != argc-1)))
	ERROR("wrong argument count for macro\n"); // too few or too many args
      if ((!(*end)) && (style != MACRO_ARGS_ZDSSTYLE))
	ERROR("syntax error in argument list of a macro\n");
      args[j] = str_cpy_n_alloc(begin, end-begin);
      begin = end+1;
    }
  if (style == MACRO_ARGS_CSTYLE)
    end++; // point after closing parentese
  return end;
}

// '&argn\W' becomes args[n]
// '\Wargn\W' becomes args[n]
static char *macro_subs_intern(struct macro_t *macro, char **args)
{
  int size = 0, argc;
  int i, j;
  char *text;
  char *retval;
  
  if (macro->text == NULL)
    return "";
  text = macro->text;
  argc = macro->argc;
  // calculate the size needed for the string
  for (i = 0; text[i]; i++)
    {
      if (text[i] == '&')
	{
	  for (j = 0; j < argc; j++)
	    if (macro_token_eq(text+i+1, macro->args[j]))
	      {
		size += strlen(args[j]) - 1;
		i += strlen(macro->args[j]);
		break;
	      }
	  size++;
	}
      else if (macro_token_all(text[i]) && ((i==0) || !macro_token_all(text[i-1]))) // smart '||' is important
	{
	  for (j = 0; j < argc; j++)
	    if (macro_token_eq(text+i, macro->args[j]))
	      {
		size += strlen(args[j]) - 1;
		i += strlen(macro->args[j]) - 1;
		break;
	      }
	  size++;
	}
      else
	size++;
    }

  // actually substitute
  if (!(retval = l_alloc(size+1)))
    ERROR("internal error\n");
  size = 0;
  for (i = 0; text[i]; i++)
    {
      retval[size] = text[i];
      if (text[i] == '&')
	{
	  for (j = 0; j < argc; j++)
	    if (macro_token_eq(text+i+1, macro->args[j]))
	      {
		strcpy(retval+size, args[j]);
		size += strlen(args[j])-1;
		i += strlen(macro->args[j]);
		break;
	      }
	  size++;
	}
      else if (macro_token_all(text[i]) && ((i==0) || !macro_token_all(text[i-1]))) // smart '||' is important
	{
	  for (j = 0; j < argc; j++)
	    if (macro_token_eq(text+i, macro->args[j]))
	      {
		strcpy(retval+size, args[j]);
		size += strlen(args[j])-1;
		i += strlen(macro->args[j]) - 1;
		break;
	      }
	  size++;
	}
      else
	size++;
    }
  retval[size] = 0;
  return retval;
}

// substitute macro->name with macro->text, while args are used in the normal way
char *macro_substitute(char *name, int argc, char **args)
{
  struct macro_search_t *macro_search;
  struct macro_t *macro;

  if ((!(macro_search = macro_search_find(macro_tree, name))) || (!(macro = macro_search->macro)))
    {
      WARNING("macro not found: \"%s\"\n", name);
      return NULL;
    }
  if (macro->argc != argc)
    {
      ERROR("macro \"%s\" expects %i arguments, %i are supplied\n", name, macro->argc, argc);
      return NULL;
    }
  return macro_subs_intern(macro, args);
}

char *macro_substitute_all(char *string)
{
  int i;
  char *token;
  char *text;
  char *token_end;
  char **args;
  int argc;
  struct macro_t *macro;

  for (token = macro_token_begin(string); token; token = macro_token_next(token))
    {
      if (macro_token_eq(token, "defined"))
	{
	  if (!(token_end = macro_get_args(macro_token_end(token), &args, 1)))
	    ERROR("internal error\n");
	  if (!(text = token_begin(args[0], " \t")))
	    ERROR("no name given to 'defined'\n");
	  if (!macro_token_all(text[0]))
	    ERROR("invalid name given to 'defined'\n");
	  if (token_next(text, " \t"))
	    ERROR("invalid name given to 'defined'\n"); // more than one macro name specified
	  if (macro_token_find(text))
	    text = l_str_cpy_alloc("1");
	  else
	    text = l_str_cpy_alloc("0");
	  argc = 1;
	}
      else if ((macro = macro_token_find(token)))
	{
	  argc = macro->argc;
	  if ((token_end = macro_token_end_lit(token)))
	    if (!(token_end = macro_get_args(token_end, &args, argc)))
	      ERROR("internal error\n");
	  if (!(text = macro_subs_intern(macro, args)))
	    ERROR("internal error\n");
	}
      else
	continue;
      if (!(string = string_substitute_l(string, token, token_end - token, text)))
	ERROR("internal error\n");
      l_dealloc(text);
      for (i = 0; i < argc; i++)
	free(args[i]);
      if (args)
	free(args);
      text = macro_substitute_all(string);
      if (text != string)
	l_dealloc(string);
      return text;
    }
  return string;
}

char *macro_substitute_all_once(char *string)
{
  int i;
  char *token;
  char *text;
  char *token_end;
  char **args;
  int argc;
  struct macro_t *macro;

  for (token = macro_token_begin(string); token; token = macro_token_next(token))
    {
      if (macro_token_eq(token, "defined"))
	{
	  if (!(token_end = macro_get_args(macro_token_end(token), &args, 1)))
	    ERROR("internal error\n");
	  if (!(text = token_begin(args[0], " \t")))
	    ERROR("no name given to 'defined'\n");
	  if (!macro_token_all(text[0]))
	    ERROR("invalid name given to 'defined'\n");
	  if (token_next(text, " \t"))
	    ERROR("invalid name given to 'defined'\n");
	  if (macro_token_find(text))
	    text = l_str_cpy_alloc("1");
	  else
	    text = l_str_cpy_alloc("0");
	  argc = 1;
	}
      else if ((macro = macro_token_find(token)))
	{
	  argc = macro->argc;
	  if ((token_end = macro_token_end_lit(token)))
	    if (!(token_end = macro_get_args(token_end, &args, argc)))
	      ERROR("internal error\n");
	  if (!(text = macro_subs_intern(macro, args)))
	    ERROR("internal error\n");
	}
      else
	continue;
      if (!(string = string_substitute_l(string, token, token_end - token, text)))
	ERROR("internal error\n");
      l_dealloc(text);
      for (i = 0; i < argc; i++)
	free(args[i]);
      if (args)
	free(args);
      token = token_end;
    }
  return string;
}
