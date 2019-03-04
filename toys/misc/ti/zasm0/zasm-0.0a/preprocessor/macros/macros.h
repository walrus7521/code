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

#ifndef MACROS_H
#define MACROS_H 1
#include <config.h>
#define MACRO_UPPER(C) (((C)<='Z')&&((C)>='A'))
#define MACRO_LOWER(C) (((C)<='z')&&((C)>='a'))
#define MACRO_NUMBER(C) (((C)<='9')&&((C)>='0'))
#define MACRO_GET_CHAR(C) (MACRO_NUMBER(C)?(C-'0'):(MACRO_UPPER(C)?(C-'A'+10):(MACRO_LOWER(C)?(C-'a'+36):(((C)=='_')?62:-1))))

enum
  {
    MACRO_SEARCH_LARGE,
    MACRO_SEARCH_SMALL,
    MACRO_SEARCH_COUNT
  };

struct macro_t
{
  char *name;
  int argc;
  char **args;
  char *text;
};

struct macro_search_t
{
  int type;
  struct macro_search_t *parent;
  struct macro_t *macro;
};

// used form 48 children upwards
struct macro_search_large_t
{
  struct macro_search_t head;
  struct macro_search_t *children[63];    // only 63 chars are permitted: 'a'-'z','A'-'Z','0'-'9','_'
};

// used form 2 to 47 children
struct macro_search_small_t
{
  struct macro_search_t head;
  int child_count;
  char *mapping;                         // "acb0d3" means that 'a' has the first entry, 'c' the second, ...
  struct macro_search_t **children;
};

static struct macro_search_t *macro_tree = NULL;

// search.c
static int macro_search_replace(struct macro_search_t *tree,
				struct macro_search_t *orig,
				struct macro_search_t *new);
static struct macro_search_t *macro_search_make_small(struct macro_t *macro, 
						      struct macro_search_t **children, 
						      char *mapping, 
						      int child_count);
static struct macro_search_t *macro_search_make_small_tree(struct macro_t *macro, char *name);
static struct macro_search_t *macro_search_get_next(struct macro_search_t *tree, char *name);
static struct macro_search_t *macro_search_find(struct macro_search_t *tree, char *name);
static int macro_search_child_count(struct macro_search_t *tree);
static void macro_search_free(struct macro_search_t *tree);
static void macro_search_unlink(struct macro_search_t *tree, struct macro_search_t *node);
static void macro_search_del_intern(struct macro_search_t *tree);
// token
int macro_token_all(char c);
int macro_token_eq(char *t1, char *t2);
static struct macro_t *macro_token_find(char *name);
char *macro_token_begin(char *string);
char *macro_token_end(char *token);
char *macro_token_next(char *token);
// subs.c
static char *macro_get_args(char *string, char ***args_p, int argc_p);
static char *macro_subs_intern(struct macro_t *macro, char **args);
// ../expr.c
static int macro_print_intern(struct macro_search_t *tree, int depth);
static int macro_add_intern(struct macro_t *macro, struct macro_search_t *tree, char *name);
static void macro_free(struct macro_t *macro);
static struct macro_t *macro_make_macro(char *name, int argc, char **args, char *text);

#endif
