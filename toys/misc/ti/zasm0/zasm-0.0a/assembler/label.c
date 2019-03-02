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

#define LABEL_C
#include <config.h>
#include "assembler.h"
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif

struct label_t *resolve_label(char *name)
{
  struct label_t *label = NULL;
  for (label = symtable; label; label = label->next)
    {
      if (strcmp(label->name, name)==0)
	{
	  DEBUG("label \"%s\" = %i\n", label->name, label->address);
	  return label;
	}
    }
  ERROR("unresolved label: %s\n", name);
  return NULL;
}

struct label_t *make_label(char *name, unsigned short int address, char page)
{
  struct label_t *retval;
  if (!(retval = (struct label_t *)malloc(sizeof(struct label_t))))
    return NULL;
  retval->name = name;
  retval->address = address;
  retval->page = page;
  return retval;
}
