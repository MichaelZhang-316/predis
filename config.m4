dnl $Id$
dnl config.m4 for extension predis

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(predis, for predis support,
dnl Make sure that the comment is aligned:
dnl [  --with-predis             Include predis support])

dnl Otherwise use enable:

 PHP_ARG_ENABLE(predis, whether to enable predis support,
 Make sure that the comment is aligned:
 [  --enable-predis           Enable predis support])

if test "$PHP_PREDIS" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-predis -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/predis.h"  # you most likely want to change this
  dnl if test -r $PHP_PREDIS/$SEARCH_FOR; then # path given as parameter
  dnl   PREDIS_DIR=$PHP_PREDIS
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for predis files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PREDIS_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PREDIS_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the predis distribution])
  dnl fi

  dnl # --with-predis -> add include path
  dnl PHP_ADD_INCLUDE($PREDIS_DIR/include)
  PHP_ADD_INCLUDE(./lib)
  PHP_ADD_LIBRARY_WITH_PATH(hiredis, ./lib, PREDIS_SHARED_LIBADD)
  PHP_SUBST(PREDIS_SHARED_LIBADD)

  dnl # --with-predis -> check for lib and symbol presence
  dnl LIBNAME=predis # you may want to change this
  dnl LIBSYMBOL=predis # you most likely want to change this

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PREDIS_DIR/$PHP_LIBDIR, PREDIS_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PREDISLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong predis lib version or lib not found])
  dnl ],[
  dnl   -L$PREDIS_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PREDIS_SHARED_LIBADD)

  PHP_NEW_EXTENSION(predis, predis.c, $ext_shared)
fi
