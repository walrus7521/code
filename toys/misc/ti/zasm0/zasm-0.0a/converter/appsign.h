/*******************************************************************************\
 * Copyright (C) Peter-Martijn Kuipers                                         *
 *                                                                             *
 * Disclaimer:                                                                 *
 * This library comes without any warranties, not even the implied warranty of *
 * merchantability or fitness for a particular purpose, to the maximum extent  *
 * permitted by applicable law.                                                *
 * You will hold neither the Porter/Author, not Texas Instruments responsible  *
 * for any and all damages caused by the use of this library.                  *
 *                                                                             *
 * Copying and reverse engineering:                                            *
 * You may copy the library to any unlimited number of machines or people,     *
 * prived that all license and copyright notices remain intact.                *
 * You may not reverse-engineer, disassemble, reassemble, or decompile the     *
 * library.                                                                    *
 *                                                                             *
 *--Peter-Martijn                                                              *
\*******************************************************************************/

/* Appsign static library v1.0b
   Usage:
   
   do something like:
   "gcc yourfile.c libappsign.a -o youroutfile"
   and be sure to do
   '#include 'appsign.h' " 
   in your c files that use the library.

   Routines:
   int mk8xk(char* infile, char* outfile, char* keyfile);
   int mkApp(char* infile, char* outfile, char* keyfile);
   
   infile:  the input filename, which containes the unsigned app
   outfile: the filename of the file that'll contain the signed app
   keyfile: the name of the keyfile that is to be used to sign the app
            if NULL, or "", it _should_ revert to "./0104.key" automatically,
	    but don't count on it, _always_ specify the file!

   mk8xk makes an app with graphlink header
   mkapp makes an app without one.

   both routines cat return the error defined (and commented) below

   good luck! 
   --Peter-Martijn Kuipers

*/
#ifndef __LIBAPPSIGN
#define __LIBAPPSIGN

int mk8xk(char*,char*,char*);
int mkApp(char*,char*,char*);

// Error defines:
// No errors:
#define ASERR_NOERR  0 
// Couldn't delete the temp files (non-crucial, stopped after files were made)
#define ASERR_TMPDEL 1
// Couldn't make the temp files   (crucial, stopped before files were made)
#define ASERR_NOTMP  2


#endif
