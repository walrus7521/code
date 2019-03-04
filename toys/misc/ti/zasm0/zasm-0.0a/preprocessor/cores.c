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

#define CORES_C
#include <config.h>
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "preprocessor.h"
#include "cores/cores.h"

struct core_t *core = &core_default;
struct core_ll_t *core_ll = NULL;

int dir_if_depth = 0;
int dir_if_false_depth;

int core_activate(struct core_t *new_core)
{
  struct core_ll_t *ll;
  ALLOCATE(struct core_ll_t, ll, 1);
  ll->previous = core_ll;
  ll->core = core;
  core_ll = ll;
  core = new_core;
  return 0;
}

int core_deactivate()
{
  struct core_ll_t *ll;
  ll = core_ll;
  if (!ll)
    ERROR("internal error\n");
  core = ll->core;
  core_ll = ll->previous;
  free(ll);
  return 0;
}

char *comments_remove(char *line)
{
  int i;
  char instring = 0;

  for (i = 0; line[i]; i++)
    {
      if ((line[i] == '"') || (line[i] == '\''))
	{
	  if (!instring) instring = line[i];
	  else if (instring == line[i]) instring = 0;
	}
      else if ((line[i] == '\\') && instring && line[i+1]) i++;
      else if ((line[i] == ';') && (!instring))
	{
	  line[i] = 0;
	  break;
	}
    }
  return line;
}

char *preprocess(char *line)
{
  return core->preprocess(line);
}

char *directives(char *str)
{
  int i;
  char *dir;
  char *args;

  dir = token_begin(str, " \t");
  if (!dir)
    return str;
  args = token_next(dir, " \t");
  for (i = 0; core->directives[i].dir; i++)
    {
      if (token_eq_case(core->directives[i].dir, dir, " \t"))
	return core->directives[i].function(args);
    }
  return str;
}

char *codes(char *label)
{
  int i;
  char *code;
  char *args;
  
  if (!(code = token_next(label, " \t:")))
    code = "";
  args = token_next(code, " \t");
  for (i = 0; core->codes[i].code; i++)
    {
      if (token_eq_case(core->codes[i].code, code, " \t"))
	return core->codes[i].function(label, code, args);
    }
  ERROR("code \"%s\" is not permitted here\n", code);
}

char *defines(char *label)
{
  int i;
  char *code;
  char *args;
  
  if (!(code = token_next(label, " \t:")))
    code = "";
  args = token_next(code, " \t");
  for (i = 0; core->defines[i].code; i++)
    {
      if (token_eq_case(core->defines[i].code, code, " \t"))
	return core->defines[i].function(label, code, args);
    }
  return label;
}

char *code_ignore(char *label, char *code, char *args){return "";}
