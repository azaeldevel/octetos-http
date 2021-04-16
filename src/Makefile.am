
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = liboctetos-nanohttp.la

bin_PROGRAMS = develop


liboctetos_nanohttp_la_SOURCES = http.cc http-db.cc
liboctetos_nanohttp_la_LDFLAGS = 
liboctetos_nanohttp_la_CXXFLAGS = $(CGICC_CFLAGS) $(SQLITE3_CFLAGS) $(OPENSSL_CFLAGS) $(OCTETOS_CORE_CFLAGS)  
liboctetos_nanohttp_la_LIBADD = $(CGICC_LIBS) $(SQLITE3_LIBS) $(OPENSSL_LIBS) $(OCTETOS_CORE_LIBS)

develop_SOURCES = main.cc
develop_LDFLAGS = 
develop_CXXFLAGS = $(CGICC_CFLAGS) $(SQLITE3_CFLAGS) $(OPENSSL_CFLAGS) $(OCTETOS_CORE_CFLAGS)
develop_LDADD = $(CGICC_LIBS) $(SQLITE3_LIBS) $(OPENSSL_LIBS) $(OCTETOS_CORE_LIBS) liboctetos-nanohttp.la

octetos_core_includedir = $(includedir)/octetos/http
octetos_core_include_HEADERS = http.hh http-db.hh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = octetos-nanohttp.pc
EXTRA_DIST = octetos-nanohttp.pc.in

DBdir = $(DBDIR)
DB_DATA = database
