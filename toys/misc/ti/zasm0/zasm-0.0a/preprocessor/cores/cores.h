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

#ifndef CORES_H
#define CORES_H 1
#include <config.h>
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

struct directives_t
{
  char *dir;
  char *(*function)(char *args);
};

struct codes_t
{
  char *code;
  char *(*function)(char *label, char *code, char *args);
};

struct core_t
{
  char *(*preprocess)(char *line);
  struct directives_t *directives;
  struct codes_t *defines;
  struct codes_t *codes;
};

struct core_ll_t
{
  struct core_ll_t *previous;
  struct core_t *core;
};

char *code_macro(char *name, char *code, char *args);
char *code_equ(char *name, char *code, char *args);
char *code_db(char *name, char *code, char *args);
char *code_dw(char *name, char *code, char *args);
char *code_opcode(char *name, char *code, char *args);
char *code_zbit(char *name, char *code, char *args);
char *code_empty(char *name, char *code, char *args);
char *code_ignore(char *label, char *code, char *args);

char *core_pp_line_default(char *line);
char *core_pp_line_iffalse(char *line);
char *core_pp_line_macro(char *line);

// directives.c
char *dir_org(char *arg);
char *dir_file(char *arg);
char *dir_line(char *arg);
char *dir_page(char *arg);
char *dir_newpage(char *arg);
char *dir_db(char *arg);
char *dir_dw(char *arg);
char *dir_include(char *file);
char *dir_if(char *args);
char *dir_ifdef(char *args);
char *dir_ifndef(char *args);
char *dir_else(char *args);
char *dir_endif(char *args);
char *dir_define(char *name);
char *dir_undef(char *args);
char *dir_ignore(char *args);

#ifndef DEFAULT_C
extern struct core_t core_default;
extern struct directives_t core_dir_default[];
extern struct codes_t core_defines_default[];
extern struct codes_t core_codes_default[];
#endif
#ifndef IFFALSE_C
extern struct core_t core_iffalse;
extern struct directives_t core_dir_iffalse[];
#endif
#ifndef ELSIFFALSE_C
extern struct core_t core_elsiffalse;
extern struct directives_t core_dir_elsiffalse[];
#endif
#ifndef CORES_C
extern int dir_if_depth;
extern int dir_if_false_depth;
#endif
#ifndef MACRO_C
extern char *code_macro_name;
extern int code_macro_argc;
extern char **code_macro_args;
extern char *code_macro_text;
extern int code_macro_depth;
extern struct core_t core_macro;
#endif
#endif
