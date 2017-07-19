AC_INIT([BatchRename], [1.0.0], [jingnan.si@gmail.com])
AC_CONFIG_SRCDIR(src/app.cpp)
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

AM_PROG_AR

LT_INIT

AC_PROG_CC
AC_PROG_CXX
AC_C_CONST
AC_HEADER_STDBOOL

AC_LANG(C++)

dnl enable debug
AC_ARG_ENABLE([debug],
     [  --enable-debug    Turn on debugging],
     [case "${enableval}" in
       yes) debug=yes ;;
       no)  debug=no ;;
       *) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
     esac],[debug=no])

if test "$debug" = yes; then
    debug_flag="-g -D_DEBUG"
else
    debug_flag=""
fi

dnl enable static
AC_ARG_ENABLE([static],
     [  --enable-static    Turn on static link to wxWidget],
     [case "${enableval}" in
       yes) static=yes ;;
       no)  static=no ;;
       *) AC_MSG_ERROR([bad value ${enableval} for --enable-static]) ;;
     esac],[static=no])

AC_CHECK_PROG(WX_CONFIG,[wx-config],yes,no)
if test "$WX_CONFIG" = no; then
	AC_MSG_FAILURE(wx-config not exists)
fi

ADDTIONAL_CXX_FLAGS=

AM_CONDITIONAL(BUILD_ANGSTROM, test x = y)
AM_CONDITIONAL(BUILD_WIN32, test x = y)
AM_CONDITIONAL(WIN32, test x = y)

case "${host}" in
  *-mingw32* | *-cygwin* )
	AC_DEFINE(BUILD_WIN32, 1, Build Form Win32)
	ADDTIONAL_CXX_FLAGS="-DWIN32 -D_WIN32 -DWINDOWS -D_WINDOWS -DUNICODE -D_UNICODE"
	AM_CONDITIONAL(BUILD_WIN32, test x = x)
	AM_CONDITIONAL(WIN32, test x = x)
	AC_CHECK_TOOL(WINDRES, [windres])
  ;;
  *-angstrom* )
	AC_DEFINE([BUILD_ANGSTROM], 1, [Build for angstrom])
	AM_CONDITIONAL(BUILD_ANGSTROM, test x = x)
  ;;
  *)
esac

CXXFLAGS+=" `wx-config --cxxflags --static=$static --debug=$debug` ${debug_flag} ${ADDTIONAL_CXX_FLAGS}"
CPPFLAGS+=" `wx-config --cppflags --static=$static --debug=$debug` ${debug_flag} ${ADDTIONAL_CXX_FLAGS}"
CFLAGS+=" `wx-config --cflags --static=$static --debug=$debug` ${debug_flag} ${ADDTIONAL_CXX_FLAGS}"
LIBS+=" `wx-config --libs std,richtext --static=$static --debug=$debug`"

AC_CHECK_HEADERS(["wx/wx.h"],
	[AC_MSG_RESULT(checking for wx/wx.h... OK)],
	[AC_MSG_FAILURE(wx/wx.h is not found)]
	)

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_HEADER_STDC
AC_HEADER_TIME
AC_CHECK_FUNCS([memset])
AC_CHECK_FUNCS([sqrt])
AC_CHECK_FUNCS([gettimeofday])
AC_CHECK_FUNCS([mmap])
AC_CHECK_FUNCS([open nanosleep usleep])
AC_CHECK_HEADERS([algorithm],
	[AC_DEFINE([HAVE_ALGORITHM], 1, [Define to 1 if you have <algorithm>.]) ],
	[AC_MSG_ERROR([unable to find algorithm, please install libstdc++])])
AC_CHECK_HEADERS([memory],
	[AC_DEFINE([HAVE_MEMORY], 1, [Define to 1 if you have <memory>.]) ],
	[AC_MSG_ERROR([unable to find memory, please install libstdc++])])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

AC_OUTPUT
