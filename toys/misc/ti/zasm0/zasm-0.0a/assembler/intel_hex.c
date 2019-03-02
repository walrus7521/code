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

#define INTEL_HEX_C 1
#include <config.h>
#include "assembler.h"

static int checksum = 0;
static int length = 0;
static int address = 0;
static char data_array[64];

static int intel_hex_flush(FILE *dest);
static int intel_hex_byte(FILE *dest, char h1, char h2);

int intel_hex_end(FILE *dest)
{
  if (intel_hex_flush(dest) < 0)
    return -1;
  if (fprintf(dest, ":00000001FF\r\n")!= 13)
    return -1;
  return 0;
}

int intel_hex_page(FILE *dest, char page)
{
  if (intel_hex_flush(dest) < 0)
    return -1;
  if (fprintf(dest, ":02000002%04X%02X\r\n", page, 0x100 - page - 2) != 13)
    return -1;
  return 0;
}

// write data to intel hex with rowlength 32
int intel_hex_write(FILE *dest, char *data, int dest_addr)
{
  int i;
  
  if (dest_addr != (address + length))
    {
      if (intel_hex_flush(dest) < 0)
	return -1;
      address = dest_addr;
    }
  if (data == NULL)
    {
      if (intel_hex_flush(dest) < 0)
	return -1;
      else
	return 0;
    }
  for (i = 0; data[i] && data[i+1]; i+=2)
    if (intel_hex_byte(dest, data[i], data[i+1]) < 0)
      return -1;
  return 0;

}

static int intel_hex_byte(FILE *dest, char h1, char h2)
{
  if (length >= 32)
    if (intel_hex_flush(dest)<0)
      return -1;
  data_array[length*2  ] = h1;
  data_array[length*2+1] = h2;
  length++;
  checksum += hex_byte(h1, h2);
  return 0;
}

static int intel_hex_flush(FILE *dest)
{
  if (length <= 0)
    return 0;
  if (fprintf(dest, ":%02hhX%04hX00", length & 0xff, address & 0xffff) != 9)
    return -1;
  if (fwrite(data_array, 2, length, dest) < 0)
    return -1;
  checksum += (length & 0xff) + (address & 0xff) + ((address >> 8) & 0xff);
  if (fprintf(dest, "%02hhX\r\n", 0x100 - checksum) != 4)
    return -1;
  checksum = 0;
  address += length;
  length = 0;
  return 0;
}
