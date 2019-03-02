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

int macro_token_all(char c)
{
  if ((c <= 'z') && (c >= 'a'))
    return 1;
  if ((c <= 'Z') && (c >= 'A'))
    return 1;
  if ((c <= '9') && (c >= '0'))
    return 1;
  if (c == '_')
    return 1;
  return 0;
}

int macro_token_eq(char *t1, char *t2)
{
  for (; macro_token_all(*t1) && macro_token_all(*t2); t1++, t2++)
    if (*t1 != *t2)
      return 0;
  if (macro_token_all(*t1) || macro_token_all(*t2))
    return 0;
  return 1;
}

static struct macro_t *macro_token_find(char *name)
{
  struct macro_search_t *tree;
  if (!name)
    return NULL;
  
  for (tree = macro_tree; macro_token_all(*name); name++)
    if (!(tree = macro_search_get_next(tree, name)))
      return NULL;
  return tree->macro;
}

char *macro_token_begin(char *string)
{
  char instring = 0;
  if (!string)
    return NULL;
  while (*string && (instring || (!macro_token_all(*string))))
    {
      if ((*string == '"') || (*string == '\''))
	{
	  if (instring == *string) instring = 0;
	  else if (!instring) instring = *string;
	}
      else if ((*string == '\\') && instring && string[1]) string++;
      string++;
    }
  if (*string)
    return string;
  return NULL;
}

char *macro_token_end(char *token)
{
  if (!token)
    return NULL;
  while (macro_token_all(*token))
    token++;
  if (*token)
    return token;
  return NULL;
}

// doesn't return NULL on empty string
char *macro_token_end_lit(char *token)
{
  if (!token)
    return NULL;
  while (macro_token_all(*token))
    token++;
  return token;
}

char *macro_token_next(char *token)
{
  return macro_token_begin(macro_token_end(token));
}

#if 0
static int macro_token_len(char *token)
{
  return macro_token_end(token) - token;
}
#endif
