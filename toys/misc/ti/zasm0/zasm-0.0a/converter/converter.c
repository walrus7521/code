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

#define CONVERTER_C 1
#include <config.h>

#include "appsign.h"
#include "debug.h"

#ifdef HAVE_LIBTIFILES
#include <tilp/tifiles.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif
#ifdef STDC_HEADERS
#include <stdio.h>
#endif
#ifdef HAVE_STDLIB_H 
#include <stdlib.h>
#endif

#include <ctype.h>

#define HEX_INT_L(C) ((int)((((C)<='z')&&((C)>='a'))?((C)-'a'+10):0))
#define HEX_INT_U(C) ((int)((((C)<='Z')&&((C)>='A'))?((C)-'A'+10):HEX_INT_L(C)))
#define HEX_INT(C)   ((int)((((C)<='9')&&((C)>='0'))?((C)-'0')   :HEX_INT_U(C)))

// for compatibility with libappsign
unsigned short int *__ctype_b;
void *__builtin_new(int l)
{
  return malloc(l);
}

struct type_t
{
  char *name;
  int ID;
  int (*filter)(int calc_type, int var_type, char *IH_file, char *outfile);
};

struct calc_t
{
  char *name;
  int ID;
  struct type_t *types;
};

struct page_t
{
  int size;
  char *data; // binary
};

struct pages_t
{
  int count;
  struct page_t *pages;
};

struct IH_line_t
{
  int size;
  int address;
  int type;
  char *data;
  int checksum;
};

struct calc_t current_calc = {NULL, 0, NULL};
struct type_t current_type = {NULL, 0, NULL};
char *infile = NULL;
char *outfile = NULL;
char *name;
int typechr = 0;
static char *l_basename(char *filename)
{
  int i, j;
  static char base[8];

  DEBUG_BEGIN("basename(\"%s\")\n", filename);
  i = 0;
  while (((filename[i]<'A') || (filename[i]>'Z')) && ((filename[i]<'a') || (filename[i]>'z')) && filename[i])
    i++;
  if (!filename[i])
    {
      base[0] = 0;
      DEBUG_END("return \"\"\n");
      return base;
    }
  j = 0;
  while ((((filename[i]>='A') && (filename[i]<='Z')) ||
	  ((filename[i]>='a') && (filename[i]<='z')) ||
	  ((filename[i]>='0') && (filename[i]<='9'))) &&
	 j < 7)
    {
      if ((filename[i]>='a') && (filename[i]<='z'))
	base[j] = filename[i] - 'a' + 'A';
      else
	base[j] = filename[i];
      i++; j++;
    }
  base[j] = 0;
  DEBUG_END("return \"%s\"\n", base);
  return base;
}

// returns hex data
struct IH_line_t *IH_read_line(FILE *file)
{
  char line_h[9];
  char line_e[2];
  static struct IH_line_t line[1];
  static char *data = NULL;
  int c;

  DEBUG_BEGIN("IH_read_line(%p)\n", file);
  if (fread(line_h, sizeof(char), 9, file) != 9)
    ERROR("I/O error\n");
  if (line_h[0] != ':')
    ERROR("invalid intel hex file\n");
  line->size = (HEX_INT(line_h[1])<<4) + HEX_INT(line_h[2]);
  line->address = (HEX_INT(line_h[3])<<12) + (HEX_INT(line_h[4])<<8) + (HEX_INT(line_h[5])<<4) + HEX_INT(line_h[6]);
  line->type = (HEX_INT(line_h[7])<<4) + HEX_INT(line_h[8]);
  if (line->size)
    {
      REALLOCATE(char, data, line->size * 2);
      if (fread(data, sizeof(char), line->size * 2, file) != line->size * 2)
	ERROR("I/O error\n");
    }
  if (fread(line_e, sizeof(char), 2, file) != 2)
    ERROR("I/O error\n");
  if ((c = fgetc(file)) != EOF)
    {
      if (c == '\r')
	if ((c = fgetc(file)) == EOF)
	  ERROR("I/O error\n");
      if (c != '\n')
	ERROR("invalid intel hex file\n");
    }
  line->data = data;
  line->checksum = (HEX_INT(line_e[0])<<4) + HEX_INT(line_e[1]);
  DEBUG_END("return %p\n", line);
  return line;
}

