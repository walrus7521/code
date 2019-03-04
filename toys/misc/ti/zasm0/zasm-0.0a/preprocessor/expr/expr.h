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

#ifndef EXPR_H
#define EXPR_H 1
#include <config.h>
// expression types
enum
{
  EXPR_TYPE_EXPR,
  EXPR_TYPE_NUM
};

// associativity types: with other functions of the same precedence level:
// a + b - c means (a + b) - c thus '-' is left associative
// all functions of the same precedence level should be of the same associativity
enum
{
  EXPR_ASSOC_LEFT,
  EXPR_ASSOC_RIGHT
};

struct expr_t
{
  int type;                // TYPE_EXPR
  int argc;
  struct expr_t **args;
  int (*calculate)(int *args);
  char *(*print)(char **args);
};

struct precedence_t
{
  struct operator_t *ops;
  int assoc;
};

struct operator_t
{
  char *pattern;
  int (*calculate)(int *);
  char *(*print)(char **);
};

struct numbertype_t
{
  char *pattern;
  char *allowed_chars;
  int (*value)(char *str);
  char *(*print)(char *str);
};

// expr.c
static struct expr_t *expr_interpr(char **string, int level);
static struct expr_t *expr_make_expr(struct expr_t **args, int argc, int (*calc)(int *), char *(*print)(char **));
static struct number_t *expr_make_number(char *string, int (*value)(char *), char *(*print)(char *));
static char *expr_print_intern(struct expr_t *expr);
static int expr_calc_intern(struct expr_t *expr);
static void expr_free(struct expr_t *expr);
// pattern.c
static int expr_pattern_match(char **string, char *pat,
			      struct expr_t **args, struct expr_t *arg1,
			      char *after_arg1, int assoc, int level);
static int expr_number_pattern_match(char *string, char *pattern, char *all_chars);
static char *expr_number_pattern_capture(char **str, char *pattern, char *all_chars);
#endif
