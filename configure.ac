#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([HP11em],[0.0.1],[giulio@rapgenic.com],[hp11em],[www.rapgenic.com/hp11em])
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_SRCDIR([src/])
AM_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11(, [mandatory])

# Checks for libraries.
PKG_CHECK_MODULES([GTKMM], [gtkmm-3.0 >= 3.8.0])
PKG_CHECK_MODULES([CLN], [cln >= 1.3.3])
AC_CHECK_LIB(gmp, __gmpz_init, , [AC_MSG_ERROR([GNU MP not found, see https://gmplib.org/])])

# Checks for header files.
AC_CHECK_HEADERS([string])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.

AC_ARG_WITH([debug],
    AS_HELP_STRING([--with-debug], [Enable debug features]),
    AC_DEFINE([DEBUG], , ["Debug features enabled"]))

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