struct pages_t *IH_read_bin(char *filename)
{
  struct pages_t *retval;
  struct page_t *pages = NULL;
  int count;
  int size;
  char data[0x10000]; // theoretical max on 1 page: z80 is a 16bit processor
  struct IH_line_t *line;
  FILE *file;
  int i;
  
  if (!(file = fopen(filename, "r")))
    ERROR("couldn't open file \"%s\"\n", filename);
  size = 0;
  count = 0;
  for (line = IH_read_line(file); line; line = IH_read_line(file))
    {
      switch (line->type)
	{
	case 0x00: // normal data line
	  for (i = 0; i < line->size; i++)
	    data[size+i] = (HEX_INT(line->data[i*2])<<4) + HEX_INT(line->data[i*2+1]);
	  size += line->size;
	  break;
	case 0x01: // EOF
	  goto IH_bin_read;
	case 0x02: // new page;
	  if (size == 0)
	    break; // don't use empty pages
	  count++;
	  REALLOCATE(struct page_t, pages, count);
	  pages[count - 1].size = size;
	  ALLOCATE(char, pages[count-1].data, size);
	  memcpy(pages[count-1].data, data, size);
	  size = 0;
	default:
	  ERROR("invalid intel hex file\n");
	}
    }
 IH_bin_read:
  fclose(file);
  if (size != 0)
    {
      count++;
      REALLOCATE(struct page_t, pages, count);
      pages[count - 1].size = size;
      ALLOCATE(char, pages[count-1].data, size);
      memcpy(pages[count-1].data, data, size);
    }
  if (count == 0)
    return NULL;
  ALLOCATE(struct pages_t, retval, 1);
  retval->count = count;
  retval->pages = pages;
  return retval;
}

struct pages_t *IH_read_hex(char *filename)
{
  struct pages_t *retval;
  struct page_t *pages = NULL;
  int count;
  int size;
  char data[0x10000]; // theoretical max on 1 page: z80 is a 16bit processor
  struct IH_line_t *line;
  FILE *file;
  
  file = fopen(filename, "r");
  size = 0;
  count = 0;
  for (line = IH_read_line(file); line; line = IH_read_line(file))
    {
      switch (line->type)
	{
	case 0x00: // normal data line
	  memcpy(data + size, line->data, line->size * 2);
	  size += line->size * 2;
	  break;
	case 0x01: // EOF
	  goto IH_hex_read;
	case 0x02: // new page;
	  if (size == 0)
	    break; // don't use empty pages
	  count++;
	  REALLOCATE(struct page_t, pages, count);
	  pages[count - 1].size = size;
	  ALLOCATE(char, pages[count-1].data, size);
	  memcpy(pages[count-1].data, data, size);
	  size = 0;
	}
    }
 IH_hex_read:
  fclose(file);
  if (size != 0)
    {
      count++;
      REALLOCATE(struct page_t, pages, count);
      pages[count - 1].size = size;
      ALLOCATE(char, pages[count-1].data, size);
      memcpy(pages[count-1].data, data, size);
    }
  if (count == 0)
    return NULL;
  ALLOCATE(struct pages_t, retval, 1);
  retval->count = count;
  retval->pages = pages;
  return retval;
}

int make_ti83p_app(int ct, int vt, char *infile, char *outfile)
{
  int e;
  if ((e = mkApp__FPcN20(infile, outfile, "0104.key")))
    ERROR("mkApp (from libappsign) returned error code %i\n", e);
  return 0;
}

int make_ti83p_8xk(int ct, int vt, char *infile, char *outfile)
{
  int e;
  if ((e = mk8xk__FPcN20(infile, outfile, "0104.key")))
    ERROR("mk8xk (from libappsign) returned error code %i\n", e);
  return 0;
}

