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

#define TOKEN_C 1
#include <config.h>
#include "preprocessor.h"

#define LOWER(C) (((C)<='Z') && (((C)>='A'))?(C)-'A'+'a':(C))

int instr(char c, char *str)
{
  if (!str)
    return 0;
  for (;*str;str++)
    if (*str == c)
      return 1;
  return 0;
}

int instr_index(char c, char *str)
{
  int i;
  if (!str)
    return -1;
  for (i = 0;str[i];i++)
    if (str[i] == c)
      return i;
  return -1;
}

int token_eq(char *str1, char *str2, char *delims)
{
  while ((*str1) == (*str2))
    {
      if (instr(*str1, delims) || !(*str1))
	{
	  if (instr(*str2, delims) || !(*str2))
	    return 1;
	  else
	    return 0;
	}
      else if (instr(*str2, delims) || !(*str2))
	return 0;
      str1++;
      str2++;
    }
  if ((instr(*str1, delims) || !(*str1)) && (instr(*str2, delims) || !(*str2)))
    return 1;
  return 0;
}

int token_eq_case(char *str1, char *str2, char *delims)
{
  while (LOWER(*str1) == LOWER(*str2))
    {
      if (instr(*str1, delims) || !(*str1))
	{
	  if (instr(*str2, delims) || !(*str2))
	    return 1;
	  else
	    return 0;
	}
      else if (instr(*str2, delims) || !(*str2))
	return 0;
      str1++;
      str2++;
    }
  if ((instr(*str1, delims) || !(*str1)) && (instr(*str2, delims) || !(*str2)))
    return 1;
  return 0;
}

char *token_begin(char *string, char *delims)
{
  if (!string)
    return NULL;
  while (instr(*string, delims))
    string++;
  if (*string)
    return string;
  else
    return NULL;
}

char *token_begin_lit(char *string, char *delims)
{
  if (!string)
    return NULL;
  while (instr(*string, delims))
    string++;
  return string;
}

char *token_end(char *string, char *delims)
{
  if (!string)
    return NULL;
  while (*string && (!instr(*string, delims)))
    string++;
  if (*string)
    return string;
  else
    return NULL;
}

char *token_next(char *string, char*delims)
{
  string = token_end(string, delims);
  return token_begin(string, delims);
}

// modifies source string !!
// use the above functions as much as possible
char *token_get(char **stringp, char *delims)
{
  char *retval;
  int i = 0;
  if ((!stringp) || (!(*stringp)))
    return NULL;
  retval = token_begin(*stringp, delims);
  while (retval[i] && (!instr(retval[i],delims)))
    i++;

  if (retval[i])
    {
      retval[i] = 0;
      *stringp = retval + i + 1;
      return retval;
    }
  else if (i == 0)
    {
      // no token
      *stringp = NULL;
      return NULL;
    }
  else
    {
      // last token
      *stringp = NULL;
      return retval;
    }
}
