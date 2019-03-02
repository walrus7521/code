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

#define STRING_C 1
#include <config.h>
#include "assembler.h"

#ifdef STDC_HEADERS
#include <stdio.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif

static char *eval_expr_intern(char *expr, int *val, int addr)
{
  int arg1 = 0, arg2 = 0;
  int i = 0;
  struct label_t *label = NULL;
  char *member = NULL;

  DEBUG("eval_expr: expr = \"%s\"\n",expr);
  switch (expr[0])
    {
    case '^':
      expr = eval_expr_intern(expr+1, &arg1, addr);
      if (!expr) return NULL;
      *val =  ~arg1;
      return expr;
    case '|':
      expr = eval_expr_intern(expr+1, &arg1, addr);
      if (!expr) return NULL;
      expr = eval_expr_intern(expr+1, &arg2, addr);
      if (!expr) return NULL;
      *val =  arg1 | arg2;
      return expr;
    case '&':
      expr = eval_expr_intern(expr+1, &arg1, addr);
      if (!expr) return NULL;
      expr = eval_expr_intern(expr+1, &arg2, addr);
      if (!expr) return NULL;
      *val =  arg1 & arg2;
      return expr;
    case '<':
      expr = eval_expr_intern(expr+1, &arg1, addr);
      if (!expr) return NULL;
      expr = eval_expr_intern(expr+1, &arg2, addr);
      if (!expr) return NULL;
      *val =  arg1 << arg2;
      return expr;
    case '>':
      expr = eval_expr_intern(expr+1, &arg1, addr);
      if (!expr) return NULL;
      expr = eval_expr_intern(expr+1, &arg2, addr);
      if (!expr) return NULL;
      *val =  arg1 >> arg2;
      return expr;
    case '-':
      expr = eval_expr_intern(expr+1, &arg1, addr);
      if (!expr) return NULL;
      expr = eval_expr_intern(expr+1, &arg2, addr);
      if (!expr) return NULL;
      *val =  arg1 - arg2;
      return expr;
    case '+':
      expr = eval_expr_intern(expr+1, &arg1, addr);
      if (!expr) return NULL;
      expr = eval_expr_intern(expr+1, &arg2, addr);
      if (!expr) return NULL;
      *val =  arg1 + arg2;
      return expr;
    case '*':
      expr = eval_expr_intern(expr+1, &arg1, addr);
      if (!expr) return NULL;
      expr = eval_expr_intern(expr+1, &arg2, addr);
      if (!expr) return NULL;
      *val =  arg1 * arg2;
      return expr;
    case '/':
      expr = eval_expr_intern(expr+1, &arg1, addr);
      if (!expr) return NULL;
      expr = eval_expr_intern(expr+1, &arg2, addr);
      if (!expr) return NULL;
      if (arg2 == 0){ERROR("division by zero\n");return 0;}
      *val = arg1 / arg2;
      return expr;
    case '%':
      expr = eval_expr_intern(expr+1, &arg1, addr);
      if (!expr) return NULL;
      expr = eval_expr_intern(expr+1, &arg2, addr);
      if (!expr) return NULL;
      if (arg2 == 0){ERROR("division by zero\n");return 0;}
      *val = arg1 % arg2;
      return expr;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      for (i = 0; (expr[i] != ':') && (expr[i]); i++);
      expr[i] = 0;
      *val = atoi(expr);
      return expr+i;
    case '$':
      if ((!expr[1]) || (expr[1] == ':'))
	{
	  *val = addr;
	  return expr+1;
	}
    default:
      for (i = 0; (expr[i] != ':') && (expr[i]); i++)
	{
	  if ((!member) && (expr[i] == '.'))
	    {
	      member = expr+i+1;
	      expr[i] = 0;
	    }
	};
      expr[i] = 0;
      label = resolve_label(expr);
      if (!label) return NULL;
      if (!member)
	*val = label->address;
      else if (0 == strcasecmp(member, "page"))
	*val = label->page;
      else if (0 == strcasecmp(member, "address"))
	*val = label->address; // for the ones that don't like defaults
      return expr+i;
    }
}

// tidy form: no spaces, all numbers in decimal, integers
// allowed operations: +,-,*,/,% in prefix notation
// example: *+2,5,/6,3 gives (2+5)*(6/3) = 14
// correct syntax is assumed (checked in preprocessor)
int eval_expr(char *expr, int addr)
{
  int retval = 0;
  if (!eval_expr_intern(expr, &retval, addr))
    return 0;
  return retval;
}

char *str_cpy_alloc(char *str)
{
  char *dest = NULL;
  if (!str)
    return NULL;
  dest = (char *)malloc(sizeof(char)*(strlen(str)+1));
  if (!dest)
    return NULL;
  return strcpy(dest, str);
}

// read in and allocate a line safely
char *fgetline(FILE *stream)
{
  static int ll = 32;
  static char *line = NULL; // allocated in blocks of 32 bytes (normally 32 bytes should be enough for a line)
  char *retval = NULL;
  int i = 0;

  if ((!line)&&(!(line = (char *)malloc(ll*sizeof(char)))))
    return NULL;

  if (!(fgets(line, ll, stream)))
    return NULL;

  for (i = 0; line[i] != '\n'; i++)
    {
      if ((line[i] == 0)&&(feof(stream)))
	break;
      if (i == ll-1)
	{
	  if (line[i] != 0)
	    return NULL; // fgets doesn't comply to its man page, stop to prevent problems
	  ll += 32;
	  line = (char *)realloc(line, ll*sizeof(char));
	  if (!(fgets(line + i, 33, stream))) // 33 = 32 (new) + 1 (terminating null)
	    {
	      if (feof(stream))
		break;
	      return NULL;
	    }
	  i--;
	}
    }
  line[i] = 0;
  if (!(retval = (char *)malloc((i+1)*sizeof(char))))
    return NULL;

  return strcpy(retval, line);
}