int make_bin(int ct, int vt, char *infile, char *outfile)
{
  struct pages_t *pages;
  struct page_t *page;
  Ti8xVarEntry *entry;
  Ti8xRegular *content;
  int e;

  if (!(pages = IH_read_bin(infile)))
    ERROR("internal error\n");
  if (pages->count != 1)
    ERROR("a program should contain exactly one page\n");
  page = pages->pages;
  page->size += 2;
  REALLOCATE(char, page->data, page->size);
  memmove(page->data+2, page->data, page->size - 2);
  page->data[0] = (page->size-2) & 0xff;
  page->data[1] = ((page->size-2)>>8) & 0xff;
  if (!name)
    name = l_basename(outfile);
  //fill entry
  ALLOCATE(Ti8xVarEntry, entry, 1);
  strcpy(entry->name, name);
  entry->type = vt;
  entry->attr = ATTRB_NONE;
  entry->size = page->size;
  entry->data = page->data;
  // fill content
  if (!(content = ti8x_create_regular_content()))
    ERROR("could not create content structure\n");
  content->calc_type = ct;
  strcpy(content->comment, "created with zasm v0.0 alpha");
  content->num_entries = 1;
  content->entries = entry;
  // write out
  if ((e = ti8x_write_regular_file(outfile, content, NULL)) != 0)
    ERROR("couldn't write to file \"%s\": \n\tti8x_write_regular_file (from libtifiles) returned error code %i\n", outfile, e);
  free(page->data);
  free(page);
  free(pages);
  return 0;
}

int make_bin83p(int ct, int vt, char *infile, char *outfile)
{
  struct pages_t *pages;
  struct page_t *page;
  Ti8xVarEntry *entry;
  Ti8xRegular *content;
  int e;

  if (!(pages = IH_read_bin(infile)))
    ERROR("internal error\n");
  if (pages->count != 1)
    ERROR("a program should contain exactly one page\n");
  page = pages->pages;
  if (typechr)
    {
      page->size += 4;
      REALLOCATE(char, page->data, page->size);
      memmove(page->data+4, page->data, page->size - 4);
      page->data[2] = 0xbb; // t2ByteTok
      page->data[3] = 0x6d; // tAsmCmp
    }
  else
    {
      page->size += 2;
      REALLOCATE(char, page->data, page->size);
      memmove(page->data+2, page->data, page->size - 2);
    }
  page->data[0] = (page->size-2) & 0xff;
  page->data[1] = ((page->size-2)>>8) & 0xff;
  if (!name)
    name = l_basename(outfile);
  //fill entry
  ALLOCATE(Ti8xVarEntry, entry, 1);
  strcpy(entry->name, name);
  entry->type = vt;
  entry->attr = ATTRB_NONE;
  entry->size = page->size;
  entry->data = page->data;
  // fill content
  if (!(content = ti8x_create_regular_content()))
    ERROR("could not create content structure\n");
  content->calc_type = ct;
  strcpy(content->comment, "created with zasm v0.0 alpha");
  content->num_entries = 1;
  content->entries = entry;
  // write out
  if ((e = ti8x_write_regular_file(outfile, content, NULL)) != 0)
    ERROR("couldn't write to file \"%s\": \n\tti8x_write_regular_file (from libtifiles) returned error code %i\n", outfile, e);
  free(page->data);
  free(page);
  free(pages);
  return 0;
}

