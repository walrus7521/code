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

#define OPCODE_C 1
#include <config.h>
#include "assembler.h"
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

struct opcode_t *make_opcode(char size, char *code, int type, char *arg1, char *arg2, unsigned short int addr)
{
  struct opcode_t *retval;
  if (!(retval = (struct opcode_t *)malloc(sizeof(struct opcode_t))))
    return NULL;
  retval->size = size;
  retval->code = str_cpy_alloc(code); // COPY !! (original mem is freed later on, before main use)
  if (!(retval->code))
    return NULL;
  retval->type = type;
  retval->arg1 = str_cpy_alloc(arg1); // COPY !!
  if (arg1 && !(retval->arg1))
    return NULL;
  retval->arg2 = str_cpy_alloc(arg2); // COPY !!
  if (arg2 && !(retval->arg2))
    return NULL;
  retval->address = addr;
  retval->pos_line = pos_line;
  retval->pos_file = pos_file;
  return retval;
}

struct new_page_t *make_new_page(char page)
{
  struct new_page_t *retval;
  if (!(retval = (struct new_page_t *)malloc(sizeof(struct new_page_t))))
    return NULL;
  retval->page = page;
  retval->type = Z80_TYPE_NEW_PAGE;
  retval->next = NULL;
  return retval;
}
