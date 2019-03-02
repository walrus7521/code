#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.57)
AC_INIT([[zasm]],[[0.0 alpha]],[[stevendeprez@users.sourceforge.net]])
AC_REVISION([revision 0])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_MAKE_SET
AC_PROG_INSTALL

# other checks
AC_GNU_SOURCE
# Checks for libraries.
AC_CHECK_LIB([tifiles], [[ti8x_write_regular_file]],,
			[AC_MSG_ERROR([[cannot find libtifiles, wich is needed for writing graphlink headers]])])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h unistd.h],,
			   [AC_MSG_ERROR([[Some needed include files are missing]])])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_STAT
AC_CHECK_FUNCS([memmove strcasecmp strchr strncasecmp strtol asprintf],,
			[AC_MSG_ERROR([[ToDo: replace some non-portable functions with local alternatives]])])

AC_CONFIG_FILES([assembler/Makefile
                 converter/Makefile
                 preprocessor/Makefile
		 Makefile])
AC_OUTPUT

AC_MSG_NOTICE([[zasm is configured, now you can type `make` and `make install`]])
