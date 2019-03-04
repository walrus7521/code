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

#define STRING_C 1
#include <config.h>
#include "preprocessor.h"

#ifdef STDC_HEADERS
#include <stdio.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif

#define CHAR_OCT(C) ((((C)<='7')&&((C)>='0'))?(C)-'0':0)
#define CHAR_DEC(C) ((((C)<='9')&&((C)>='0'))?(C)-'0':0)
#define CHAR_HEX_U(C) ((((C)<='F')&&((C)>='A'))?(C)-'A'+10:0)
#define CHAR_HEX_L(C) ((((C)<='f')&&((C)>='a'))?(C)-'a'+10:CHAR_HEX_U(C))
#define CHAR_HEX(C) ((((C)<='9')&&((C)>='0'))?(C)-'0':CHAR_HEX_L(C))

char *string_interpolate(char *str, char instring, int *cc)
{
  int si, di;
  char c;

  for (si = 0, di = 0; str[si] != instring; si++, di++)
    {
      if (!str[si]) ERROR("unterminated string\n")
      else if (str[si] == '\\')
	{
	  switch (str[si+1])
	    {
	    case 0:
	      break;
	    case 'n':
	      si++;
	      str[si] = '\n';
	      break;
	    case 't':
	      si++;
	      str[si] = '\t';
	      break;
	    case 'r':
	      si++;
	      str[si] = '\r';
	      break;
	    case 'e':
	      si++;
	      str[si] = '\e';
	      break;
	    case 'f':
	      si++;
	      str[si] = '\f';
	      break;
	    case 'a':
	      si++;
	      str[si] = '\a';
	      break;
	    case '0':
	    case 'o':
	      c = 64*CHAR_OCT(str[si+2]) + 8*CHAR_OCT(str[si+3]) + CHAR_OCT(str[si+4]);
	      si += 4;
	      str[si] = c;
	      break;
	    case 'x':
	      c = 16*CHAR_HEX(str[si+2]) + CHAR_HEX(str[si+3]);
	      si += 3;
	      str[si] = c;
	      break;
	    case 'd':
	      c = 100*CHAR_DEC(str[si+2]) + 10*CHAR_DEC(str[si+3]) + CHAR_DEC(str[si+4]);
	      si += 4;
	      str[si] = c;
	      break;
	    default:
	      si++;
	    }
	}
      str[di] = str[si];
    }
  str[di] = 0;
  if (cc)
    *cc = di;
  return str + si + 1;
}

// faster version of `strncmp(str1, str2, strlen(str2)) == 0`
int string_match_second(char *str1, char *str2)
{
  int i;
  for (i = 0;str2[i]; i++)
    if (str1[i] != str2[i])
      return 0;
  return 1;
}

char *string_substitute_l(char *in, char *what, int w_l, char *by)
{
  int i,j, b_l, i_l;
  char *dest;

  b_l = strlen(by);
  i_l = strlen(in);
  if (!(dest = (char *)l_alloc((i_l-w_l+b_l+1)*sizeof(char))))
    ERROR("internal error\n");
  for (i = 0, j = 0; i <= i_l; i++, j++)
    {
      dest[j] = in[i];
      if (in+i == what)
	{
	  strcpy(dest + j, by);
	  i += w_l - 1;
	  j += b_l - 1;
	}
    }
  return dest;
}

char *str_cpy_alloc(char *str)
{
  char *dest = NULL;
  if (!str)
    return NULL;
  ALLOCATE(char, dest, strlen(str)+1);
  return strcpy(dest, str);
}

char *l_str_cpy_alloc(char *str)
{
  char *dest = NULL;
  if (!str)
    return NULL;
  dest = (char *)l_alloc(sizeof(char)*(strlen(str)+1));
  if (!dest)
    ERROR("internal error\n");
  return strcpy(dest, str);
}

char *str_cpy_n_alloc(char *str, int l)
{
  char *dest = NULL;
  if (!str)
    return NULL;
  ALLOCATE(char, dest, l+1)
  dest[l] = 0;
  return strncpy(dest, str, l);
}

char *strcat4(char *str1, char *str2, char *str3, char *str4)
{
  char *dest = NULL;
  int sl1 = strlen(str1);
  int sl2 = strlen(str2);
  int sl3 = strlen(str3);
  int sl4 = strlen(str4);
  if (!str1) return NULL;
  if (!str2) return NULL;
  if (!str3) return NULL;
  if (!str4) return NULL;
  ALLOCATE(char, dest, sl1+sl2+sl3+sl4+1);
  strncpy(dest, str1, sl1);
  strncpy(dest+sl1, str2, sl2);
  strncpy(dest+sl1+sl2, str3, sl3);
  strncpy(dest+sl1+sl2+sl3, str4, sl4);
  dest[sl1+sl2+sl3+sl4] = 0;
  return dest;
}

