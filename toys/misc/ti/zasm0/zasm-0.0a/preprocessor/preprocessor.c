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

#define PREPROCESSOR_C 1
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

char *current_path = NULL;

char *include_path_default[] =
  {
    "",
    NULL
  };

char **include_path = include_path_default;

FILE *outfile = NULL;

// always to outfile
int preprocess_file(FILE *file)
{
  char *line;
  char *ppline;

  while (!feof(file))
    {
      if (!(line = fgetline(file)))
	{
	  if (feof(file))
	    break;
	  else
	    ERROR("couldn't fetch a line form file\n");
	}

      if (!(ppline = preprocess(line)))
	ERROR("unknown fatal error\n");
      if (*ppline)
	fprintf (outfile, "%s\n", ppline);
      free(line);
      l_dealloc_all();
    }  
  return 0;
}

int main(int argc, char *argv[])
{
  int i;

  outfile = stdout;

  debug_file = NULL;
  warning_file = stderr;
  error_file = stderr;
  current_path = str_cpy_alloc("");

  for (i = 1; i < argc; i++)
    {
      if (parse_option(argv[i])<0)
	ERROR("invalid option: \"%s\"\n", argv[i]);
    }

  if (outfile != stdout)
    if (fclose(outfile))
      ERROR("I/O error\n");

  return 0;
}
