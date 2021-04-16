
AC_INIT(octetos-http, 0.3.0-alpha,azael.devel@gmail.com)
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE()
AM_SILENT_RULES([yes])
AC_PROG_CXX



AC_DEFINE(DBDIR, "/var/octetos/http",["Directorio de http"])



LT_INIT


PKG_CHECK_MODULES(OPENSSL,[openssl])
PKG_CHECK_MODULES(SQLITE3, [sqlite3])

PKG_CHECK_MODULES(OCTETOS_CORE, [octetos-core])

AC_OUTPUT([
Makefile
src/Makefile
src/octetos-http.pc
])