int make_hex83p(int ct, int vt, char *infile, char *outfile)
{
  struct pages_t *pages;
  struct page_t *page;
  Ti8xVarEntry *entry;
  Ti8xRegular *content;
  char *data;
  int i, size, line_count, e;

  if (!(pages = IH_read_hex(infile)))
    ERROR("internal error\n");
  if (pages->count != 1)
    ERROR("a program should contain exactly one page\n");
  page = pages->pages;
  
  size = (page->size * 13)/12;
  line_count = page->size / 12;
  ALLOCATE(char, data, size);
  for (i = 0; i < line_count; i++)
    {
      memcpy(data+13*i, page->data+12*i, 12);
      data[13*i + 12] = 0x3f; // newline
    }
  memcpy(data+13*i, page->data+12*i, size - line_count * 13);
  free(page->data);
  free(page);
  free(pages);
  if (typechr)
    {
      size += 5;
      REALLOCATE(char, data, size);
      memmove(data+5, data, size - 5);
      data[2] = 0xbb; // t2ByteTok
      data[3] = 0x6c; // tAsmPrgm
      data[4] = 0x3f; // newline
    }
  else
    {
      size += 2;
      REALLOCATE(char, data, size);
      memmove(data+2, data, size - 2);
    }
  data[0] = (size-2) & 0xff;
  data[1] = ((size-2)>>8) & 0xff;
  if (!name)
    name = l_basename(outfile);
  //fill entry
  DEBUG("data = \"");
  fwrite(data, sizeof(char), size, stderr);
  DEBUG("\"\n");
  ALLOCATE(Ti8xVarEntry, entry, 1);
  strcpy(entry->name, name);
  entry->type = vt;
  entry->attr = ATTRB_NONE;
  entry->size = size;
  entry->data = data;
  // fill content
  if (!(content = ti8x_create_regular_content()))
    ERROR("could not create content structure\n");
  content->calc_type = ct;
  strcpy(content->comment, "created with zasm v0.0 alpha");
  content->num_entries = 1;
  content->entries = entry;
  // write out
  if ((e = ti8x_write_regular_file(outfile, content, NULL)) != 0)
    ERROR("couldn't write to file \"%s\": \n\tti8x_write_regular_file (from libtifiles) returned error code %i\n", outfile, e);
  free(data);
  return 0;
}

struct type_t types_73[] = 
  {
    {"PRGM", TI73_ASM, make_bin},
    {"PROGRAM", TI73_ASM, make_bin},
    {"PROGRAMME", TI73_ASM, make_bin},
    {"ASM", TI73_ASM, make_bin},
    {"SQSH", TI73_ASM, make_bin},
    {"SQUISH", TI73_ASM, make_bin},
    {"SQUISHED", TI73_ASM, make_bin},
    {"COMPILED", TI73_ASM, make_bin},

    {NULL, 0, NULL}
  };

struct type_t types_82[] = 
  {
    {"PRGM", TI82_PPGM, make_bin},
    {"PROGRAM", TI82_PPGM, make_bin},
    {"PROGRAMME", TI82_PPGM, make_bin},
    {"ASM", TI82_PPGM, make_bin},
    {"SQSH", TI82_PPGM, make_bin},
    {"SQUISH", TI82_PPGM, make_bin},
    {"SQUISHED", TI82_PPGM, make_bin},
    {"COMPILED", TI82_PPGM, make_bin},

    {NULL, 0, NULL}
  };

struct type_t types_83[] = 
  {
    {"PRGM", 0x06, make_bin},       // TI83_ASM is not defined by tifiles
    {"PROGRAM", 0x06, make_bin},
    {"PROGRAMME", 0x06, make_bin},
    {"ASM", 0x06, make_bin},
    {"SQSH", 0x06, make_bin},
    {"SQUISH", 0x06, make_bin},
    {"SQUISHED", 0x06, make_bin},
    {"COMPILED", 0x06, make_bin},

    {NULL, 0, NULL}
  };

struct type_t types_83P[] = 
  {
    {"PRGM", TI83p_PRGM, make_hex83p},
    {"PROGRAM", TI83p_PRGM, make_hex83p},
    {"PROGRAMME", TI83p_PRGM, make_hex83p},

    {"ASM", TI83p_ASM, make_bin83p},
    {"SQSH", TI83p_ASM, make_bin83p},
    {"SQUISH", TI83p_ASM, make_bin83p},
    {"SQUISHED", TI83p_ASM, make_bin83p},
    {"COMPILED", TI83p_ASM, make_bin83p},

    {"APP", 0, make_ti83p_app},
    {"8XK", 0, make_ti83p_8xk},
    {"APPLICATION", 0, make_ti83p_8xk},
    {NULL, 0, NULL}
  };

