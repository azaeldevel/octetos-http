
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = liboctetos-http.la

noinst_PROGRAMS = develop


liboctetos_http_la_SOURCES = http.cc http-db.cc
liboctetos_http_la_LDFLAGS = 
liboctetos_http_la_CXXFLAGS = $(CGICC_CFLAGS) $(SQLITE3_CFLAGS) $(OPENSSL_CFLAGS) $(OCTETOS_CORE_CFLAGS)  
liboctetos_http_la_LIBADD = $(CGICC_LIBS) $(SQLITE3_LIBS) $(OPENSSL_LIBS) $(OCTETOS_CORE_LIBS)

develop_SOURCES = main.cc
develop_LDFLAGS = 
develop_CXXFLAGS = $(MICROHTTP_CFLAGS) $(SQLITE3_CFLAGS) $(OPENSSL_CFLAGS) $(OCTETOS_CORE_CFLAGS)
develop_LDADD = $(MICROHTTP_LIBS) $(SQLITE3_LIBS) $(OPENSSL_LIBS) $(OCTETOS_CORE_LIBS) liboctetos-http.la

octetos_core_includedir = $(includedir)/octetos/http
octetos_core_include_HEADERS = http.hh http-db.hh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = octetos-http.pc
EXTRA_DIST = octetos-http.pc.in

DBdir = $(DBDIR)
DB_DATA = database
