#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([HP11em],[0.0.5],[giulio@rapgenic.com],[hp11em],[www.rapgenic.com/hp11em])
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_SRCDIR([src/])
AM_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11(, [mandatory])

# Checks for libraries.
PKG_CHECK_MODULES([GTKMM], [gtkmm-3.0 >= 3.8.0])

# Checks for header files.
AC_CHECK_HEADERS([string])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.

AC_ARG_WITH([debug],
    AS_HELP_STRING([--with-debug], [Enable debug features]),
    AC_DEFINE([DEBUG], , ["Debug features enabled"]))

AC_DEFINE([CONFIG_DIR], ["/.config/hp11em/"], ["The directory used to store the configuration"])
AC_ARG_VAR([CONFIG_DIR], ["Set the directory used to store the configuration (default: ~/.config/hp11em/)"])

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