struct type_t types_85[] = 
  {
    {"PRGM", TI85_STRNG, make_bin},     // binary
    {"PROGRAM", TI85_STRNG, make_bin},
    {"PROGRAMME", TI85_STRNG, make_bin},
    {"ASM", TI85_STRNG, make_bin},
    {"SQSH", TI85_STRNG, make_bin},
    {"SQUISH", TI85_STRNG, make_bin},
    {"SQUISHED", TI85_STRNG, make_bin},
    {"COMPILED", TI85_STRNG, make_bin},
    {"STRNG", TI85_STRNG, make_bin},
    {"STRING", TI85_STRNG, make_bin},

    {NULL, 0, NULL}
  };

struct type_t types_86[] = 
  {
    {"PRGM", TI86_PRGM, make_bin},      // binary
    {"PROGRAM", TI86_PRGM, make_bin},
    {"PROGRAMME", TI86_PRGM, make_bin},
    {"ASM", TI86_PRGM, make_bin},
    {"SQSH", TI86_PRGM, make_bin},
    {"SQUISH", TI86_PRGM, make_bin},
    {"SQUISHED", TI86_PRGM, make_bin},
    {"COMPILED", TI86_PRGM, make_bin},

    {NULL, 0, NULL}
  };

struct calc_t calcs[] = 
  {
    {"73", CALC_TI73, types_73},
    {"TI73", CALC_TI73, types_73},

    {"82", CALC_TI82, types_82},
    {"TI82", CALC_TI82, types_82},

    {"83", CALC_TI83, types_83},
    {"TI83", CALC_TI83, types_83},

    {"83PLUS", CALC_TI83P, types_83P},
    {"83P", CALC_TI83P, types_83P},
    {"83+", CALC_TI83P, types_83P},
    {"TI83PLUS", CALC_TI83P, types_83P},
    {"TI83P", CALC_TI83P, types_83P},
    {"TI83+", CALC_TI83P, types_83P},

    {"85", CALC_TI85, types_85},
    {"TI85", CALC_TI85, types_85},

    {"86", CALC_TI86, types_86},
    {"TI86", CALC_TI86, types_86},

    {NULL, 0, NULL}
  };

struct calc_t find_calc(char *name)
{
  int i;
  
  for (i = 0; calcs[i].name; i++)
    if (0 == strcasecmp(calcs[i].name, name))
      return calcs[i];
  ERROR("unknown calculator type: \"%s\"\n", name);
}

struct type_t find_type(char *name, struct type_t *types)
{
  int i;
  
  if (!types)
    ERROR("no calculator specified yet\n");
  for (i = 0; types[i].name; i++)
    if (0 == strcasecmp(types[i].name, name))
      return types[i];
  ERROR("unknown variable type: \"%s\"\n", name);
}

int main(int argc, char *argv[])
{
  unsigned short int **ctype_b = __ctype_b_loc();
  int i;
  __ctype_b = *ctype_b;

  debug_file = NULL;
  warning_file = stderr;
  error_file = stderr;

  for (i = 1; i < argc; i++)
    {
      if ((strcasecmp(argv[i], "--calc") == 0) || (strcasecmp(argv[i], "-c") == 0))
	{
	  if (i == argc)
	    ERROR("invalid command line\n");
	  current_calc = find_calc(argv[++i]);
	}
      else if ((strcasecmp(argv[i], "--type") == 0) || (strcasecmp(argv[i], "-t") == 0))
	{
	  if (i == argc)
	    ERROR("invalid command line\n");
	  current_type = find_type(argv[++i], current_calc.types);
	}
      else if ((strcasecmp(argv[i], "--begin-chars") == 0) || (strcasecmp(argv[i], "-b") == 0))
	typechr = 1;
      else if (infile)
	outfile = argv[i];
      else
	infile = argv[i];
    }
  if ((!current_calc.types) || (!current_type.filter) || (!infile) || (!outfile))
    ERROR("not all needed information is given\n");
  if (current_type.filter(current_calc.ID, current_type.ID, infile, outfile))
    ERROR("error while converting \"%s\" to \"%s\"\n", infile, outfile);
  return 0;
}
