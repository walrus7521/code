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

#include "expr.h"
static int expr_pattern_match(char **string, char *pat,
			      struct expr_t **args, struct expr_t *arg1,
			      char *after_arg1, int assoc, int level)
{
  char *str = *string;

  if (pat[0] == '#')
    {
      if (!arg1)
	return 0;
      args[0] = arg1;
      str = after_arg1;
      args++;
      pat++;
    }
  else
    str = token_begin(str, " \t");
  if (!str)
    return 0;
  while (*pat)
    {
      if (*pat == '#')
	{
	  str = token_begin(str, " \t");
	  if (!str)
	    return 0;
	  if (!pat[1])
	    {
	      switch (assoc)
		{
		case EXPR_ASSOC_LEFT:
		  *args = expr_interpr(&str, level+1);
		  break;
		case EXPR_ASSOC_RIGHT:
		  *args = expr_interpr(&str, level);
		default:
		  return 0;
		}
	    }
	  else
	    *args = expr_interpr(&str, 0);
	  if (!args[0])
	    return 0;
	  args++;
	  pat++;
	  str = token_begin(str, " \t");
	  if (!str)
	    {
	      if (*pat)
		return 0;
	      *args = NULL;
	      *string = str;
	      return 1;
	    }
	}
      else
	{
	  if (*pat != *str)
	    return 0;
	  pat++;
	  str++;
	}
    }
  *args = NULL;
  *string = str;
  return 1;
}

static int expr_number_pattern_match(char *string, char *pattern, char *all_chars)
{
  int si, pi;
  for (si = 0, pi = 0; pattern[pi]; si++, pi++)
    {
      if (pattern[pi] == '#')
	{
	  pi++;
	  if (!instr(string[si], all_chars)) // avoid empty matches
	    return 0;
	  if (!pattern[pi])
	    return 1;
	  for (si++; string[si]; si++)
	    if ((string[si] == pattern[pi]) && expr_number_pattern_match(string + si, pattern + pi, all_chars))
	      return 1;
	    else if (!instr(string[si], all_chars))
	      return 0;
	  return 0;
	}
      else if (pattern[pi] != string[si])
	return 0;
    }
  return 1;
}

static char *expr_number_pattern_capture(char **str, char *pattern, char *all_chars)
{
  int si, pi, i;
  char *string = *str;
  
  for (si = 0, pi = 0; pattern[pi]; si++, pi++)
    {
      if (pattern[pi] == '#')
	{
	  pi++;
	  i = si;
	  if (!pattern[pi])
	    {
	      for (; instr(string[si], all_chars); si++);
	      *str = string + si;
	      return str_cpy_n_alloc(string + i, si-i);
	    }
	  for (; string[si]; si++)
	    if ((string[si] == pattern[pi]) && expr_number_pattern_match(string + si, pattern + pi, all_chars))
	      {
		*str = string+si;
		expr_number_pattern_capture(str, pattern+pi, all_chars);
		return str_cpy_n_alloc(string + i, si-i);
	      }
	    else if (!instr(string[si], all_chars))
	      return NULL;
	  return NULL;
	}
      else if (pattern[pi] != string[si])
	return NULL;
    }
  *str = string + si;
  return NULL;
}

