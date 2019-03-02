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

#define ALLOC_C 1
#include <config.h>

#include "preprocessor.h"
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

struct memory_t
{
  struct memory_t *next;
  struct memory_t *previous;
  void *mem;
};

static struct memory_t *extra_mem = NULL;

static struct memory_t *alloc_add(void *mem)
{
  struct memory_t *memory;

  ALLOCATE(struct memory_t, memory, 1);
  memory->next = NULL;
  memory->previous = NULL;
  memory->mem = mem;
  return memory;  
}

static struct memory_t *alloc_local(int size)
{
  void *mem;
  
  ALLOCATE(void, mem, size);
  return alloc_add(mem);
}

static struct memory_t *alloc_find(void *mem)
{
  struct memory_t *memory;

  for (memory = extra_mem; memory; memory = memory->next)
    if (memory->mem == mem)
      return memory;
  return NULL;
}

static void alloc_free(struct memory_t *mem)
{
  free(mem->mem);
  free(mem);
}

static int alloc_realloc(struct memory_t *mem, int size)
{
  REALLOCATE(void, mem->mem, size);
  return 0;
}

void *l_alloc(int size)
{
  struct memory_t *mem;

  if (!(mem = alloc_local(size)))
    ERROR("couldn't allocate %i bytes of memory\n", size);
  mem->next = extra_mem;
  if (extra_mem)
    extra_mem->previous = mem;
  extra_mem = mem;
  return mem->mem;
}

void *l_realloc(void *mem, int size)
{
  struct memory_t *memory;

  if (!(memory = alloc_find(mem)))
    ERROR("internal error\n");
  if (alloc_realloc(memory, size)<0)
    ERROR("internal error\n");
  return memory->mem;
}

void l_dealloc(void *mem)
{
  struct memory_t *memory;
  if (!(memory = alloc_find(mem)))
    {
      WARNING("internal problem\n");
      return;
    }
  if (memory->previous)
    memory->previous->next = memory->next;
  else
    extra_mem = memory->next;
  if (memory->next)
    memory->next->previous = memory->previous;
  alloc_free(memory);
}

void l_dealloc_all()
{
  struct memory_t *mem;
  struct memory_t *next;
  
  for (mem = extra_mem; mem; mem = next)
    {
      next = mem->next;
      alloc_free(mem);
    }
  extra_mem = NULL;
}

int l_add(void *memory)
{
  struct memory_t *mem;

  if (!(mem = alloc_add(memory)))
    ERROR("couldn't add memory to tree\n");
  mem->next = extra_mem;
  if (extra_mem)
    extra_mem->previous = mem;
  extra_mem = mem;
  return 0;
}
