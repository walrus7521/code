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

#ifndef DEBUG_H
#define DEBUG_H 1

#include <stdio.h>

#ifndef DEBUG_C
extern int debug_depth;
extern FILE *debug_file;
extern FILE *warning_file;
extern FILE *error_file;
#endif

#define DEBUG_OUT(file, format, args...) {if (file) fprintf(file, format, ## args);}
#define DEBUG_PRINT(header, file, format, args...) {DEBUG_OUT(file, header); DEBUG_OUT(file, format, ## args);}

#define DEBUG(format, args...) {DEBUG_OUT(debug_file, "%*s", debug_depth, ""); DEBUG_OUT(debug_file, format, ## args);}
#define WARNING(format, args...) {DEBUG_PRINT("warning: ", warning_file, format, ## args);}
#define ERROR(format, args...) {DEBUG_PRINT("error: ", error_file, format, ## args);exit(1);}

#define DEBUG_BEGIN(format, args...) {DEBUG(format, ## args); debug_depth++;}
#define DEBUG_END(format, args...) {debug_depth--;DEBUG(format, ## args);}

#define ALLOCATE(type, var, count) {if (!(var = (type *)malloc(sizeof(type)*(count))))\
 ERROR("couldn't allocate %i instances of %s\n", count, # type);}
#define REALLOCATE(type, var, count) {if (!(var = (type *)realloc(var, sizeof(type)*(count))))\
 ERROR("couldn't allocate %i instances of %s\n", count, # type);}

#endif
