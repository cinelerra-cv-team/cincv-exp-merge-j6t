noinst_LTLIBRARIES = libeffecttv.la
libeffecttv_la_LDFLAGS = 
libeffecttv_la_LIBADD =
libeffecttv_la_SOURCES = effecttv.C

plugin_LTLIBRARIES = burn.la
burn_la_LDFLAGS = -avoid-version -module -shared 
burn_la_LIBADD = libeffecttv.la
burn_la_SOURCES = burn.C burnwindow.C
AM_CXXFLAGS = $(LARGEFILE_CFLAGS)

AM_CPPFLAGS = \
	-I$(top_srcdir)/guicast \
	-I$(top_srcdir)/cinelerra \
	-I$(top_srcdir)/quicktime
LIBTOOL = $(SHELL) $(top_builddir)/libtool $(LTCXX_FLAGS)

noinst_HEADERS = burn.h burnwindow.h effecttv.h effecttv.inc
EXTRA_DIST = picon.png

BUILT_SOURCES = picon_png.h
picon_png.h: picon.png
	$(top_builddir)/guicast/pngtoh $^ || { rm -f $@; exit 1; }
clean-local:
	$(RM) picon_png.h
