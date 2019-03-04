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

#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H 1
#include <config.h>
#ifdef STDC_HEADERS
#include <stdio.h>
#endif
#include "cores/cores.h"
#include "debug/debug.h"

#define chr_upcase(C) ((((C)>='a')&&((C)<='z'))?C-'a'+'A':C)
#define chr_case_eq(C1,C2) ((chr_upcase(C1)==chr_upcase(C2))?1:0)

struct number_t
{
  int type;                // TYPE_NUM
  char *str;
  int (*value)(char *);
  char *(*print)(char *);
};
// options.c
int parse_option(char *op);
// alloc.c
void *l_alloc(int size);
void *l_realloc(void *mem, int size);
void l_dealloc(void *mem);
void l_dealloc_all(void);
int l_add(void *mem);
// macros.c
int macro_defined(char *name);
int macro_add(char *name, int argc, char **args, char *text);
int macro_del(char *name);
int macro_print(void);
char *macro_def_get_args(char *begin, char ***args_p, int *argc_p, char end_char);
char *macro_substitute(char *name, int argc, char **args);
char *macro_substitute_all(char *string);
char *macro_substitute_all_once(char *string);
// macros/token.c
int macro_token_all(char c);
int macro_token_eq(char *t1, char *t2);
char *macro_token_begin(char *string);
char *macro_token_end(char *token);
char *macro_token_end_lit(char *token);
char *macro_token_next(char *token);
// token.c
int instr(char c, char *str);
int instr_index(char c, char *str);
int token_eq(char *str1, char *str2, char *delims);
int token_eq_case(char *str1, char *str2, char *delims);
char *token_begin(char *string, char *delims);
char *token_begin_lit(char *string, char *delims);
char *token_end(char *string, char *delims);
char *token_next(char *string, char*delims);
char *token_get(char **stringp, char *delims);
// expr.c
int expr_calculate(char *expr);
int expr_calculate_begin(char **expr);
char *expr_print(char *expr);
char *expr_print_begin(char **expr);
// string.c
char *string_interpolate(char *str, char instring, int *cc);
int string_match_second(char *str1, char *str2);
char *string_substitute_l(char *in, char *what, int w_l, char *by);
char *strcat4(char *str1, char *str2, char *str3, char *str4);
char *strcat3(char *str1, char *str2, char *str3);
char *strcat3_realloc(char *str1, char *str2, char *str3);
char *strcat2(char *str1, char *str2);
char *strcat2_realloc(char *str1, char *str2);
char *str_cpy_alloc(char *str);
char *l_str_cpy_alloc(char *str);
char *str_cpy_n_alloc(char *str, int l);
char *fgetline(FILE *stream);
// pattern.c
int patcasetest(char *str, char *pat);
char *patcasecapture(char *str, char *pat);
// preprocessor.c
#ifndef PREPROCESSOR_C
extern FILE *outfile;
extern char **include_path;
extern char *include_path_default[];
extern char *current_path;
#endif
int main(int argc, char *argv[]);
int preprocess_file(FILE *file);
// cores.c
int core_activate(struct core_t *new_core);
int core_deactivate();
char *comments_remove(char *line);
char *preprocess(char *line);
char *directives(char *dir);
char *codes(char *label);
char *defines(char *label);
// path.c
char *find_in_path(char **path, char *file);
char *get_path(char *path);
#endif
