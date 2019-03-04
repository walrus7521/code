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

static int calc_minus(int *args);
static int calc_plus (int *args);
static int calc_rem  (int *args);
static int calc_div  (int *args);
static int calc_times(int *args);
static int calc_neg  (int *args);

static int calc_log_or(int *args);
static int calc_log_and(int *args);
static int calc_log_not(int *args);
static int calc_bit_or(int *args);
static int calc_bit_and(int *args);
static int calc_bit_not(int *args);

static int calc_eq(int *args);
static int calc_ne(int *args);
static int calc_ge(int *args);
static int calc_le(int *args);
static int calc_gt(int *args);
static int calc_lt(int *args);

static int calc_paren(int *args);

static int calc_shift_left(int *args);
static int calc_shift_right(int *args);

static char *print_minus(char **args);
static char *print_plus (char **args);
static char *print_rem  (char **args);
static char *print_div  (char **args);
static char *print_times(char **args);
static char *print_neg  (char **args);

static char *print_log_or (char **args);
static char *print_log_and(char **args);
static char *print_log_not(char **args);
static char *print_bit_or (char **args);
static char *print_bit_and(char **args);
static char *print_bit_not(char **args);

static char *print_eq(char **args);
static char *print_ne(char **args);
static char *print_ge(char **args);
static char *print_le(char **args);
static char *print_gt(char **args);
static char *print_lt(char **args);

static char *print_paren(char **args);

static char *print_shift_left(char **args);
static char *print_shift_right(char **args);

static int val_hex(char *str);
static int val_dec(char *str);
static int val_oct(char *str);
static int val_bin(char *str);
static int val_const(char *str);

static char *print_hex(char *str);
static char *print_dec(char *str);
static char *print_oct(char *str);
static char *print_bin(char *str);
static char *print_const(char *str);

static struct operator_t operators_logic[] = 
  {
    {"#||#", calc_log_or,  print_log_or},
    {"#&&#", calc_log_and, print_log_and},
    {"!#",   calc_log_not, print_log_not},
    {NULL,  NULL, NULL}
  };
static struct operator_t operators_ineq[] = 
  {
    {"#==#", calc_eq, print_eq},
    {"#!=#", calc_ne, print_ne},
    {"#<=#", calc_le, print_le},
    {"#>=#", calc_ge, print_ge},
    {"#<#",  calc_lt, print_lt},
    {"#>#",  calc_gt, print_gt},
    {NULL,  NULL, NULL}
  };
static struct operator_t operators_add[] = 
  {
    {"#+#", calc_plus,  print_plus},
    {"#-#", calc_minus, print_minus},
    {NULL,  NULL, NULL}
  };
static struct operator_t operators_mult[] = 
  {
    {"#*#", calc_times, print_times},
    {"#%#", calc_rem,   print_rem},
    {"#/#", calc_div,   print_div},
    {"-#",  calc_neg,   print_neg},
    {NULL,  NULL, NULL}
  };
static struct operator_t operators_shift[] = 
  {
    {"#<<#", calc_shift_left, print_shift_left},
    {"#>>#", calc_shift_right, print_shift_right},
  };
static struct operator_t operators_bit[] = 
  {
    {"#|#", calc_bit_or,  print_bit_or},
    {"#&#", calc_bit_and, print_bit_and},
    {"^#",  calc_bit_not, print_bit_not},
    {NULL,  NULL, NULL}
  };
static struct operator_t operators_paren[] = 
  {
    {"(#)", calc_paren, print_paren},
    {"{#}", calc_paren, print_paren},
    {"[#]", calc_paren, print_paren},
    {NULL, NULL, NULL}
  };

static struct precedence_t prec_levels[] = 
  {
    {operators_logic, EXPR_ASSOC_LEFT},
    {operators_ineq, EXPR_ASSOC_LEFT},
    {operators_add, EXPR_ASSOC_LEFT},
    {operators_mult, EXPR_ASSOC_LEFT},
    {operators_shift, EXPR_ASSOC_LEFT},
    {operators_bit, EXPR_ASSOC_LEFT},
    {operators_paren, EXPR_ASSOC_LEFT},
    {NULL, 0}
  };

static struct numbertype_t numbertypes[] = 
  {
    {"0x#", "0123456789ABCDEFabcdef", val_hex, print_hex},
    {"0X#", "0123456789ABCDEFabcdef", val_hex, print_hex},
    {"0h#", "0123456789ABCDEFabcdef", val_hex, print_hex},
    {"0H#", "0123456789ABCDEFabcdef", val_hex, print_hex},
    {"0d#", "0123456789", val_dec, print_dec},
    {"0D#", "0123456789", val_dec, print_dec},
    {"0o#", "01234567", val_oct, print_oct},
    {"0O#", "01234567", val_oct, print_oct},
    {"0b#", "01", val_bin, print_bin},
    {"0B#", "01", val_bin, print_bin},

    {"#o",  "01234567", val_oct, print_oct},
    {"#O",  "01234567", val_oct, print_oct},
    {"#h",  "0123456789ABCDEFabcdef", val_hex, print_hex},
    {"#H",  "0123456789ABCDEFabcdef", val_hex, print_hex},
    {"#b",  "01", val_bin, print_bin},
    {"#B",  "01", val_bin, print_bin},
    {"#d",  "0123456789", val_dec, print_dec},
    {"#D",  "0123456789", val_dec, print_dec},

    {"0#",  "01234567", val_oct, print_oct},
    {"#",   "0123456789", val_dec, print_dec},

    {"#",   "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._$",
     val_const, print_const},  // '.' explicitly permitted, for label.page
    {NULL, NULL, NULL, NULL}
  };

