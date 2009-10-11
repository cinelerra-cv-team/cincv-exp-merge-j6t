noinst_LTLIBRARIES = libeffecttv.la
libeffecttv_la_LDFLAGS = 
libeffecttv_la_LIBADD = ../colors/libcolors.la
libeffecttv_la_SOURCES = effecttv.C

plugin_LTLIBRARIES = burn.la
burn_la_LDFLAGS = -avoid-version -module -shared 
burn_la_LIBADD = libeffecttv.la
burn_la_SOURCES = burn.C burnwindow.C
AM_CXXFLAGS = $(LARGEFILE_CFLAGS)

INCLUDES = \
	-I$(top_srcdir)/guicast \
	-I$(top_srcdir)/cinelerra \
	-I$(top_srcdir)/quicktime \
	-I$(top_srcdir)/plugins/colors
LIBTOOL = $(SHELL) $(top_builddir)/libtool $(LTCXX_FLAGS)

noinst_HEADERS = burn.h burnwindow.h picon_png.h effecttv.h effecttv.inc
EXTRA_DIST = picon.png
