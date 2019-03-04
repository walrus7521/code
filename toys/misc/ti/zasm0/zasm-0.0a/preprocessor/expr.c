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

#define EXPR_C 1
#include <config.h>

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef STDC_HEADERS
#include <stdio.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif
#include "preprocessor.h"

#include "expr/expr.h"
#define int_error 0x7fffffff

#include "expr/default.c"
#include "expr/pattern.c"

static struct expr_t *expr_make_expr(struct expr_t **args, int argc, int (*calc)(int *), char *(*print)(char **))
{
  struct expr_t **ops;
  struct expr_t *retval;
  int i;

  ALLOCATE(struct expr_t *, ops, argc);
  ALLOCATE(struct expr_t, retval, 1);
  for (i = 0; i<argc; i++)
    ops[i] = args[i];
  retval->type = EXPR_TYPE_EXPR;
  retval->args = ops;
  retval->argc = argc;
  retval->calculate = calc;
  retval->print = print;
  return retval;
}

static struct number_t *expr_make_number(char *string, int (*value)(char *), char *(*print)(char *))
{
  struct number_t *retval;

  ALLOCATE(struct number_t, retval, 1);
  retval->type = EXPR_TYPE_NUM;
  retval->str = string;
  retval->value = value;
  retval->print = print;
  return retval;
}

static void expr_free_number(struct number_t *number)
{
  free(number->str);
  free(number);
}

static struct  expr_t *expr_interpr(char **string, int level)
{
  int i,j;
  char *number;
  char *after_arg1;
  char *temp;
  struct expr_t *arg1;
  struct expr_t *args[3]; // max arg count + 1
  struct operator_t *ops = prec_levels[level].ops;

  // operator?
  if (ops)
    {
      after_arg1 = token_begin(*string, " \t");
      arg1 = expr_interpr(&after_arg1, level+1);
      after_arg1 = token_begin(after_arg1, " \t");
    find_operator:
      for (i = 0; ops[i].pattern; i++)
	{
	  if (!expr_pattern_match(string, ops[i].pattern, args, arg1, after_arg1, prec_levels[level].assoc, level))
	    continue;
	  for (j = 0; args[j]; j++);
	  switch (prec_levels[level].assoc)
	    {
	    case EXPR_ASSOC_LEFT:
	      arg1 = expr_make_expr(args, j, ops[i].calculate, ops[i].print);
	      after_arg1 = *string;
	      if (!arg1)
		return NULL;
	      goto find_operator;
	    case EXPR_ASSOC_RIGHT:
	      return expr_make_expr(args, j, ops[i].calculate, ops[i].print);
	    default:
	      return NULL;
	    }
	}
      *string = after_arg1;
      return arg1;
    }
  // number?
  after_arg1 = *string;
  arg1 = NULL;
  for (i = 0; numbertypes[i].pattern; i++)
    {
      if (expr_number_pattern_match(*string, numbertypes[i].pattern, numbertypes[i].allowed_chars))
	{
	  temp = *string;
	  if (!(number = expr_number_pattern_capture(&temp, numbertypes[i].pattern, numbertypes[i].allowed_chars)))
	    return NULL;
	  if (temp <= after_arg1)
	    continue;
	  if (arg1)
	    expr_free_number((struct number_t *)arg1);
	  arg1 = (struct expr_t *)expr_make_number(number, numbertypes[i].value, numbertypes[i].print);
	  after_arg1 = temp;
	}
    }
  *string = after_arg1;
  return arg1;
}

static char *expr_print_intern(struct expr_t *expr)
{
  int i;
  char **args;
  char *val;
  if (expr->type == EXPR_TYPE_NUM)
    {
      val = ((struct number_t *)expr)->print(((struct number_t *)expr)->str);
      return val;
    }

  ALLOCATE(char *, args, expr->argc);
  for (i = 0; i < expr->argc; i++)
    args[i] = expr_print_intern(expr->args[i]);
  val = expr->print(args);
  for (i = 0; i < expr->argc; i++)
    free (args[i]);
  free(args);
  return val;
}

static int expr_calc_intern(struct expr_t *expr)
{
  int i;
  int *args;
  int val;
  if (expr->type == EXPR_TYPE_NUM)
    {
      return ((struct number_t *)expr)->value(((struct number_t *)expr)->str);
    }
  ALLOCATE(int, args, expr->argc);
  for (i = 0; i < expr->argc; i++)
    args[i] = expr_calc_intern(expr->args[i]);
  val = expr->calculate(args);
  free(args);
  return val;
}

static void expr_free(struct expr_t *expr)
{
  int i;
  if (expr->type == EXPR_TYPE_NUM)
    free (((struct number_t *)expr)->str);
  else
    {
      for (i = 0; i < expr->argc; i++)
	expr_free(expr->args[i]);
      free(expr->args);
    }
  free(expr);
}

int expr_calculate(char *expr)
{
  struct expr_t *ex;
  int val;

  if (!(ex = expr_interpr(&expr, 0)))
    return int_error;
  if (token_begin(expr, " \t"))
    return int_error; // not the complete expr is valid
  val = expr_calc_intern(ex);
  expr_free(ex);
  return val;
}

int expr_calculate_begin(char **expr)
{
  struct expr_t *ex;
  int val;

  if (!(ex = expr_interpr(expr, 0)))
    return int_error;
  *expr = token_begin(*expr, " \t");
  val = expr_calc_intern(ex);
  expr_free(ex);
  return val;
}

char *expr_print(char *expr)
{
  struct expr_t *ex;
  char *val;

  if (!(ex = expr_interpr(&expr, 0)))
    return NULL;
  if (token_begin(expr, " \t"))
    return NULL; // not the complete expr is valid
  val = expr_print_intern(ex);
  expr_free(ex);
  return val;
}

// interpretes the largest part at the beginning of the string that can be considered as an expression
char *expr_print_begin(char **expr)
{
  struct expr_t *ex;
  char *val;
  
  if (!(ex = expr_interpr(expr, 0)))
    return NULL;
  *expr = token_begin(*expr, " \t");
  val = expr_print_intern(ex);
  expr_free(ex);
  return val;
}