static int calc_minus(int *args){return args[0] - args[1];}
static int calc_plus (int *args){return args[0] + args[1];}
static int calc_rem  (int *args){return args[0] % args[1];}
static int calc_div  (int *args){return args[0] / args[1];}
static int calc_times(int *args){return args[0] * args[1];}
static int calc_neg  (int *args){return -args[0];}

static int calc_log_or(int *args){return args[0] || args[1];}
static int calc_log_and(int *args){return args[0] && args[1];}
static int calc_log_not(int *args){return !(args[0]);}
static int calc_bit_or(int *args){return args[0] | args[1];}
static int calc_bit_and(int *args){return args[0] & args[1];}
static int calc_bit_not(int *args){return ~args[0];}

static int calc_eq(int *args){return args[0] == args[1];}
static int calc_ne(int *args){return args[0] != args[1];}
static int calc_ge(int *args){return args[0] >= args[1];}
static int calc_le(int *args){return args[0] <= args[1];}
static int calc_gt(int *args){return args[0] > args[1];}
static int calc_lt(int *args){return args[0] < args[1];}

static int calc_paren(int *args){return args[0];}

static int calc_shift_left(int *args){return args[0] << args[1];}
static int calc_shift_right(int *args){return args[0] >> args[1];}

static char *print_minus(char **args){return strcat4("-", args[0], ":", args[1]);}
static char *print_plus (char **args){return strcat4("+", args[0], ":", args[1]);}
static char *print_rem  (char **args){return strcat4("%", args[0], ":", args[1]);}
static char *print_div  (char **args){return strcat4("/", args[0], ":", args[1]);}
static char *print_times(char **args){return strcat4("*", args[0], ":", args[1]);}
static char *print_neg  (char **args){return strcat4("-",     "0", ":", args[0]);}

// boolean operators are not accepted by the assembler
static char *print_log_or (char **args){ERROR("operator not permitted here\n");} 
static char *print_log_and(char **args){ERROR("operator not permitted here\n");}
static char *print_log_not(char **args){ERROR("operator not permitted here\n");}
static char *print_bit_or (char **args){return strcat4("|", args[0], ":", args[1]);}
static char *print_bit_and(char **args){return strcat4("&", args[0], ":", args[1]);}
static char *print_bit_not(char **args){return strcat2("^", args[0]);}

static char *print_eq(char **args){ERROR("operator not permitted here\n");}
static char *print_ne(char **args){ERROR("operator not permitted here\n");}
static char *print_ge(char **args){ERROR("operator not permitted here\n");}
static char *print_le(char **args){ERROR("operator not permitted here\n");}
static char *print_gt(char **args){ERROR("operator not permitted here\n");}
static char *print_lt(char **args){ERROR("operator not permitted here\n");}

static char *print_paren(char **args){return str_cpy_alloc(args[0]);}

static char *print_shift_left(char **args){return strcat4("<", args[0], ":", args[1]);}
static char *print_shift_right(char **args){return strcat4(">", args[0], ":", args[1]);}

static int val_hex(char *str){return strtol(str, NULL, 16);}
static int val_dec(char *str){return strtol(str, NULL, 10);}
static int val_oct(char *str){return strtol(str, NULL, 8);}
static int val_bin(char *str){return strtol(str, NULL, 2);}
static int val_const(char *str){return int_error;}
static char *print_hex(char *str)
{
  char *retval;
  if (asprintf(&retval, "%i", val_hex(str))<0)
    ERROR("asprintf returned an error\n");
  return retval;
}
static char *print_dec(char *str)
{
  char *retval;
  if (asprintf(&retval, "%i", val_dec(str))<0)
    ERROR("asprintf returned an error\n");
  return retval;
}
static char *print_oct(char *str)
{
  char *retval;
  if (asprintf(&retval, "%i", val_oct(str))<0)
    ERROR("asprintf returned an error\n");
  return retval;
}
static char *print_bin(char *str)
{
  char *retval;
  if (asprintf(&retval, "%i", val_bin(str))<0)
    ERROR("asprintf returned an error\n");
  return retval;
}
static char *print_const(char *str)
{
  return str_cpy_alloc(str); // so str can be freed
}
