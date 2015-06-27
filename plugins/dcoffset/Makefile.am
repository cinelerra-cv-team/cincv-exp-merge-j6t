plugin_LTLIBRARIES = dcoffset.la
dcoffset_la_LDFLAGS = -module -shared -avoid-version
dcoffset_la_LIBADD =
dcoffset_la_SOURCES = dcoffset.C
AM_CXXFLAGS = $(LARGEFILE_CFLAGS)

AM_CPPFLAGS = -I$(top_srcdir)/guicast -I$(top_srcdir)/cinelerra -I$(top_srcdir)/quicktime
LIBTOOL = $(SHELL) $(top_builddir)/libtool $(LTCXX_FLAGS)

noinst_HEADERS = dcoffset.h
EXTRA_DIST = picon.png

BUILT_SOURCES = picon_png.h
picon_png.h: picon.png
	$(top_builddir)/guicast/pngtoh $^ || { rm -f $@; exit 1; }
clean-local:
	$(RM) picon_png.h