char *strcat3(char *str1, char *str2, char *str3)
{
  char *dest = NULL;
  int sl1 = strlen(str1);
  int sl2 = strlen(str2);
  int sl3 = strlen(str3);
  if (!str1) return NULL;
  if (!str2) return NULL;
  if (!str3) return NULL;
  ALLOCATE(char, dest, sl1+sl2+sl3+1);
  strncpy(dest, str1, sl1);
  strncpy(dest+sl1, str2, sl2);
  strncpy(dest+sl1+sl2, str3, sl3);
  dest[sl1+sl2+sl3] = 0;
  return dest;
}

char *strcat3_realloc(char *str1, char *str2, char *str3)
{
  int sl1;
  int sl2 = strlen(str2);
  int sl3 = strlen(str3);

  if (!str1) sl1 = 0; else sl1 = strlen(str1);
  if (!str2) return NULL;
  if (!str3) return NULL;
  REALLOCATE(char, str1, sl1+sl2+sl3+1);
  strncpy(str1+sl1, str2, sl2);
  strncpy(str1+sl1+sl2, str3, sl3);
  str1[sl1+sl2+sl3] = 0;
  return str1;
}

char *strcat2(char *str1, char *str2)
{
  char *dest = NULL;
  int sl1 = strlen(str1);
  int sl2 = strlen(str2);
  if (!str1) return NULL;
  if (!str2) return NULL;
  ALLOCATE(char, dest, sl1+sl2+1);
  strncpy(dest, str1, sl1);
  strncpy(dest+sl1, str2, sl2);
  dest[sl1+sl2] = 0;
  return dest;
}

char *strcat2_realloc(char *str1, char *str2)
{
  int sl1;
  int sl2 = strlen(str2);
  if (!str1) sl1 = 0; else sl1 = strlen(str1);
  if (!str2) return NULL;
  REALLOCATE(char, str1, sl1+sl2+1);
  strncpy(str1+sl1, str2, sl2);
  str1[sl1+sl2] = 0;
  return str1;
}

// read in and allocate a line safely
char *fgetline(FILE *stream)
{
  static int ll = 32;
  static char *line = NULL; // allocated in blocks of 32 bytes (normally 32 bytes should be enough for a line)
  char *retval = NULL;
  int i = 0;
  
  pos_line_begin = pos_line_end + 1;
  pos_line_end++;

  if (!line)
    ALLOCATE(char, line, ll);

  if (!(fgets(line, ll, stream)))
    return NULL;

  for (i = 0; line[i] != '\n'; i++)
    {
      if ((line[i] == 0)&&(feof(stream)))
	break;
      else if (i == ll-1)
	{
	  if (line[i] != 0)
	    ERROR("I/O error: fgets acts strange");
	  ll += 32;
	  REALLOCATE(char, line, ll);
	  if (!(fgets(line + i, 33, stream))) // 33 = 32 (new) + 1 (terminating null)
	    {
	      if (feof(stream))
		break;
	      ERROR("I/O error\n");
	    }
	  i--; // check first char read
	}
      else if (line[i] == '\\')
	{
	  if ((line[i+1] == '\n') || ((line[i+1] == '\r') && (line[i+2] == '\n'))) // UNIX and DOS format
	    {
	      pos_line_end++;
	      
	      if (!(fgets(line+i, ll-i, stream)))
		ERROR("I/O error or premature end of file\n");
	      i--; // check first char read
	    }
	  else if (!line[i+1])
	    {
	      if (feof(stream))
		{
		  i++;
		  break;
		}
	      if (i == ll-2)
		{ // read further, so I can do my work
		  ll += 32;
		  REALLOCATE(char, line, ll);
		  if (!(fgets(line + i + 1, 33, stream))) // 33 = 32 (new) + 1 (terminating null)
		    {
		      if (feof(stream))
			{
			  i++;
			  break;
			}
		      ERROR("I/O error\n");
		    }
		  i--; // recheck '\\'
		}
	      else
		ERROR("I/O error or file contains null chars (binary?)\n"); // not eof nor end of string ???
	    }
	  else if ((!line[i+2]) && (line[i+1] == '\r')) //
	    {
	      if (feof(stream))
		{
		  i++;
		  break;
		}
	      if (i == ll-3)
		{ // read further, so I can do my work
		  ll += 32;
		  REALLOCATE(char, line, ll);
		  if (!(fgets(line + i + 1, 33, stream))) // 33 = 32 (new) + 1 (terminating null)
		    {
		      if (feof(stream))
			{
			  i++;
			  break;
			}
		      ERROR("I/O error\n");
		    }
		  i--; // recheck '\\'
		}
	      else
		ERROR("I/O error or file contains null chars (binary?)\n");
	    }
	  else if (line[i+1] == '\\')
	    i++; // safely ignore next '\\'
	}
    }
  if ((i>0) && (line[i-1] == '\r'))
    i--;
  line[i] = 0;
  ALLOCATE(char, retval, i+1);

  return strcpy(retval, line);
}
