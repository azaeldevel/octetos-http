
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = liboctetos-http.la

noinst_PROGRAMS = hellobrowser basicauthentication


liboctetos_http_la_SOURCES = http.cc http-db.cc
liboctetos_http_la_LDFLAGS = 
liboctetos_http_la_CXXFLAGS = $(CGICC_CFLAGS) $(SQLITE3_CFLAGS) $(OPENSSL_CFLAGS) $(OCTETOS_CORE_CFLAGS)  
liboctetos_http_la_LIBADD = $(CGICC_LIBS) $(SQLITE3_LIBS) $(OPENSSL_LIBS) $(OCTETOS_CORE_LIBS)

hellobrowser_SOURCES = hellobrowser.cc
hellobrowser_LDFLAGS = 
hellobrowser_CXXFLAGS = $(MICROHTTP_CFLAGS) $(SQLITE3_CFLAGS) $(OPENSSL_CFLAGS) $(OCTETOS_CORE_CFLAGS)
hellobrowser_LDADD = $(MICROHTTP_LIBS) $(SQLITE3_LIBS) $(OPENSSL_LIBS) $(OCTETOS_CORE_LIBS) liboctetos-http.la

basicauthentication_SOURCES = basicauthentication.cc
basicauthentication_LDFLAGS = 
basicauthentication_CXXFLAGS = $(MICROHTTP_CFLAGS) $(SQLITE3_CFLAGS) $(OPENSSL_CFLAGS) $(OCTETOS_CORE_CFLAGS)
basicauthentication_LDADD = $(MICROHTTP_LIBS) $(SQLITE3_LIBS) $(OPENSSL_LIBS) $(OCTETOS_CORE_LIBS) liboctetos-http.la


octetos_core_includedir = $(includedir)/octetos/http
octetos_core_include_HEADERS = http.hh http-db.hh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = octetos-http.pc
EXTRA_DIST = octetos-http.pc.in

DBdir = $(DBDIR)
DB_DATA = database
