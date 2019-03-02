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

#define PATTERN_C 1
#include <config.h>
#include "preprocessor.h"

// match a string against a simple pattern (case is ignored)
int patcasetest(char *str, char *pat)
{
  int si, pi; // indices

  if ((str == NULL) && (pat == NULL))
    return 1;
  else if ((str == NULL) || (pat == NULL))
    return 0;
  
  for (si = 0, pi = 0;pat[pi]; si++, pi++)
    {
      if (pat[pi] == '*')
	{
	  if (!pat[pi+1])
	    return 1;
	  for (pi++;str[si];si++)
	    if ((chr_case_eq(str[si],pat[pi])) && (patcasetest(str+si,pat+pi)))
	      return 1;
	  return 0;
	}
      else if (!chr_case_eq(str[si],pat[pi]))
	return 0;
    }
  if (str[si] == 0)
    return 1;
  else
    return 0;
}

// return the string that represents the wildcard
char *patcasecapture(char *str, char *pat)
{
  int si, pi, wi; // indices

  if ((str == NULL) || (pat == NULL))
    return NULL;
  
  for (si = 0, pi = 0;pat[pi]; si++, pi++)
    {
      if (pat[pi] == '*')
	{
	  if (!pat[pi+1])
	    return str+si;
	  wi = si;
	  for (pi++;str[si];si++)
	    if ((chr_case_eq(str[si],pat[pi])) && (patcasetest(str+si,pat+pi)))
	      {
		str[si] = 0;
		return str+wi;
	      }
	  return NULL;
	}
      else if (!chr_case_eq(str[si],pat[pi]))
	return NULL;
    }
  return NULL;
}
